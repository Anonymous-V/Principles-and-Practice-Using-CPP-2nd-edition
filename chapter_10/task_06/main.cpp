/*
 * Описание задачи:
 * ================
 * Определите класс Roman_int для хранения римских цифр (как чисел типа int) с
 * операторами << и >>. Включите в класс Roman_int функцию as_int(), возвращающую
 * значение типа int, так, чтобы, если объект r имеет тип Roman_int, мы могли
 * написать cout << "Римское " << r << " равно " << r.as_int() << '\n';.
 *
 * Идея реализации:
 * ================
 * Для реализации этой задачи потребовалось сделать следующее:
 * - записать в константные векторы римские символы и их значения
 * - сделать преобразование каждого римского символа в эквивалент арабского числа
 *
 * Алгоритм преобразования римского числа в арабское состоит в следующем:
 * 1. Считать последний символ числа
 * 2. Преобразовать символ в эквивалент арабского числа
 * 3. Произвести проверку:
 *    - если число из п.1 больше или равно предыдущему, то прибавить это число
 *      в общую сумму и предыдущему число присвоить текущее
 *    - если число из п.1 меньше, чем предыдущее, то вычесть его из суммы
 * 4. Повторить алгоритм, пока римского число полностью не преобразовано
 *
 * P.S. При инициализации предыдущее число равняется нулю, т.е. самая малая римская
 * единица - это один.
 * */

#include "Roman.h"


int main() {
    try {
        Roman::Roman_int r{"MMDCXLVIII"};
        std::cout << "Roman " << r << " is equal " << r.as_int() << " " << Roman::to_roman(r.as_int()) << '\n';
        //std::cin >> r;
        //
        // std::cout << r << " = " << r.as_int() << '\n';

        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}