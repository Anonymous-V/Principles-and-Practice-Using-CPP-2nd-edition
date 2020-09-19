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
        void sort();             // Сортировка names и ages
        const std::vector<std::string>& get_name() const { return names; }
        const std::vector<double>& get_age() const { return ages; }
    };

    // Вывод пар (names[i], ages[i])
    std::ostream& operator << (std::ostream &os, const Name_pairs &np);
    bool operator == (const Name_pairs& a, const Name_pairs& b);
    bool operator != (const Name_pairs& a, const Name_pairs& b);
}