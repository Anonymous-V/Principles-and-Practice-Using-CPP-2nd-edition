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
 * Модифицируйте функцию Token_stream::get() так, чтобы обнаружив символ перехода
 * на следующую строку, она возвращала Token(print).
 * Это повлечет за собой реализацию просмотра пробельных символов и обработку
 * символа '\n'. Для этого можно использовать стандартную библиотечную функцию
 * isspace(ch), возвращающую значение true, если символ ch ялвяется пробельным.
 *
 * Идея реализации:
 * ================
 * В данной реализации необходимо было заменить считывание символа с обычного cin
 * на cin.get с чтением всех символов. Кроме того, в функцию primary() был
 * добавлен ещё один раздел case print. Это необходимо было сделать, т.к. если
 * передано незаконченное выражение, например, 3+, то в этом случае ни результата
 * об ошибке, ни вычисленного результат не было, пока не ввести ещё символ или
 * нажать на Enter.
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
const string const_str = "const";// Ключевое слово const для создания неизменяемых переменных
const char const_sym = 'k';       // Лексема для создания констант


// * * * Блок инструкций по работе с лексемами и их хранение * * *
//------------------------------------------------------------------------------


// Класс хранения объявленных переменных
class Variable {
public:
    string name;
    double value;
    bool const_val {false};
};


// Класс для работы с переменными
class Symbol_table {
public:
    double get(const string &s);
    void set(const string &s, double d);
    bool is_declared(const string &var);
    double define(const string &var, double val, bool const_val);

private:
    vector <Variable> var_table;
};


double Symbol_table::get(const string &s)
// Возвращает значение переменной с именем s
{
    for (const Variable &v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined variable ", s);
}


void Symbol_table::set(const string &s, double d)
// Присваивает объекту s типа Variable значение d
{
    for (Variable &v : var_table)
        if (v.name == s) {
            if (v.const_val) error("set_value: immutable variable");
            v.value = d;
            return;
        }
    error("set: undefined variable ", s);
}


bool Symbol_table::is_declared(const string &var)
// Есть ли переменная var в векторе var_table?
{
    for (const Variable &v : var_table)
        if (v.name == var) return true;
    return false;
}


double Symbol_table::define(const string &var, double val, bool const_val)
// Добавляем пару (var, val) в вектор var_table
{
    if (is_declared(var) ) error(var, " repeat define");
    var_table.push_back( Variable{var, val, const_val} );
    return val;
}


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
//    cin >> ch;    // заметим, что cin пропускает пробелы
    while(cin.get(ch) && isspace(ch))       // cin.get(ch) не пропускает пробельные символы
        if (ch == '\n') return Token(print);

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
                if (s == const_str) return Token(const_sym); // Лексема для создания констант
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


Token_stream ts;            // работа с get() и putback()
Symbol_table st;            // Работа с переменными
double expression();        // объявление чтобы primary() мог вызвать expression()


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
            ts.putback(t2);
            return t.value; // возвращает значение числа
        }
        case '-':           // обработка числа с отрицательным знаком
            return -primary();
        case '+':
            return primary();
        case print:         // выражение не закончено, но перенос строки произошел
            error("primary: invalid expression");
        default:
            Token t2 = ts.get();
            // Проверка присваивания переменной нового значения
            if (t2.kind == letsym) {
                double d = expression();
                // Проверка, что переменная объявлена
                if ( !st.is_declared(t.name) ) error(t.name, " isn't defined");
                // Установка переменной нового значения
                st.set(t.name, d);
                return d;
            }
            ts.putback(t2);
            // Проверка, что вызвана функция sqrt
            if (t.name == sqrt_fun) {
                double d = primary();
                if (d < 0) error("sqrt; negative argument");
                return sqrt(d);
            }
            // Проверка, что символ является переменной
            if (!t.name.empty()) return st.get(t.name);
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


// Обработка объявления переменных
double declaration(bool const_val)
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
    st.define(var_name, d, const_val);
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
            return declaration(false);
            // Объявление констант
        case const_sym:
            return declaration(true);
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
        st.define("pi", 3.1415926535, true);
        st.define("e", 2.7182818284, true);
        st.define("k", 1000, true);

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