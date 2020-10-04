#include <stdexcept>
#include "Token.h"

namespace Token {
    // putback() заносит аргумент в буфер из потока cin и возвращает его
    void Token_stream::putback(Token t)
    {
        if (full) throw std::runtime_error("putback() into a full buffer");
        buffer = t;       // копировать t в буфер
        full = true;      // буфер полон
    }


// Функция-член возвращает считанных символ из потока или сохраненный в буфере
    Token Token_stream::get(std::istream& is)
    {
        if (full) {       // заполнен ли буфер?
            // возвращаем значение и делаем буфер доступным
            full = false;
            return buffer;
        }

        char ch;
//    cin >> ch;    // заметим, что cin пропускает пробелы
        while(is.get(ch) && isspace(ch))       // cin.get(ch) не пропускает пробельные символы
            if (ch == '\n') return Token(print);

        if (!is) return Token(quit);   // При случае, когда конец файла и в calculate пытается
        // считать следующий символ

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
            case ',':      // используется в функции возведения в степень
                return Token(ch);        // Каждый символ представляет сам себя

            case '.':                    // Число с плавающей точкой может
                // начинаться с точки
                // Числовой литерал
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                is.putback(ch);            // возврат цифры во входной поток
                double val;
                is >> val;                 // Чтение числа с плавающей точкой
                return Token(number,val);
            }
            case declkey:                   // Лексема объявления переменной
                return Token(let);
            default:
                if ( isalpha(ch) ) {        // Проверка, является ли символ буквой
                    std::string s;
                    s += ch;
                    // Читаем символы пока это буквы или цифры
                    while (is.get(ch) &&
                           ( isalpha(ch) || isdigit(ch) || ch == '_' )) s += ch;
                    is.putback(ch);
                    if (s == exit_prog) return Token(quit); // Лексема выхода из программы
                    if (s == const_str) return Token(const_sym); // Лексема для создания констант
                    if (s == help_str) return Token(help);  // Лексема для вывода справки
                    if (s == sqrt_fun) return Token(sqrt_sym);  // Корень из числа
                    if (s == pow_fun) return Token(pow_sym);    // Возведение в степень
                    if (s == from) return Token(from_sym);      // Импортировать данные из файла
                    return Token {name, s}; // название переменной или функции
                }
                throw std::runtime_error("Bad token");
        }
    }


// Функция-член пропускает все символы из входного потока до символа 'c'
// используется для восстановления после неверных выражений
    void Token_stream::ignore(std::istream& is, char c)
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
        while (is.get(ch))
            if (ch == c || ch == '\n') return;
    }
} // Token namespace