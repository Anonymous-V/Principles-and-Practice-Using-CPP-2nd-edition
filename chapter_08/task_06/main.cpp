/*
 * Описание задачи:
 * ================
 * Напишите варианты функций из упражения 5 для класса vector <string>
 *
 * Идея реализации:
 * ================
 * На самом деле достаточно заменить тип int на vector, как в этом файле, так
 * и в других местах программы
 * */

#include "print_str.h"

void swap_elems(std::vector <std::string> &elems)
{
    int cnt = elems.size() / 2;
    for (int i = 0; i < cnt; ++i) {
        std::swap( elems[i], elems[elems.size() - i - 1] );
    }
}

int main() {
    std::vector <std::string> elems {"one", "two", "three", "four"};
    swap_elems(elems);
    print("Result", elems);
    return 0;
}