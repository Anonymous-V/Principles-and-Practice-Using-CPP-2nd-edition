/*
 * Описание задачи:
 * ================
 * Переменная типа int может хранить целые числа, не превышающие некоторого
 * максимального числа. Вычислите приближение этого максимального числа с
 * помощью функции fibonacci().
 *
 * Идея реализации:
 * ================
 * Из предыдущего примера цикл заменился на while. Аргумент n теперь используется
 * для количества элементов, которые подходят для типа int из чисел Фибоначчи.
 * Также заменено предусловие - теперь входные параметры X и Y должны быть
 * положительными.
 * */

#include "print_nums.h"


void fibonacci(int x, int y, std::vector <int> &nums, int &n)
{
    // Предусловие: x и y должны быть положительны и не равны нулям
    if (x < 0 || y < 0) throw std::runtime_error("Invalid arguments");
    nums.push_back(x);
    nums.push_back(y);

    n = 0;
    int val = 1;
    int i = 2;
    while (val > 0) {
        val = nums[i - 2] + nums[i - 1];
        if (val > 0) {
            nums.push_back(val);
            ++n;
        }
        ++i;
    }
}


int main() {
    try {
        std::vector<int> nums;
        int x = 1;
        int y = 1;
        int n = 10;

        fibonacci(x, y, nums, n);
        std::cout << "Approximation of a number: " << n << std::endl;
        print("Result", nums);
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}