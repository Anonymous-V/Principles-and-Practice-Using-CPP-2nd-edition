#include <iostream>
#include <vector>


namespace Roman {

    // Класс Roman_int хранит римское число и его арабский эквивалент
    class Roman_int {
    public:
        Roman_int(std::string roman);

        int as_int() const { return val; }              // Вернуть арабское представление числа
        std::string as_roman() const { return roman; }  // Вернуть римское представление числа
    private:
        std::string roman;  // Римское представление числа
        int val;            // Арабское представление числа
    };

    // Вспомогательные функции:
    int to_arab(std::string &str); // Перевод римского числа в арабское
    std::string to_roman(int num); // Перевод арабского числа в римское
    bool is_roman(char ch);        // Проверить, является ли символ римским числом

    // Перегрузка операторов ввода и вывода
    std::ostream &operator<<(std::ostream &os, Roman_int &r);
    std::istream &operator>>(std::istream &is, Roman_int &r);
} // Roman namespace