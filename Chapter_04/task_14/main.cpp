/*
 * Описание задачи:
 * ================
 * Измените программу, описанную в предыдущем упражнении, так, чтобы в нее
 * вводилось число max, а затем найдите все простые числа от 1 до max.
 *
 * Идея реализации:
 * ================
 * Идея та же, что и в предыдущей задача.
 * */

#include "../../std_lib_facilities.h"

int main() {
    vector <int> primes;
    // Параметр
    int p = 2;
    int max_val;

    cout << "Enter the length of the sequence of numbers:" << endl;
    cin >> max_val;

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