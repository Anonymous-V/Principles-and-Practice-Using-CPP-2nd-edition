/*
 * Описание задачи:
 * ================
 * Попробуйте вычислить количество зерен риса, запрошенных изобретателем шахмат
 * в упр. 8. Оказывается, что это число настолько велико, что для его точного
 * представления не подходит ни тип int, ни тип double. Чему равно наибольшее
 * количество зерен риса (с использованием переменной типа int). Определите
 * наибольшее количество клеток, для которых еще можно вычислить приближенное
 * количество зерен (с использованием переменной типа double)?
 *
 * Идея реализации:
 * ================
 * Пройтись циклом 64 раза, чтобы посмотреть вместимость значений в тип данных.
 * Экспериментальным путем было выявлено, что тип int вмещает 31 шаг, а тип
 * double 1023 шага (дальше идет значение inf у типа double).
 * */

#include "../../std_lib_facilities.h"

int main() {
    unsigned int max_int_val = 1;
    double max_double_val = 1;
    int step_begin = 0, step_end = 64;
    int step_int = 0, step_double = 64;

    while (step_begin < step_end) {
        max_int_val *= 2;
        max_double_val *= 2;
        ++step_begin;
        if (max_int_val != 0) step_int = step_begin;
        if (max_double_val != 0) step_double = step_begin;

        cout << "Step: " << step_begin << " : "
             << max_int_val << " " << max_double_val << endl;
    }

    cout << endl;
    cout << "Max step for int = " << step_int << '\n'
         << "Max step for double = " << step_double << endl;

    return 0;
}