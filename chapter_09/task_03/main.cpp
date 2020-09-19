/*
 * Описание задачи:
 * ================
 * Замените фукнцию Name_pair::print() (глобальным) оператором operator<< и
 * определите операции == и != для объектов класса Name_pair
 *
 * Идея реализации:
 * ================
 * Добавил три перегрузки операторов. Понял, что при перегрузке оператора вывода
 * необходимо всё содержимое выводить именно в него, а потом уже этот поток
 * возвращать обратно (из функции). Операторы сравнения работают просто - проверяют
 * соответствующие элементы в векторах. Пришлось написать простенькие функции,
 * которые возвращают эти самые векторы.
 * */

#include "Name_pairs.h"

int main() {
    try {
        Pairs::Name_pairs obj{};
        obj.read_names();
        obj.read_ages();
        Pairs::Name_pairs obj2 = obj;
        std::cout << obj << std::endl;

        if (obj == obj2) std::cout <<   "Equal"   << std::endl;
        if (obj != obj2) std::cout << "Not equal" << std::endl;

        obj.sort();
        std::cout << obj << std::endl;

        if (obj == obj2) std::cout <<   "Equal"   << std::endl;
        if (obj != obj2) std::cout << "Not equal" << std::endl;

        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}