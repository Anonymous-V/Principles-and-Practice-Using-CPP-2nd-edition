/*
 * Описание задачи:
 * ================
 * Напишите две функции, обращающие порядок следования элементов в объекте типа
 * vector<int>. Например, вектор, 1, 3, 5, 7, 9 становится вектором 9, 7, 5, 3, 1.
 * Первая функция, изменяющая порядок следования элементов на противоположный,
 * должна создавать новый объект класса vector, а исходный объект класса vector
 * должен оставаться неизменным. Другая функция должна изменять порядок следования
 * элементов в передаваемом ей векторе без использования других векторов.
 * Указание: воспользуйтесь функцией swap.
 *
 * Идея реализации:
 * ================
 * В программе не стал действовать по описанию задания, т.к. непонятно для чего
 * это необходимо (хотя, если сохранить исходный вектор).
 * Здесь происходит сразу замена местами переменных. Для этой реализации достаточно
 * пройтись половину вектора и поменять местами соответствующие элементы.
 * За вывод также отвечает заголовочный файл из предыдущих программ.
 * */

#include "print_nums.h"

void swap_elems(std::vector <int> &elems)
{
    int cnt = elems.size() / 2;
    for (int i = 0; i < cnt; ++i) {
        std::swap( elems[i], elems[elems.size() - i - 1] );
    }
}

int main() {
    std::vector <int> elems {1, 3, 5, 7, 9, 11};

    swap_elems(elems);
    print("Result", elems);

    return 0;
}