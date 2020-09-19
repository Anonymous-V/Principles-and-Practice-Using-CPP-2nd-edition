#include "Rational.h"

namespace Rt {

    // Конструктор
    Rational::Rational(int a, int b)
        :numerator{a}, denominator{b}
    {
        if (!valid_denominator(b)) throw std::runtime_error("Division by zero");
    }


    // Присвоение новых значений дроби
    void Rational::setNums(int a, int b)
    {
        if (!valid_denominator(b)) throw std::runtime_error("Division by zero");
        numerator = a;
        denominator = b;
    }


    // Проверка, что знаменатель не равен нулю
    bool valid_denominator(int num)
    {
        return num != 0;
    }


    // Сокращение дроби на общее значение
    Rational simplify(Rational rt)
    {
        int numerator = rt.getNumerator();
        int denominator = rt.getDenominator();
        int nd = nod(numerator, denominator); // Общее значение находится через НОД
        rt.setNums(numerator / nd, denominator / nd);
        return rt;
    }


    // НОД для сокращения дроби
    int nod(int a, int b)
    {
        a = abs(a);
        b = abs(b);
        for(;;) {   // Бесконечный цикл
            if (a % b == 0) return b;
            if (b % a == 0) return a;
            (a > b) ? a -= b : b -= a;  // Уменьшить один из знаменателей на другой
        }
    }


    // Операция "сложения"
    Rational operator + (const Rational& a, const Rational& b)
    {
        int num = a.getNumerator()   * b.getDenominator() // Перемножение крест-накрест
                + a.getDenominator() * b.getNumerator();  // т.е. числителя на знаменатель
        int den = a.getDenominator() * b.getDenominator();
        return simplify({num, den});
    }


    // Операция "вычитания"
    Rational operator - (const Rational& a, const Rational& b)
    {
        Rational r = {-b.getNumerator(), b.getDenominator()}; // Достаточно добавить "минус"
        return simplify(a + r); // в числитель или знаменатель и произвести сложение
    }


    // Операция "умножения"
    Rational operator * (const Rational& a, const Rational& b)
    {
        int num = a.getNumerator() * b.getNumerator();
        int den = a.getDenominator() * b.getDenominator();
        return simplify({num, den});
    }


    // Операция "деления"
    Rational operator / (const Rational& a, const Rational& b)
    {
        Rational r {b.getDenominator(), b.getNumerator()};
        return simplify(a * r); // Деление - это умножение с перевернутой второй дробью
    }


    // Сравнение соответствующих значений
    bool operator == (const Rational& a, const Rational& b)
    {
        return a.getNumerator() == b.getNumerator()
            && b.getDenominator() == b.getDenominator();
    }


    // Вывод в виде дроби
    std::ostream& operator << (std::ostream& os, const Rational& a)
    {
        return os << a.getNumerator() << '/' << a.getDenominator();
    }
}