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
 * Реализация осталась той же, только добавился ещё один параметр - шкала измерения.
 * Для шкалы Цельсия соответствует значение 'c', для шкалы Фаренгейт - 'f'. Эти
 * значения также записываются в выходной файл.
 * */

#include <iostream>
#include <fstream>
#include <vector>


struct Reading {    // Данные по температуре
    int hour;       // Часы после полуночи [0, 23]
    double temp;    // Температура
    char scale;     // Шкала Цельсия или Фаренгейта
};


void read_from_file(std::vector<Reading>& temps, const std::string& file_name)
// Считать данные из файла в формате: hour, temp, scale
{
    std::ifstream ist {file_name};
    if (!ist) throw std::runtime_error("Unable to open file");

    int hour;
    double temperature;
    char scale;

    while (ist >> hour >> temperature >> scale) {
        if (hour < 0 || 23 < hour) throw std::runtime_error("Invalid time");
        temps.push_back(Reading{hour, temperature, scale});
    }
}


void write_to_file(std::vector<Reading>& temps, const std::string& file_name)
// Записать данные в файл в формате: (hour, temp, scale)
{
    std::ofstream ost {file_name};
    if (!ost) throw std::runtime_error("Unable to create file");

    for (Reading& temp : temps)
        ost << '(' << temp.hour << ','
            << temp.temp << ','
            << temp.scale << ")\n";
}


int main() {
    std::vector<Reading> temps; // Здесь хранится считанная информация

    read_from_file(temps, "input.txt");
    write_to_file(temps, "raw_temps.txt");

    return 0;
}