#include "Name_pairs.h"
#include <algorithm>

namespace Pairs {

    // Ввод имен в вектор names
    void Name_pairs::read_names()
    {
        std::string name;
        std::cout << "Enter names (to exit enter 'stop'):" << std::endl;
        while (name != "stop") {
            std::cin >> name;
            if (name == "stop") continue;   // Условие выхода из цикла
            names.push_back(name);
        }
    }


    // Ввод возрастов для имен вектора names
    void Name_pairs::read_ages()
    {
        // Если вектор имен пуст, то вызываем исключение
        if (names.empty()) throw std::runtime_error("Vector names is empty");

        double age;
        for (std::string name : names) {
            std::cout << name << ":";
            std::cin >> age;
            if (!std::cin) throw std::runtime_error("Invalid age");
            ages.push_back(age);
        }
    }


    // Вывод пар (names[i], ages[i])
    void Name_pairs::print()
    {
        if (names.empty()) throw std::runtime_error("Vector are empty");

        for (int i = 0; i < names.size(); ++i)
            std::cout << "(" << names[i] << "," << ages[i] << ")" << std::endl;
        std::cout << std::endl;
    }


    // Сортировка векторов names и ages
    void Name_pairs::sort()
    {
        std::vector<std::string> names_copy = names;     // Необходим для сортировки ages
        std::sort(names.begin(), names.end());  // Стандартная функция сортировки

        for (int i = 0; i < names.size(); ++i)
            for (int j = 0; j < names_copy.size(); ++j)
                if (names[i] == names_copy[j]) {
                    std::swap(names_copy[i], names_copy[j]);
                    std::swap(ages[i], ages[j]);
                    continue;
                }
    }
} // Pairs