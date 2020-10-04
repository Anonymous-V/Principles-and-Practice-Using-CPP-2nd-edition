/*
 * Класс для хранения переменных и констант
 * */

#include <string>
#include <vector>

namespace Var {

    // Структура для хранения объявленных переменных
    struct Variable {
        std::string name;
        double value;
        bool const_val {false};
    };

    // Класс для работы с переменными
    class Symbol_table {
    public:
        double get(const std::string &s);
        void set(const std::string &s, double d);
        bool is_declared(const std::string &var);
        double define(const std::string &var, double val, bool const_val);

    private:
        std::vector <Variable> var_table;
    };
} //Var namespace