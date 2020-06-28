/*
 * Описание задачи:
 * ================
 * Напишите программу, находящую все простые числа между 1 и 100. Для решения
 * этой задачи существует классический метод "Решето Эратосфена". Если этот метод
 * вам неизвестен, поищите его описание в Интернете. Напишите программу,
 * использующую этот метод.
 *
 * Идея реализации:
 * ================
 * 1. Заполнить вектор числами от 2 до n
 * 2. Параметру p присвоить значение 2
 * 3. Удалить (например, присвоить значение ноль) все числа, начиная с значения
 *    p * p с шагом p
 * 4. Найти первое неудаленное число и присвоить его параметру p
 * 5. Повторить действия 3 и 4 пока не будет пройден весь вектор
 * */

#include "../../std_lib_facilities.h"

int main() {
    vector <int> primes;
    // Параметр
    int p = 2;
    const int max_val = 100;

    // Заполнение вектора последовательностью чисел
    // Для дальнейшего удобства использования заполнил вектор от 0 до max_val
    // Если заполнять с 2-х и до max_val, то в дальнейшем нужно учитывать, что
    // вектор будет длинный max_val - 2
    for (int i = 0; i <= max_val; ++i)
        primes.push_back(i);

    // Затираем единицу, т.к. она не является простым цислом.
    primes[1] = 0;
    for (int i = 2; i <= max_val; ++i) {
        p = i;
        if (p == 0) continue;

        for (int j = p * p; j <= max_val; j += p)
            primes[j] = 0;
    }

    for (int i = 0; i <= max_val; ++i)
        if (primes[i] != 0)
            cout << primes[i] << " ";

    return 0;
}