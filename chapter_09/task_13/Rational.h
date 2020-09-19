/*
 * Класс Rational. Хранит числа в виде "дробей" - отдельно числитель и знаменатель.
 * Возвращает результат как в виде дроби, так и в десятичном представлении.
 * Также умеет присваивать новые значения дробей.
 * */

#include <iostream>

namespace Rt {
    class Rational {
    public:
        Rational(int a, int b);

        // Немодифицирующие функции:
        double result() { return double(numerator) / denominator; }
        int getNumerator() const { return numerator; }
        int getDenominator() const { return denominator; }

        // Модифицирующие функции:
        void setNums(int a, int b);     // Присвоить значения числителю и знаменателю
    private:
        int numerator;      // Числитель
        int denominator;    // Знаменатель
    };

    // Вспомогательные функции:
    int nod(int a, int b);           // НОД; используется для сокращения дроби
    bool valid_denominator(int num); // Проверка, что знаменатель != 0
    Rational simplify(Rational rt);  // Сокращения числителя и знаменателя
    bool operator == (const Rational& a, const Rational& b); // Сравнение числителя и знаменателя
    Rational operator + (const Rational& a, const Rational& b);
    Rational operator - (const Rational& a, const Rational& b);
    Rational operator * (const Rational& a, const Rational& b);
    Rational operator / (const Rational& a, const Rational& b);
    std::ostream& operator << (std::ostream& os, const Rational& a); // Вывод в виде дроби
} // Rt