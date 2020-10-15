/*
 * Описание задачи:
 * ================
 * Напишите программу, считывающую из файла числа, разделенные пробельными
 * символами, и выводящую их в порядке возрастания по одному числу в строке. Каждое
 * число должно быть записано только один раз, если обнаружится дубликат, то
 * необходимо вывести количество таких дубликатов в строке. Например, результат
 * обработки ввода 7 5 5 7 3 117 5 должен иметь следующий вид:
 * 3
 * 5 3
 * 7 2
 * 117
 *
 * Идея реализации:
 * ================
 * Для реализации программы необходимо считать данные из файла в вектор, сортировать
 * вектор чисел, удалить из него дубликаты и вывести в другой файл.
 *
 * Т.к. операция удаления значений из вектора очень затратная, то было принято
 * решение создать новый вектор (без дубликатов) и присвоить его в исходный вектор.
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


void remove_duplicates(std::vector<int>& nums, std::vector<int>& dublicates)
// Удаление дубликатов (присваивание нового вектора) из вектора чисел
{
    std::vector<int> res;
    if (nums.empty()) return;

    int cnt {1};                            // Количество повторяющихся элементов
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == nums[i + 1]) {
            ++cnt;
            continue;
        }
        res.push_back(nums[i]);
        dublicates.push_back(cnt);
        cnt = 1;
    }
    nums = res;                             // Заменяем вектор с повторяющимися элементами
                                            // на вектор без повторяющихся элементов
}


void dublicates(std::string& iname, std::string& oname)
// Считать данные из файла и вывести в сортированном виде в другой файл
// без повторений и количеством дубликатов каждого числа
{
    std::ifstream ifs {iname};
    if (!ifs) throw std::runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    std::ofstream ofs {oname};
    if (!ofs) throw std::runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);


    std::vector<int> nums;
    for (int num; ifs >> num;) {
        nums.push_back(num);
    }

    std::sort(nums.begin(), nums.end());            // Сортировка вектора
    std::vector<int> dubls;                         // Вектор дубликатов чисел
    remove_duplicates(nums, dubls);           // Удаление дубликатов и возврат вектора
                                                    // с количеством дубликатов каждого числа

    for (int i = 0; i < nums.size(); ++i) {         // Вывод словаря чисел с количеством дубликатов
        ofs << nums[i];
        if (dubls[i] > 1) ofs << " " << dubls[i];
        ofs << '\n';
    }
}

int main() {
    std::string iname {"input.txt"};
    std::string oname {"output.txt"};
    dublicates(iname, oname);
}