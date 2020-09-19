#include <iostream>
#include <vector>

namespace Pairs {
    class Name_pairs {
        std::vector<std::string> names;
        std::vector<double> ages;

    public:
        Name_pairs() {};
        void read_names();       // Ввод имен в names
        void read_ages();        // Ввод возрастов в ages
        void print();            // Вывод пар (names[i], ages[i])
        void sort();             // Сортировка names и ages
    };
}