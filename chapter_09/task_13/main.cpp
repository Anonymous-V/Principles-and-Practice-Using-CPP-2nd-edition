/*
 * Описание задачи:
 * ================
 * Разработайте и реализуйте класс для представления рациональных чисел Rational.
 * Рациональное число состоит из двух частей: числителя и знаменателя, например
 * 5 / 6 (пять шестых, или .83333). Предусмотрите операторы присваивания, сложения,
 * вычитания, умножения, деления и проверки равенства. Кроме того, предусмотрите
 * преобразование в тип double. Зачем может понадобиться такой класс Rational?
 *
 * Идея реализации:
 * ================
 * Такой класс может поднадобиться для точного хранения значения. Обычное десятичное
 * представление может быть неточным, округлено или усечено, тогда как дроби
 * являются более точными. Например, число 22 / 7 (число PI). В десятичном
 * представлении не может быть точно представлено, т.к. является бесконечным, а
 * в дроби легко умещается.
 * */

#include "Rational.h"

int main() {
    try {
        Rt::Rational r{5, 9};
        Rt::Rational b {2, 24};

        std::cout <<  r << " == " << r.result() << std::endl;

        std::cout << r << " + " << b << " == " << r + b << std::endl;
        std::cout << r << " - " << b << " == " << r - b << std::endl;
        std::cout << r << " * " << b << " == " << r * b << std::endl;
        std::cout << r << " / " << b << " == " << r / b << std::endl;
        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}