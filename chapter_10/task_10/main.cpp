/*
 * Простой калькулятор
 *
 * История версий:
 *
 * 03.10.2020 добавлена работа с файлами.
 *
 * Переписан с книги Виталием в июле 2020 г.
 *
 * Эта программа реализует основные выражения калькулятора.
 *
 * Ввод осуществляется из потока cin; вывод - в поток cout.
 *
 *
 * Грамматика для ввода:
 *
 * Вычисления:
 *     Инструкция
 *     Вывод_справки
 *     Вывод
 *     Выход
 *
 * Вывод:
 *     ;
 *
 * Выход:
 *     q
 *
 * Вывод_справки:
 *     help
 *
 * Инструкция:
 *     # Объявление_переменной
 *     const Объявление_переменной
 *     Функция
 *     from (импорт файла)
 *     Выражение
 *
 * Объявление_переменной:
 *     Имя '=' Выражение
 *
 * Имя:
 *     Латинская_буква
 *     Латинская_буква Последовательность_имени
 *
 * Последовательность_имени:
 *     Латинская_буква
 *     '_'
 *     Натуральное_число
 *
 * Латинская_буква:
 *     Символы_'a'..'b'_или_'A'..'B'
 *
 * Натуральное_число:
 *     Число_от_нуля_до_девяти
 *
 * Выражение:
 *     Терм
 *     Выражение '+' Терм
 *     Выражение '-' Терм
 *
 * Терм:
 *     Первичное_выражение
 *     Терм '*' Первичное_выражение
 *     Терм '/' Первичное_выражение
 *     Терм '%' Первичное_выражение
 *
 * Первичное_выражение:
 *     Число
 *     '(' Выражение ')'
 *     '-' Первичное_выражение
 *     '+' Первичное_выражение
 *     Число '!'
 *     Значение_имени
 *     Имя '=' Выражение
 *
 * Значение_имени:
 *     Число
 *
 * '!':
 *     Вычисление факториала
 *
 * Функция:
 *     sqrt '(' Выражение ')'
 *     pow '(' Выражение ',' Выражение ')'
 *
 * Число:
 *     Литерал_с_плавающей_точкой
 *
 * Ввод из потока cin через Token_stream с именем ts.
 * */


/*
 * Описание задачи:
 * ================
 * Добавьте в калькулятор из главы 7 команду from x, осуществляющую ввод данных
 * из файла x. Добавьте в калькулятор команду to y, выполняющую вывод (как обычных
 * данных, так и сообщений об ошибках) в файл y. Напишите набор тестов, основанных
 * на идеях из раздела 7.3, и примените его для проверки калькулятора. Объясните,
 * как использовать эти команды для тестирования.
 *
 * Идея реализации:
 * ================
 * Произошли некоторые изменения в программе, помимо работы с файлами:
 * 1. Обработка функций (sqrt, pow) перенесена в функци statement()
 * 2. В функцию-член get() добавлена проверка окончания ввода (для файлов)
 *
 * Остальные изменения касаются работы с файлами. Для того, чтобы такую возможность реализовать
 * необходимо передавать потоки ввода и вывода начиная с первого вызова программы.
 * С помощью команд from и to осуществляется, соответственно, ввод из файла и вывод.
 * В класс Token_stream не были добавлены потоки ввода и вывода, т.к. неполучалось заменить их
 * потоки для работы с файлами. По этой причине создается новый Token_stream и уже через него
 * происходит работа с файлами.
 *
 * Команда для работы с файлами выглядит следующим образом:
 * from <имя_входного_файла> to <имя_выходного_файла> - считать из входного файла и записать в выходной файл
 *                      или
 * from <имя_входного_файла> to default - считать из входного файла и вывести в консоль
 *
 * Кроме того, файл был немного декомпозирован: выделены работа с переменными и потоком символов
 * */

#include "Variable.h"
#include "Token.h"
#include "../../std_lib_facilities.h"

// * * * Вспомогательные функции * * *
//------------------------------------------------------------------------------

Token::Token_stream ts {};    // работа с get() и putback()
Var::Symbol_table st;            // Работа с переменными
double expression(istream& is, ostream& os);        // объявление чтобы primary() мог вызвать expression()
void calculate(istream& is, ostream& os);


