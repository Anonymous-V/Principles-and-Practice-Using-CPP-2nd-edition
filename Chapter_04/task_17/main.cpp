/*
 * Описание задачи:
 * ================
 * Напишите программу, определяющую наименьшее и наибольшее значения, а также
 * моду последовательности строк типа string.
 *
 * Идея реализации:
 * ================
 * Идея та же самая, что и в предыдущей задачи.
 * */

#include "../../std_lib_facilities.h"

int main() {
    vector <string> strs;
    vector <int> cnt_modas;
    vector <string> val_modas;
    int cnt, max_val = -1, min_val;

    cout << "Enter a sequence of string:" << endl;
    // Все положительные числа будут храниться в векторе
    for (string val; cin >> val;) {
        strs.push_back(val);
    }

    // Присваивание максимального значения (длины вектора)
    // для корректного вычисления минимального
    min_val = strs.size();

    for (int i = 0; i < strs.size(); ++i) {
        cnt = 1;
        // Встречавшееся ранее число пропускается
        if ( strs[i].empty() ) continue;
        for (int j = i + 1; j < strs.size(); ++j) {
            // Проверка, что строки совпадают
            if (strs[i] == strs[j]) {
                ++cnt;
                // Пометка, что строка уже проверена
                strs[j] = "";
            }
        }
        // Поиск максимального количества строк
        if (max_val < cnt) max_val = cnt;
        // Поиск минимальной строки
        if (min_val > cnt) min_val = cnt;
        // Добавление в массивы количество повторяющихся
        // строк и самой строки
        if (cnt > 1) {
            cnt_modas.push_back(cnt);
            val_modas.push_back(strs[i]);
        }
        // Пометка текущей строки, как рассмотренного
        strs[i] = "";
    }

    // Случай, когда мода не была найдена, т.е. строка
    // встречались ноль или один раз
    if (max_val < 2)
        cout << "In the sequence of strings there no modas" << endl;

    for (int i = 0; i < cnt_modas.size(); ++i) {
        // Вывод всех мод строк
        if (cnt_modas[i] == max_val)
            cout << "The string \"" << val_modas[i]
                 << "\" is a mode of strings ("
                 << cnt_modas[i] << ")" << endl;
    }

    cout << "Min value: " << min_val << endl;

    system("pause");

    return 0;
}