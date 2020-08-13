/*
 * Простой калькулятор
 *
 * История версий:
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
 * Инструкция:
 *     Выражение
 *     Вывод
 *     Выход
 *
 * Вывод:
 *     ;
 *
 * Выход:
 *     q
 *
 * Выражение:
 *     Терм
 *     Выражение + Терм
 *     Выражение - Терм
 *
 * Терм:
 *     Первичное_выражение
 *     Терм * Первичное_выражение
 *     Терм / Первичное_выражение
 *     Терм % Первичное_выражение
 *
 * Первичное_выражение:
 *     Число
 *     ( Выражение )
 *     - Первичное_выражение
 *     + Первичное_выражение
 *
 * Число:
 *     Литерал_с_плавающей_точкой
 *
 * Ввод из потока cin через Token_stream с именем ts.
 * */


/*
 * Описание задачи:
 * ================
 * Предусмотрите использование символа подчеркивания в именах переменных
 * калькулятора
 *
 * Идея реализации:
 * ================
 * В функцию-член get() в цикл while необходимо добавить ещё одно условие
 * ch == '_'
 * */

#include "../../std_lib_facilities.h"

const char number = '8';         // t.kind == number означает, что t - число
const char quit = 'q';           // t.kind == quit означает, что t - лексема выхода
const char print = ';';          // t.kind == print означает, что t - лексема печати
const string prompt = "> ";      // Приглашение ввода выражения
const string result = "= ";      // Использует для указания на то, что далее следует результат
const char name = 'a';           // Лексема Имя
const char let = 'L';            // Лексема let
const char letsym = '=';         // Лексема присваивания значения
const char declkey = '#';        // Ключевое слово let для создания переменных
const string exit_prog = "exit"; // Команда выхода из программы
const string sqrt_fun = "sqrt";  // Лексема вычисления квадратного корня


// * * * Блок инструкций по работе с лексемами и их хранение * * *
//------------------------------------------------------------------------------


// Класс хранения объявленных переменных
class Variable {
public:
    string name;
    double value;
};


// Класс для хранения лексем
class Token {
public:
    char kind;        // символ представляет тип хранимых данных; например, '8' - число
    double value;     // для хранения чисел
    string name;      // для хранения строковых значений; например, имя переменной

    // Инициализирует kind символом ch
    Token(char ch) :kind(ch) { }

    // Инициализирует kind и value
    Token(char ch, double val) :kind(ch), value(val) { }

    // Инициализирует kind и name
    Token(char ch, string n) :kind{ch}, name{n} { }
};


// Класс для работы с лексемами
// Использует буфер для хранения считанной лексемы
class Token_stream {
public:
    // Инициализация буфера
    Token_stream() :full{false}, buffer{0} { };

    Token get();              // считывает лексему
    void putback(Token t);    // возвращает лексему в поток
    void ignore(char c);      // Отбрасывает символы до символа 'с' включительно
private:
    bool full {false};        // Есть ли лексема в буфере?
    Token buffer;             // хранит лексему, возвращенную вызовом putback()
};


// putback() заносит аргумент в буфер из потока cin и возвращает его
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // копировать t в буфер
    full = true;      // буфер полон
}


// Функция-член возвращает считанных символ из потока или сохраненный в буфере
Token Token_stream::get()
{
    if (full) {       // заполнен ли буфер?
        // возвращаем значение и делаем буфер доступным
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // заметим, что cin пропускает пробелы

    switch (ch) {
        case print:    // вывод значения на экран
        case quit:     // выход из программы
        case '!':      // вычисление факториала
        case '%':      // вычисление остатка от деления
        case '{':      // аналог простым скобкам
        case '}':
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
            return Token(ch);        // Каждый символ представляет сам себя

        case '.':                    // Число с плавающей точкой может
            // начинаться с точки
            // Числовой литерал
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);            // возврат цифры во входной поток
            double val;
            cin >> val;                 // Чтение числа с плавающей точкой
            return Token(number,val);
        }
        case declkey:                   // Лексема объявления переменной
            return Token(let);
        default:
            if ( isalpha(ch) ) {        // Проверка, является ли символ буквой
                string s;
                s += ch;
                // Читаем символы пока это буквы или цифры
                while (cin.get(ch) &&
                       ( isalpha(ch) || isdigit(ch) || ch == '_' )) s += ch;
                cin.putback(ch);
                if (s == exit_prog) return Token(quit); // Лексема выхода из программы
                return Token {name, s}; // название переменной или функции
            }
            error("Bad token");
    }
}


// Функция-член пропускает все символы из входного потока до символа 'c'
// используется для восстановления после неверных выражений
void Token_stream::ignore(char c)
// Символ 'c' представляет разновидность лексем
{
    // Сначала проверяем буфер:
    if (full && c == buffer.kind) {
        full = false;
        return;
    }

    full = false;

    // Теперь проверяем входные данные:
    char ch = 0;
    while (cin >> ch)
        if (ch == c) return;
}

