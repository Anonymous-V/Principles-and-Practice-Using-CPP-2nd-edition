/*
 * Описание задачи:
 * ================
 * Измените программу из предыдущего упражнения так, чтобы в нее вводилось число
 * max, а затем найдите все простые числа от 1 до max.
 *
 * Идея реализации:
 * ================
 * Идея та же, что и в предыдущей задаче.
 * */

#include "../../std_lib_facilities.h"

// Функция проверки числа на простоту
bool check_primes(int val) {
    int cnt = 0;
    for (int i = 1; i <= val; ++i) {
        if (val % i == 0) ++cnt;
        if (cnt > 2) return false;
    }
    return true;
}

int main() {
    vector <int> primes;
    int max_val;

    cout << "Enter the length of the sequence of numbers:" << endl;
    cin >> max_val;

    for (int i = 2; i <= max_val; ++i) {
        if ( check_primes(i) ) primes.push_back(i);
    }

    for (int val : primes)
        cout << val << " ";

    return 0;
}