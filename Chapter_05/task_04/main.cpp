/*
 * Описание задачи:
 * ================
 * Повторите упр. 3, но в этот раз ошибку обрабатывайте в функции ctok().
 *
 * Идея реализации:
 * ================
 * В этот раз вызов ошибки производится в функции ctok. Также добавлена обработка
 * прочих ошибок, отличающихся от runtime_error.
 * */

#include "../../std_lib_facilities.h"

// Функция преобразования градусов Цельсия в градусы Кельвина
double ctok(double c)
{
    // Предусловие: температура не должна быть ниже -273.15 градусов Цельсия
    // Константа для преобразования градусов Цельсия в градусы Кельвина
    constexpr double CELS_TO_KELV = 273.15;
    if (c < -CELS_TO_KELV)
        throw runtime_error("The entered temperature should not be "
                            "lower than " + to_string(-CELS_TO_KELV) +
                            " degrees Celsius");
    return c + CELS_TO_KELV;
}

int main() {
    try {
        double c = 0;
        cout << "Enter the temperature in degrees Celsius:" << endl;
        cin >> c;
        double k = ctok(c);
        cout << c << "C == "
             << k << "K" << '\n';
    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown error" << endl;
    }

    return 0;
}