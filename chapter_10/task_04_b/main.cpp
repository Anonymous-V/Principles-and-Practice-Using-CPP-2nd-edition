/*
 * Описание задачи:
 * ================
 * Модифицируйте программу store_temps.cpp из упр. 2, включив в нее суффикс 'c'
 * для шкалы Цельсия и суффикс 'f' для шкалы Фаренгейта. Затем модифицируйте
 * программу temp_stats.cpp, чтобы перед записью в вектор она проверяла каждое
 * показание и преобразовывала температуру в градусах Цельсия в градусы Фаренгейта.
 *
 * Идея реализации:
 * ================
 * Программа практически не изменилась. Добавилась только инструкция для считывания
 * шкалы измерений, её проверка и перевод из Цельсий в Фаренгейт.
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // Для использования сортировки sort()

const char FAR = 'f';   // Для шкалы Фаренгейт
const char CEL = 'c';   // Для шкалы Цельсий


struct Reading {    // Данные по температуре
    int hour;       // Часы после полуночи [0, 23]
    double temp;    // По Фаренгейту
};


std::ifstream& operator >> (std::ifstream& ifs, Reading& r)
// Считывание данных из файла в формате: (hour,temp,scale)
{
    char ch1, ch2, ch3, ch4; // Для символов '(', ',', ',' ')'
    int hour;
    double temp;
    char scale;
    ifs >> ch1 >> hour >> ch2 >> temp >> ch3 >> scale >> ch4;
    if (ifs.eof()) return ifs;  // Окончание ввода данных из файла
    if (!ifs || ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
        throw std::runtime_error("Invalid format");
    }
    if (hour < 0 || 23 < hour) throw std::runtime_error("Invalid time");

    switch (scale) { // Проверить корреткность шкалы измерения
        case FAR:
            break;
        case CEL:
            temp = 9.0 / 5 * temp + 32; // Преобразование Цельсий в Фаренгейт
            break;
        default:
            throw std::runtime_error("Invalid scale");
    }

    r.hour = hour;
    r.temp = temp;
    return ifs;
}


void fill_from_file(std::vector<Reading>& temps, const std::string& file_name)
// Открытие файла и заполнение вектора часами и температурами
{
    std::ifstream ist {file_name};
    if (!ist) throw std::runtime_error("Unable to open file");

    for (Reading r{}; ist >> r;)
        temps.push_back(r);
}


double avg_temp(std::vector<double>& temps)
// Вычисление среднего значения температур
{
    if (temps.empty()) throw std::runtime_error("Vector is empty");

    double sum {0};
    for (double t : temps)
        sum += t;
    return sum / temps.size();
}


double med_temp(std::vector<double>& temps)
// Вычисление медианы температур
// Предполагается, что передается уже отсортированный вектор
{
    if (temps.empty()) throw std::runtime_error("Vector is empty");

    if (temps.size() % 2 != 0) return temps[temps.size() / 2];

    double val_one = temps[temps.size() / 2];
    double val_two = temps[temps.size() / 2 + 1];
    return (val_one + val_two) / 2;
}


int main() {
    try {
        std::vector<Reading> temps;     // Здесь хранится считанная информация
        std::vector<double> only_temps; // Только значения температур

        fill_from_file(temps, "raw_temps.txt");
        for (Reading &r : temps)        // Копировать значения температур в другой вектор
            only_temps.push_back(r.temp);

        std::sort(only_temps.begin(), only_temps.end());
        std::cout << "Average temps: " << avg_temp(only_temps) << std::endl;
        std::cout << "Median temps:  " << med_temp(only_temps) << std::endl;

        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}