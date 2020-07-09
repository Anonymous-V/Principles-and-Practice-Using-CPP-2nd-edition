/*
 * Описание задачи:
 * ================
 * Измените программу так, чтобы она преобразовавала температуру в градусах
 * Кельвина в температуру в градусах Цельсия.
 *
 * Идея реализации:
 * ================
 * Идея остается та же, что и в предыдущей задачи. Только для данной задачи
 * условие изменилось на k < 0
 * */

#include "../../std_lib_facilities.h"

// Функция преобразования градусов Цельсия в градусы Кельвина
double ktoc(double k)
{
    // Предусловие: температура не должна быть ниже 0 градусов Кельвина
    // Константа для преобразования градусов Кельвина в градусы Цельсия
    constexpr double KELV_TO_CELS = 273.15;
    if (k < 0)
        throw runtime_error("The entered temperature should not be "
                            "lower than 0 degrees Kelvin");
    return k + KELV_TO_CELS;
}

int main() {
    try {
        double k = 0;
        cout << "Enter the temperature in degrees Kelvin:" << endl;
        cin >> k;
        double c = ktoc(k);
        cout << k << "K == "
             << c << "C" << '\n';
    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown error" << endl;
    }

    return 0;
}