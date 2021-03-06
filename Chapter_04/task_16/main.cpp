/*
 * Описание задачи:
 * ================
 * В заданиях вам было предложено написать программу, которая для определенного
 * ряда чисел определяла бы наибольшее и наименьшее числа в нем. Число, которое
 * повторяется в последовательности наибольшее число раз называется модой.
 * Напишите программу, определяющую моду множества положительных чисел.
 *
 * Идея реализации:
 * ================
 * Необходимо учитывать 3 случая:
 * 1. Моды нет (все числа встречаются по одному разу)
 * 2. Мода в единственном экземпляре
 * 3. Мода встречается 2 и более раз
 *
 * Для решения задачи используется 3 вектора: первый вектор хранит исходные даные;
 * второй вектор необходим для хранения количества наиболее встречающихся чисел;
 * третий вектор (необязательный) хранит значения наиболее встречающихся чисел.
 * После ввода всех чисел необходимо проверить каждое число на совпадение с
 * другими числами и вести счетчик повторяющихся чисел. После того, как число
 * будет проверено необходимо проверить, является ли оно максмимальным и, если
 * оно встречалось более двух раз, то добавить соответствующие значения
 * во второй и третий вектора для дальнейшей проверки.
 * После всех проверок вывести те числа, которые встречались максимальное
 * количество раз (для этого сверяется максимальное значение со значениями из
 * второго вектора).
 * */

#include "../../std_lib_facilities.h"

int main() {
    vector <int> nums;
    vector <int> cnt_modas;
    vector <int> val_modas;
    int cnt, max_val = -1;

    cout << "Enter a sequence of positive numbers:" << endl;
    // Все положительные числа будут храниться в векторе
    for (int val; cin >> val;) {
        if (val >= 0) nums.push_back(val);
        else cout << "Only positive numbers are allowed" << endl;
    }

    for (int i = 0; i < nums.size(); ++i) {
        cnt = 1;
        // Встречавшееся ранее число пропускается
        if (nums[i] == -1) continue;
        for (int j = i + 1; j < nums.size(); ++j) {
            // Проверка, что числа совпадают
            if (nums[i] == nums[j]) {
                ++cnt;
                // Пометка, что число уже проверено
                nums[j] = -1;
            }
        }
        // Поиск максимального количества чисел
        if (max_val < cnt) max_val = cnt;
        // Добавление в массивы количество повторяющихся чисел
        // и самого числа
        if (cnt > 1) {
            cnt_modas.push_back(cnt);
            val_modas.push_back(nums[i]);
        }
        // Пометка текущего числа, как рассмотренного
        nums[i] = -1;
    }

    // Случай, когда мода не была найдена, т.е. числа встречались ноль
    // или один раз
    if (max_val < 2)
        cout << "In the sequence of numbers there no modas" << endl;

    for (int i = 0; i < cnt_modas.size(); ++i) {
        // Вывод всех мод чисел
        if (cnt_modas[i] == max_val)
            cout << "The number " << val_modas[i]
                 << " is a mode of number ("
                 << cnt_modas[i] << ")" << endl;
    }

    return 0;
}