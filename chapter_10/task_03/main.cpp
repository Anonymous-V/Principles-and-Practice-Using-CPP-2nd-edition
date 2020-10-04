/*
 * Описание задачи:
 * ================
 * Напишите программу, считывающую данные из файла raw_temps.txt, созданного
 * в упр. 2, в вектор, а затем вычислите среднее значение и медиану температур.
 * Назовите программу temp_stats.cpp
 *
 * Идея реализации:
 * ================
 * Похожая программа уже была реализована не раз в предыдущих задачах, добавилось
 * только чтение из файла. Основная идея - это считать данные, отсортировать
 * вектор температур и вычислить среднее значение и медиану температур.
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // Для использования сортировки sort()


struct Reading {    // Данные по температуре
    int hour;       // Часы после полуночи [0, 23]
    double temp;    // По Фаренгейту
};


std::ifstream& operator >> (std::ifstream& ifs, Reading& r)
// Считывание данных из файла в формате: (hour,temp)
{
    char ch1, ch2, ch3; // Для символов '(', ',', ')'
    int hour;
    double temp;
    ifs >> ch1 >> hour >> ch2 >> temp >> ch3;
    if (ifs.eof()) return ifs;  // Окончание ввода данных из файла
    if (!ifs || ch1 != '(' || ch2 != ',' || ch3 != ')') {
        throw std::runtime_error("Invalid format");
    }
    if (hour < 0 || 23 < hour) throw std::runtime_error("Invalid time");

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
        for (Reading &r : temps)        // Копировать значения температур в друго вектор
            only_temps.push_back(r.temp);

        std::sort(only_temps.begin(), only_temps.end());
        std::sort(temps.begin(), temps.end());
        std::cout << "Average temps: " << avg_temp(only_temps) << std::endl;
        std::cout << "Median temps:  " << med_temp(only_temps) << std::endl;

        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}