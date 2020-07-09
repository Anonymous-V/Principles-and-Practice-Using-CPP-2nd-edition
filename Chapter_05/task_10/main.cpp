/*
 * Описание задачи:
 * ================
 * Измените программу из упр. 8 так, чтобы она использовала тип double вместо
 * int. Кроме того, создайте вектор действительных чисел, содержащий N-1 разностей
 * между соседними величинами, и выведите этот вектор на печать.
 *
 * Идея реализации:
 * ================
 * Теперь же условие для цикла ввода не нужно, т.к. значения вводятся типа double.
 * Вектор разности состоит из разности следующего значения вычитанием текущего,
 * т.е. val_diff = nums[i + 1] - nums[i]. На самом деле не стоило создавать
 * вектор разностей, т.к. можно было бы сразу вывести на печать все значения.
 * */

#include "../../std_lib_facilities.h"

int main() {
    try {
        vector <double> nums;
        vector <double> nums_diff;
        int n;

        cout << "Enter the number of summable values:" << endl;
        cin >> n;

        if (n < 0) throw runtime_error("'n' must be positive");

        cout << "Enter several integers( | to end the input)" << endl;
        for (double val; cin >> val;)
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

        for (int i = 0; i < nums.size() - 1; ++i)
            nums_diff.push_back( nums[i + 1] - nums[i] );

        cout << "The sum of the first "
             << n << " numbers (" << out_sum << ")"
             << " is " << sum << endl;

        cout << "Vector of differences:" << endl;
        for (double val : nums_diff)
            cout << val << " ";

        return 0;
    } catch (out_of_range &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown exception" << endl;
    }
}