string read_name(istream& is)
// Считать строковые значения: 'from', имена файлов и 'to'
{
    string s;
    char ch;
    // Читаем символы пока это буквы или цифры
    while (is.get(ch) && isspace(ch)) { } // Пропустить все пробелы
    is.putback(ch);
    while (is.get(ch) &&
           ( isalpha(ch) || isdigit(ch) || ch == '.' )) s += ch;
    is.putback(ch);
    return s;
}


void change_stream(istream& is, ostream& os)
// Подключение файлов имеет формат:
// from <входной_файл> to <выходной_файл>
// или
// from <входной_файл> to default
{
    string iname = read_name(is);
    ifstream ifs {iname};                                  // Подключение входного файла
    if (!ifs) error("Unable to open file ", iname);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    string to_loc = read_name(is);
    if (to_loc != Token::to) error("Invalid output");   // Проверка, что введено слово 'to'

    string oname = read_name(is);                      // Если введено default, то вывод в консоль
    if (oname == "default") {
        calculate(ifs, cout);
        return;
    }

    ofstream ofs {oname};                                 // Подключаем выходной файл
    if (!ofs) error("Unable to open file ", oname);
    ofs.exceptions(ofs.exceptions() | ios_base::badbit);

    calculate(ifs, ofs);
}


// Функция возведения в степень
double pow_funct(istream& is, ostream& os) {
    Token::Token t2 = ts.get(is);
    // Считали скобку
    if (t2.kind != '(') error("");

    double num = expression(is, os);

    // Считали запятую
    t2 = ts.get(is);
    if (t2.kind != ',') error("sqr: a comma was omitted");

    double degree = expression(is, os);

    // Считали последнюю скобку в pow
    t2 = ts.get(is);
    if (t2.kind != ')') error("");

    return pow(num, degree);
}

// Фукнция вычисления факториала
int factorial(double val) {
    // Предусловие: Значение должно быть положительным и целым
    if (val - int(val) != 0) error("An integer value is required");
    if (val < 0) error("Only positive value for factorial");

    int fact = 1;
    for (int i = 1; i <= val; ++i)
        fact *= i;
    return fact;
}

// Вывод справки
void write_help(ostream& os) {
    os << "Allowed operations: +, -, *, /, %, (, ), {, }\n";
    os << "Allowed functions: sqrt(num)\n";
    os << "Variables: #name = expression()\n";
    os << "Constants: const name = expression()\n";
    os << "To import a file, use the syntax: \n"
          "'from <input_file> to <output_file>'\n or"
          "'from <input_file> to default' for output to the console\n";
}


// * * * Блок инструкций по обработке выражений * * *
//------------------------------------------------------------------------------


// функция для работы с: '(', ')', '{', '}' и отрицательными числами
double primary(istream& is, ostream& os)
{
    Token::Token t = ts.get(is);
    switch (t.kind) {
        case '(':           // обработка '(' Выражение ')'
        {
            double d = expression(is, os);
            t = ts.get(is);
            if (t.kind != ')') error("')' expected");
            return d;
        }
        case '{':           // обработка '{' Выражение '}'
        {
            double d = expression(is, os);
            t = ts.get(is);
            if (t.kind != '}') error("'}' expected");
            return d;
        }
        case Token::number:        // Вычисление факториала
        {
            Token::Token t2 = ts.get(is);
            if (t2.kind == '!') return factorial(t.value);
            ts.putback(t2);
            return t.value; // возвращает значение числа
        }
        case '-':           // обработка числа с отрицательным знаком
            return -primary(is, os);
        case '+':
            return primary(is, os);
        case Token::print:         // выражение не закончено, но перенос строки произошел
            error("primary: invalid expression");
        default:
            Token::Token t2 = ts.get(is);
            // Проверка присваивания переменной нового значения
            if (t2.kind == Token::letsym) {
                double d = expression(is, os);
                // Проверка, что переменная объявлена
                if ( !st.is_declared(t.name) ) error(t.name, " isn't defined");
                // Установка переменной нового значения
                st.set(t.name, d);
                return d;
            }
            ts.putback(t2);
            // Проверка, что символ является переменной
            if (!t.name.empty()) return st.get(t.name);
            error("primary expected");
    }
}


