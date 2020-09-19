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



    // Вывод пар (names[i], ages[i])
    std::ostream& operator << (std::ostream &os, const Name_pairs &np)
    {
        for (int i = 0; i < np.get_name().size(); ++i)
            os << '(' << np.get_name()[i]
               << ',' << np.get_age()[i]
               << ')' << std::endl;
        return os;
    }


    // Сравнение объектов класса
    bool operator == (const Name_pairs& a, const Name_pairs& b)
    {
        if (a.get_name().size() != b.get_name().size()) return false;

        for (int i = 0; i < a.get_name().size(); ++i) {
            if (a.get_name()[i] != b.get_name()[i])
                return false;
            if (a.get_age()[i] != b.get_age()[i])
                return false;
        }
        return true;
    }


    // Сравнение объектов класса
    bool operator != (const Name_pairs& a, const Name_pairs& b)
    {
        return !(a == b);
    }
} // Pairs