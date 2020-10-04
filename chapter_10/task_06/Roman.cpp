#include "Roman.h"

namespace Roman {
    // Римское представление чисел и их арабский эквивалент
    const std::vector<std::string> roman = {
        "M", "CM",  "D", "CD", "C", "XC",
        "L", "XL", "X", "IX", "V", "IV", "I"
    };
    const std::vector<int> arab = {
        1000, 900, 500, 400, 100, 90,
        50, 40, 10, 9, 5, 4, 1
    };


    bool is_roman(char ch)
    // Проверка, что число является римским числом
    {
        std::string st {std::string(1, ch)};
        for (const std::string& sym : roman)
            if (st == sym) return true;
        return false;
    }


    // Конструктор Roman
    Roman::Roman_int::Roman_int(std::string roman)
        :roman{roman} {
            val = to_arab(roman);
    }


    int get_sym_val(char sym)
    // Получить числовое значение римского символа
    {
        std::string st {std::string(1, sym)};
        for (int i = 0; i < roman.size(); ++i)
            if (st == roman[i]) return arab[i];
        throw std::runtime_error("Invalid symbol " + st);
    }


    int to_arab(std::string &str)
    // Перевод римского числа в арабское
    {
        int sum{0};
        int num{0};
        int pred_num = num; // Сравнение с предыдущим символом
                            // для таких чисел, как IV, IX и т.д.
        for (int i = str.length() - 1; i >= 0; --i) {
            num = get_sym_val( str[i] );  // Получить арабское значение римской цифры
            if (num >= pred_num) {
                sum += num;
                pred_num = num;
            } else sum -= num;
        }
        return sum;
    }


    std::string to_roman(int num)
    // Перевод арабских чисел в римские
    {
        std::string res;
        for (int i = 0; i < roman.size(); ++i) {
            int krat = num / arab[i];
            while (krat > 0) {
                res += roman[i];
                num -= arab[i];
                --krat;
            }
        }
        return res;
    }


    // Перегрузка оператора вывода; выводит римское число
    std::ostream& operator << (std::ostream &os, Roman_int &r) {
        return os << r.as_roman();
    }


    // Перегрузка оператора ввода римского числа
    std::istream& operator >> (std::istream &is, Roman_int &r) {
        std::string roman;
        std::cout << "Enter '|' to exit" << std::endl;
        for (char sym; is >> sym && sym != '|';)
            if (is_roman(sym))
                roman += std::string(1, sym); // Преобразовать символ в строку

        r = Roman_int{roman};
        return is;
    }
} // Roman namespace