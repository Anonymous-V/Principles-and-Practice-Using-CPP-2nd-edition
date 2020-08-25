/*
 * Описание задачи:
 * ================
 * Напишите функцию maxv(), возвращающую наибольший элемент вектора, передаваемого
 * в качестве аргумента.
 *
 * Идея реализации:
 * ================
 * Алгоритм довольно прост - реализовать ввод чисел в вектор, затем пройтись по
 * всему вектору, проверяя максимальный элемент.
 * Можно было бы реализовать в виде залоголочного файла и использовать в следующей
 * задаче, но там немного другой алгоритм будет использоваться.
 * */

#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int maxv(const vector <int> &elems)
{
    if (elems.empty()) throw std::runtime_error("Vector is emtpy");

    int max = elems[0];
    for (int elem : elems)
        if (max < elem) max = elem;
    return max;
}

void inp_elems(vector <int> &v)
{
    int val;
    cout << "Enter nums (any sym to exit):" << endl;
    while (cin) {
        cin >> val;
        if (cin) v.push_back(val);
    }
}

int main() {
    try {
        vector<int> nums;

        inp_elems(nums);
        int max_val = maxv(nums);

        cout << "Max: " << max_val << endl;
        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << endl;
        return 1;
    }

    return 0;
}