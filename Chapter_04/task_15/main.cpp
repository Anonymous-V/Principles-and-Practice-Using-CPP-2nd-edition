/*
 * Описание задачи:
 * ================
 * Напишите программу, принимающую на вход число n и находящую первые n
 * простых чисел
 *
 * Идея реализации:
 * ================
 * В данном случае решето Эратосфена не подходит, т.к. неизвестно сколько нужно
 * использовать чисел, чтобы найти первые n простых. Поэтому для данной задачи
 * используется способ, описанный в задаче 11.
 * */

#include "../../std_lib_facilities.h"

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
    int cnt_primes, cnt = 0;
    int step = 2;

    cout << "Enter the number of prime numbers to find:" << endl;
    cin >> cnt_primes;

    while (cnt < cnt_primes) {
        if ( check_primes(step) ) {
            primes.push_back(step);
            ++cnt;
        }
        ++step;
    }

    for (int val : primes)
        cout << val << " ";

    return 0;
}