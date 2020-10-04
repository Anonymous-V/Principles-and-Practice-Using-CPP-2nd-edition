/*
 * Описание задачи:
 * ================
 * Напишите программу, создающую файл из данных, записанных в виде объектов класса
 * Reading, определенного в разделе 10.5. Для проверки заполните файл как минимум 50
 * показаниями температуры. Назовите эту программу store_temps.cpp, а создаваемый
 * файл - raw_temps.txt
 *
 * Идея реализации:
 * ================
 * Сама программа уже написана в книге. Идея состоит в том, чтобы открыть файлы
 * для ввода и вывода и считать данные из одного файла в другой.
 * */

#include <iostream>
#include <fstream>
#include <vector>


struct Reading {    // Данные по температуре
    int hour;       // Часы после полуночи [0, 23]
    double temp;    // По Фаренгейту
};


int main() {
    std::string iname {"input.txt"};
    std::ifstream ist {iname};
    if (!ist) throw std::runtime_error("Unable to open file");

    std::string oname {"raw_temps.txt"};
    std::ofstream ost {oname};
    if (!ost) throw std::runtime_error("Unable to create file");

    std::vector<Reading> temps; // Здесь хранится считанная информация
    int hour;
    double temperature;

    while (ist >> hour >> temperature) {
        if (hour < 0 || 23 < hour) throw std::runtime_error("Invalid time");
        temps.push_back(Reading{hour, temperature});
    }

    for (int i = 0; i < temps.size(); ++i)
        ost << '(' << temps[i].hour << ','
            << temps[i].temp << ")\n";

    return 0;
}