//------------------------------------------------------------------------------


Token_stream ts;                // работа с get() и putback()
vector <Variable> var_table;    // работа с переменными


//------------------------------------------------------------------------------

double expression();        // объявление чтобы primary() мог вызвать expression()
double get_value(string s); // объявления для вызова из primary()
//void set_value(string s, double d); // объявление для вызова из primary()
bool is_declared(string var);       // объявление для вызова из primary()


// * * * Блок инструкций по обработке выражений * * *
//------------------------------------------------------------------------------


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


// функция для работы с: '(', ')', '{', '}' и отрицательными числами
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':           // обработка '(' Выражение ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        case '{':           // обработка '{' Выражение '}'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != '}') error("'}' expected");
            return d;
        }
        case number:        // Вычисление факториала
        {
            Token t2 = ts.get();
            if (t2.kind == '!') return factorial(t.value);
            else ts.putback(t2);
            return t.value; // возвращает значение числа
        }
        case '-':           // обработка числа с отрицательным знаком
            return -primary();
        case '+':
            return primary();
        default:
            // Проверка, что вызвана функция sqrt
            if (t.name == sqrt_fun) {
                double d = primary();
                if (d < 0) error("sqrt; negative argument");
                return sqrt(d);
            }
            // Проверка, что символ является переменной
            if (!t.name.empty()) return get_value(t.name);
            error("primary expected");
    }
}


// Функция для работы с: *, / и %
double term()
{
    double left = primary();
    Token t = ts.get();

    while(true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            case '%': {
                double d = primary();
                if (d == 0) error("%: division by zero");
                // Функция fmod (стандартная библиотека) находит остаток от деления
                left = fmod(left, d);
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);     // вернуть t обратно в поток
                return left;
        }
    }
}


// функция для работы с  + и -
double expression()
{
    double left = term();      // чтение и вычисление Term
    Token t = ts.get();        // получить следующий токен из потока

    while(true) {
        switch(t.kind) {
            case '+':
                left += term();    // вычислить term() и сложить с числом
                t = ts.get();
                break;
            case '-':
                left -= term();    // вычислить term() и вычесть из числа
                t = ts.get();
                break;
            default:
                ts.putback(t);     // вернуть t обратно в поток
                return left;       // вернуть значение
        }
    }
}


// * * * Блок инструкций по объявлению переменных * * *
//------------------------------------------------------------------------------


// Функция возвращает значение переменной по передаваемому имени
double get_value(string s)
// Возвращает значение переменной с именем s
{
    for (const Variable &v: var_table)
        if (v.name == s) return v.value;
    error("get: undefined variable ", s);
}


// Функция присвоения нового значения существующей переменной
void set_value(string s, double d)
// Присваивает объекту s типа Variable значение d
{
    for (Variable &v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
    error("set: undefined variable ", s);
}


// Функция проверки наличия переменной в векторе
bool is_declared(string var)
// Есть ли переменная var в векторе var_table?
{
    for (const Variable &v : var_table)
        if (v.name == var) return true;
    return false;
}


// Функция добавления новой переменной в вектор всех переменных
double define_name(string var, double val)
// Добавляем пару (var, val) в вектор var_table
{
    if (is_declared(var) ) error(var, " repeat define");
    var_table.push_back( Variable{var, val} );
    return val;
}


// Обработка объявления переменных
double declaration()
// Считаем, что мы уже встретили ключевое слово "let"
// Обрабатываем: Имя = Выражение
// Объявление переменной с Именем с начальным значением,
// заданным Выражением
{
    Token t = ts.get();
    if (t.kind != name)
        error("The variable name is expected in the define");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != letsym)
        error("missing the = symbol in the define ", var_name);
    double d = expression();
    define_name(var_name, d);
    return d;
}


// * * * Главный блок инструкций по подготовки к вычислениям * * *
//------------------------------------------------------------------------------


// После появления ошибки отбросить все символы до символа ';'
void clean_up_mess() {
    ts.ignore(print);
}


// Функция создает переменные или производит вычисления
double statement()
{
    Token t = ts.get();
    switch (t.kind) {
        // объявление переменных
        case let:
            return declaration();
            // вычисление значения
        default:
            ts.putback(t);
            return expression();
    }
}


// Функция начала вычислений;
// Приглашение пользователя; вывод результата; выход из программы
void calculate() {
    while (cin)
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print) t = ts.get(); // Отбрасывание команд вывода
            if (t.kind == quit) return;
            ts.putback(t);
            cout << result << statement() << endl;
        } catch (exception &e) {
            cerr << e.what() << '\n'; // Вывод сообщения об ошибке
            clean_up_mess();
        }
}


// Начало программы
int main() {
    try {
        // Предопределенные имена
        define_name("pi", 3.1415926535);
        define_name("e", 2.7182818284);
        define_name("k", 1000);

        calculate();        // Функция вычисления выражений
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