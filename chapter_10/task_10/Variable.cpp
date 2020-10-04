#include <stdexcept>
#include "Variable.h"

namespace Var {
    double Symbol_table::get(const std::string &s)
// Возвращает значение переменной с именем s
    {
        for (const Variable &v : var_table)
            if (v.name == s) return v.value;
        throw std::runtime_error("get: undefined variable " + s);
    }


    void Symbol_table::set(const std::string &s, double d)
// Присваивает объекту s типа Variable значение d
    {
        for (Variable &v : var_table)
            if (v.name == s) {
                if (v.const_val) throw std::runtime_error("set_value: immutable variable");
                v.value = d;
                return;
            }
        throw std::runtime_error("set: undefined variable " + s);
    }


    bool Symbol_table::is_declared(const std::string &var)
// Есть ли переменная var в векторе var_table?
    {
        for (const Variable &v : var_table)
            if (v.name == var) return true;
        return false;
    }


    double Symbol_table::define(const std::string &var, double val, bool const_val)
// Добавляем пару (var, val) в вектор var_table
    {
        if (is_declared(var) ) throw std::runtime_error(var + " repeat define");
        var_table.push_back( Variable{var, val, const_val} );
        return val;
    }
} // Var namespace