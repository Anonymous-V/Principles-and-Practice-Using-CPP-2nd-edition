/*
 * Описание задачи:
 * ================
 * Самой низкой температурой является абсолютный нуль, т.е. -273.15 градусов
 * Цельсия, или 0K. Даже после исправления приведенная выше программа выводит
 * неверные результаты для тепературы ниже абсолютного нуля. Поместите в функцию
 * main() проверку, которая будет выводить сообщение об ошибке для температур
 * ниже -273.15 градусов Цельсия.
 *
 * Идея реализации:
 * ================
 * Для этой задачи реализован метод с помощью инструкции try. Вызывается функция
 * runtime_error, которая принимает строку с сообщением об ошибке.
 * */

#include "../../std_lib_facilities.h"

// Константа для преобразования градусов Цельсия в градусы Кельвина
constexpr double CELS_TO_KELV = 273.15;

double ctok(double c)
{
    return c + CELS_TO_KELV;
}

int main() {
    try {
        double c = 0;
        cout << "Enter the temperature in degrees Celsius:" << endl;
        cin >> c;
        if (c < -CELS_TO_KELV)
            throw runtime_error("The entered temperature should not be "
                                "lower than " + to_string(-CELS_TO_KELV) +
                                " degrees Celsius");
        double k = ctok(c);
        cout << c << " degrees Celsius == "
             << k << " degrees Kelvin" << '\n';

        return 0;
    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
    }
}