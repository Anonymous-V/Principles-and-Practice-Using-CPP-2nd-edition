/*
 * Описание задачи:
 * ================
 * Следующая программа получает температуру в градусах Цельсия и преобразует ее
 * в температуру в градусах Кельвина. Этот исходных текст содержит много ошибок.
 * Найдите ошибки, перечислите их и исправьте программу.
 * double ctok(double c) // Преобразует температуру
 * {                     // в градусах Цельсия
 *                       // в температуру в градусах Кельвина
 *     int k = c + 273.15;
 *     return int
 * }
 *
 * int main()
 * {
 *     double c = 0;            // Объявляем входную переменную
 *     cin >> d;                // Вводим температуру
 *     double k = ctok("c");    // Преобразуем температуру
 *     Cout << k << '/n';       // Выводим температуру
 * }
 *
 * Идея реализации:
 * ================
 * Решение представлено ниже
 * */

#include "../../std_lib_facilities.h"

double ctok(double c)
{
    // Константа для преобразования градусов Цельсия в градусы Кельвина
    constexpr double CELS_TO_KELV = 273.15;
    double k = c + CELS_TO_KELV;
    return k;
}

int main() {
    double c = 0;
    cout << "Enter the temperature in degrees Celsius:" << endl;
    cin >> c;
    double k = ctok(c);
    cout << c << " degrees Celsius == "
         << k << " degrees Kelvin" << '\n';

    return 0;
}