// Функция для работы с: *, / и %
double term(istream& is, ostream& os)
{
    double left = primary(is, os);
    Token::Token t = ts.get(is);

    while(true) {
        switch (t.kind) {
            case '*':
                left *= primary(is, os);
                t = ts.get(is);
                break;
            case '/':
            {
                double d = primary(is, os);
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get(is);
                break;
            }
            case '%': {
                double d = primary(is, os);
                if (d == 0) error("%: division by zero");
                // Функция fmod (стандартная библиотека) находит остаток от деления
                left = fmod(left, d);
                t = ts.get(is);
                break;
            }
            default:
                ts.putback(t);     // вернуть t обратно в поток
                return left;
        }
    }
}


// функция для работы с  + и -
double expression(istream& is, ostream& os)
{
    double left = term(is, os);      // чтение и вычисление Term
    Token::Token t = ts.get(is);        // получить следующий токен из потока

    while(true) {
        switch(t.kind) {
            case '+':
                left += term(is, os);    // вычислить term() и сложить с числом
                t = ts.get(is);
                break;
            case '-':
                left -= term(is, os);    // вычислить term() и вычесть из числа
                t = ts.get(is);
                break;
            default:
                ts.putback(t);     // вернуть t обратно в поток
                return left;       // вернуть значение
        }
    }
}


// * * * Блок инструкций по объявлению переменных * * *
//------------------------------------------------------------------------------


// Обработка объявления переменных
double declaration(istream& is, ostream& os, bool const_val)
// Считаем, что мы уже встретили ключевое слово "let"
// Обрабатываем: Имя = Выражение
// Объявление переменной с Именем с начальным значением,
// заданным Выражением
{
    Token::Token t = ts.get(is);
    if (t.kind != Token::name)
        error("The variable name is expected in the define");
    string var_name = t.name;

    Token::Token t2 = ts.get(is);
    if (t2.kind != Token::letsym)
        error("missing the = symbol in the define ", var_name);
    double d = expression(is, os);
    st.define(var_name, d, const_val);
    return d;
}


// * * * Главный блок инструкций по подготовки к вычислениям * * *
//------------------------------------------------------------------------------


// После появления ошибки отбросить все символы до символа ';'
void clean_up_mess(istream& is) {
    ts.ignore(is, Token::print);
}


// Функция создает переменные или производит вычисления
double statement(istream& is, ostream& os)
{
    Token::Token t = ts.get(is);
    switch (t.kind) {
        // объявление переменных
        case Token::let:
            return declaration(is, os, false); // Объявление констант
        case Token::const_sym:
            return declaration(is, os, true);  // вычисление значения
        case Token::sqrt_sym: {
            double d = expression(is, os);
            if (d < 0) error("sqrt; negative argument");
            return sqrt(d);
        }
        case Token::pow_sym:
            return pow_funct(is, os);
        default:
            ts.putback(t);
            return expression(is, os);
    }
}


// Функция начала вычислений;
// Приглашение пользователя; вывод результата; выход из программы
void calculate(istream& is, ostream& os) {
    while (is)
        try {
            os << Token::prompt;
            Token::Token t = ts.get(is);
            while (t.kind == Token::print) t = ts.get(is); // Отбрасывание команд вывода
            if (t.kind == Token::from_sym) {                  // Переопределить метод ввода и вывода
                change_stream(is, os);
                continue;
            }
            if (t.kind == Token::quit) return;
            if (t.kind == Token::help) write_help(os);     // Вызов справки
            else {
                ts.putback(t);
                os << Token::result << statement(is, os) << endl;
            }
        } catch (exception &e) {
            os << e.what() << '\n'; // Вывод сообщения об ошибке
            clean_up_mess(is);
        }
}


// Начало программы
int main() {
    try {
        // Предопределенные имена
        st.define("pi", 3.1415926535, true);
        st.define("e", 2.7182818284, true);
        st.define("k", 1000, true);

        cout << "Enter 'help' to call help function\n";
        calculate(cin, cout);        // Функция вычисления выражений
        keep_window_open(); // Удерживает консольное окно открытым
        return 0;
    }
    catch (exception &e) {
        cerr << "error: " << e.what() << '\n';
        keep_window_open();
        return 1;
    }
    catch (...) {
        cerr << "Oops: unknown exception!\n";
        keep_window_open();
        return 2;
    }
}