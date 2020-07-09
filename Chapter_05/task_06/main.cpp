/*
 * Описание задачи:
 * ================
 * Напишите программу, преобразовывающую температуру в градусах Цельсия в
 * температуру в градусах Фаренгейта и обратно (по формуле из раздела 4.3.3).
 * Воспользуйтесь оценками (раздел 5.8) для того, чтобы убедиться в
 * правдоподобности результатов.
 *
 * Идея реализации:
 * ================
 * Реализованы две функции для переводов из одного формата в другой и обратно.
 * В этих функциях нет предусловий и постусловий, т.к. не рассматривались ситуации
 * с минимальным и максимальным значениями.
 * Для различий вводимых температур использовался switch, где проверялась
 * переменная со значением c - Цельсий и f - Фаренгейт. Если ни одно из этих
 * условий не выполнялось, то вызывалась ошибка. Для понятного вывода использовались
 * переменные str_val_(one/two), которые присваивали соотвествующие названия, в
 * зависимости от условий.
 * */

#include "../../std_lib_facilities.h"

// Перевод из Цельсий в Фаренгейт
double ctof(double temp) {
    return 9.0 / 5 * temp + 32;
}

// Перевод из Фаренгейт в Цельсий
double ftoc(double temp) {
    return 5.0 / 9 * (temp - 32);
}

int main() {
    try {
        double temp, res_temp = 0;
        // Используются для понятного вывода сообщения
        string str_val_one, str_val_two;
        // Определяется, какая температура вводится
        // c - Цельсий, f - Фаренгейт
        char temp_sym;

        cout << "Enter the temperature and specify its format\n"
                "(c - Celsius, f - Fahrenheit)" << endl;
        cin >> temp >> temp_sym;

        switch (temp_sym) {
            case 'c':
                res_temp = ctof(temp);
                str_val_one = "Celsius";
                str_val_two = "Fahrenheit";
                break;
            case 'f':
                res_temp = ftoc(temp);
                str_val_one = "Fahrenheit";
                str_val_two = "Celsius";
                break;
            default:
                throw runtime_error("Invalid temperature format or argument");
        }

        cout << temp << " " << str_val_one << " == "
             << res_temp << " " << str_val_two<< endl;

    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknow error" << endl;
    }

    return 0;
}