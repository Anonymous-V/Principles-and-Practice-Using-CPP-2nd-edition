/*
 * Описание задачи:
 * ================
 * Добавьте оператор вычисления факториала: для его представления используйте
 * восклицательный знак !. Например, выражение 7! означает 7*6*5*4*3*2*1.
 * Присвойте оператору ! более высокий приоритет по сравнению с операторами * и /,
 * т.е. 7*8! должно означать 7*(8!), а не (7*8)!. Начните с модификации грамматики,
 * чтобы учесть оператор с более высоким приоритетом. Для согласования со
 * стандартным математическим определением факториала значение 0! примите равным 1.
 * Указание: калькулятор работает с числами типа double, но факториал определен
 * только для целочисленных значений. Поэтому для вычисления x! присвойте значение
 * x переменной типа int и вычисляйте факториал этой переменной.
 *
 * Идея реализации:
 * ================
 * В данной программе вычисление факториала целесообразно проводить в функции
 * primary(), когда возвращается число. Необходимо проверить следующий символ
 * за цифрой и убедиться есть ли там символ !. Если есть, то вычислить факториал и
 * вернуть значение факториала, либо вернуть символ обратно, т.е. поместить его в
 * буфер.
 * */

#include "../../std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
            :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
            :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full {false};        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
        :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
        case '=':    // for "print"
        case 'x':    // for "quit"
        case '!':
        case '{': case '}':
        case '(': case ')': case '+': case '-': case '*': case '/':
            return Token(ch);        // let each character represent itself
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '9':
        {
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
            return Token('8',val);   // let '8' represent "a number"
        }
        default:
            error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

int factorial(double val) {
	if (val - int(val) != 0) error("An integer value is required");
	if (val < 0) error("Only positive value for factorial");
    int fact = 1;
    for (int i = 1; i <= val; ++i)
        fact *= i;
    return fact;
}

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':    // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        case '{':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != '}') error("'}' expected");
            return d;
        }
        case '8':            // we use '8' to represent a number
        {
            Token t2 = ts.get();
            if (t2.kind == '!') return factorial(t.value);
            else ts.putback(t2);
            return t.value;
        }
        default:
            error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

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
            default:
                ts.putback(t);     // put t back into the token stream
                return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
            case '+':
                left += term();    // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term();    // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.putback(t);     // put t back into the token stream
                return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

int main() {
    try {
        double val {0};

        cout << "Welcome to out simple calculator\n"
             << "Please enter expressions using floating-point numbers\n"
             << endl;
        cout << "Acceptable operations: "
             << "+, -, *, /, (, ), {, }, !, ."
             << endl;
        cout << "To output results, use the symbol '='" << endl;
        cout << "To exit the program use 'x'" << endl;

        while (cin) {
            Token t = ts.get();

            if (t.kind == 'x') break; // 'x' for quit
            if (t.kind == '=')        // ';' for "print now"
                cout << "=" << val << '\n';
            else
                ts.putback(t);
            val = expression();
        }
        keep_window_open();
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