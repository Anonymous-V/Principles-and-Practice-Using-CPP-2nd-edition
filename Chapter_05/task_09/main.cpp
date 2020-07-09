/*
 * Описание задачи:
 * ================
 * Измените программу из упр. 8 так, чтобы она выводила сообщение об ошибке, если
 * результат не может быть представлен в виде значения типа int
 *
 * Идея реализации:
 * ===============
 * Идея реализации осталась той же. Только теперь необходимо вывести сообщение,
 * что вводимые значения должны быть типа int. Для этого в цикле ввода используется
 * условие, что значение является целым. При этом вводить можно не только значения
 * типа int, но и double тоже.
 *
 * В задании говорится, что "результат не может быть представлен в виде int" и,
 * следовало бы, произвести такую проверку в конце после суммирования, но ничего
 * не говорится, что нужно использовать вектор со значениями типа double, поэтому
 * проверка производится при вводе значений в вектор.
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
        for (double val; cin >> val;) {
            if (val - int(val) != 0) throw runtime_error("The value must be of the 'int' type");
            nums.push_back(val);
        }

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