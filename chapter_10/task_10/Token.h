#include <istream>

namespace Token {

    const char number = '8';         // t.kind == number означает, что t - число
    const char quit = 'q';           // t.kind == quit означает, что t - лексема выхода
    const char print = ';';          // t.kind == print означает, что t - лексема печати
    const std::string prompt = "> ";      // Приглашение ввода выражения
    const std::string result = "= ";      // Использует для указания на то, что далее следует результат
    const char name = 'a';           // Лексема Имя
    const char let = 'L';            // Лексема let
    const char letsym = '=';         // Лексема присваивания значения
    const char declkey = '#';        // Ключевое слово let для создания переменных
    const std::string exit_prog = "quit"; // Команда выхода из программы
    const std::string sqrt_fun = "sqrt";  // Лексема вычисления квадратного корня
    const char sqrt_sym = 's';
    const std::string const_str = "const";// Ключевое слово const для создания неизменяемых переменных
    const char const_sym = 'k';      // Лексема для создания констант
    const char help = 'h';           // Вывод помощи о использовании программы
    const std::string help_str = "help";
    const std::string pow_fun = "pow";    // Ключевое слово возведения в степень
    const char pow_sym = 'p';
    const std::string from = "from";      // Изменить поток ввода
    const char from_sym = 'f';
    const std::string to = "to";          // Изменить поток вывода

    // Класс для хранения лексем
    class Token {
    public:
        char kind;        // символ представляет тип хранимых данных; например, '8' - число
        double value;     // для хранения чисел
        std::string name;      // для хранения строковых значений; например, имя переменной

        // Инициализирует kind символом ch
        Token(char ch) :kind(ch) { }

        // Инициализирует kind и value
        Token(char ch, double val) :kind(ch), value(val) { }

        // Инициализирует kind и name
        Token(char ch, std::string n) :kind{ch}, name{n} { }
    };


// Класс для работы с лексемами
// Использует буфер для хранения считанной лексемы
    class Token_stream {
    public:
        // Инициализация буфера
        Token_stream() :full{false}, buffer{0} { };

        Token get(std::istream& is);              // считывает лексему
        void putback(Token t);    // возвращает лексему в поток
        void ignore(std::istream& is, char c);      // Отбрасывает символы до символа 'с' включительно
    private:
        bool full {false};        // Есть ли лексема в буфере?
        Token buffer;             // хранит лексему, возвращенную вызовом putback()
    };
} // Token namespace