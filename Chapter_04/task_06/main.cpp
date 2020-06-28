/*
 * Описание задачи:
 * ================
 * Создайте вектор, хранящий десять строковых значений "zero", "one", ...,
 * "nine". Используйте его в программе, преобразующей цифру в соответствующее
 * строковое представление: например, при вводе цифры 7 на экран должна быть
 * выведена строка seven. С помощью этой же программы, используя тот же цикл
 * ввода, преобразуйте строковое представление цифры в числовое: например, при
 * вводе строки seven на экран должно быть выведена цифра 7.
 *
 * Идея реализации:
 * ================
 * В цикле вводятся сначала число, затем строкое представление цисла (не
 * обязательно того же самого). Обычное число сопоставимо со строковым
 * представлением по значению индекса (nums[1] == "one").
 * В случае строк необходимо пройтись по вектору, проверяя все значения.
 * */

#include "../../std_lib_facilities.h"

int main() {
    const vector <string> nums {"zero", "one", "two",
                          "three", "four", "five", "six",
                          "seven", "eight", "nine"};
    // Строковое представление числа
    string str;

    cout << "Enter a number from 0 to 9 and string representation of a number:" << endl;
    for (int val; cin >> val >> str;) {
        // Проверка, что введенное число не выходит за границы вектора
        if (val >= 0 && val < nums.size())
            cout << val << " == " << nums[val] << endl;
        for (unsigned int i = 0; i < nums.size(); ++i) {
            if (str == nums[i]) {
                cout << str << " == " << i << endl;
                break;
            }
        }
    }

    return 0;
}