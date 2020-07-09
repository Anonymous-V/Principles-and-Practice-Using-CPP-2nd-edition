/*
 * Описание задачи:
 * ================
 * Напишите программу, считывающую и сохраняющую ряд целочисленных значений, а
 * затем вычисляющую сумму первых N чисел. Запросите значение N, считайте значения
 * в vector и вычислите сумму первых N значений. Например:
 *
 * Введите количество суммируемых значений:
 * 3
 * Введите несколько целых чисел (| для окончания ввода):
 * 12 23 13 24 15 |
 * Сумма первых 3 чисел (12 23 13) равна 48.
 *
 * Обрабатывайте любые входные данные. Например, если пользователю требуется
 * проссумировать чисел больше, чем сохранено в векторе, выводите соответствующее
 * сообщение.
 *
 * Идея реализации:
 * ================
 * При вводе значений в вектор выход из него производится не только при вводе
 * символа |, но также и других нецелочисленных значений.
 * Для вывода используется переменная out_sum, которая собирает все суммируемые
 * значение вектора.
 * */

#include "../../std_lib_facilities.h"

int main() {
    try {
        vector <int> nums;
        int n;

        cout << "Enter the number of summable values:" << endl;
        cin >> n;

        if (n < 0) throw runtime_error("'n' must be positive");

        cout << "Enter several integers( | to end the input)" << endl;
        for (int val; cin >> val;)
            nums.push_back(val);

        if (n > nums.size())
            throw out_of_range("The 'n' value is too large");

        int sum = 0;
        string out_sum {""};
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            out_sum += to_string(nums[i]);
            // Не добавлять последний пробел к суммируемой последовательности
            if (i + 1 != n) out_sum += " ";
        }

        cout << "The sum of the first "
             << n << " numbers (" << out_sum << ")"
             << " is " << sum << endl;

        return 0;
    } catch (out_of_range &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown exception" << endl;
    }
}