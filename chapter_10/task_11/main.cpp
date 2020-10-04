/*
 * Описание задачи:
 * ================
 * Напишите программу, вычисляющую сумму всех целых чисел, хранящихся в текстовом
 * файле и разделенных пробелами и словами. Например, строка "bears: 17
 * elephants 9 end" дает результат, равный 26.
 *
 * Идея реализации:
 * ================
 * Идея довольно простая - считывать данные из файла и записывать целые числа в
 * вектор. При этом, пропускать все данные не целые числа.
 * */

#include <iostream>
#include <vector>
#include <fstream>


void print_value(std::vector<int>& nums)
// Вывести значения вектора через пробел
{
    for (int val : nums) std::cout << val << " ";
    std::cout << std::endl;
}


int sum(std::vector<int>& nums)
// Вычислить сумму вектора
{
    int sum {0};
    for (int val : nums) sum += val;
    return sum;
}


bool is_int(double val)
// Проверка, является ли число целым
{
    return int(val) == val;
}


bool is_positive(double val)
// Проверка, является ли число положительным
{
    return val > 0;
}


void fill_from_file(std::vector<int>& nums, std::string& file_name)
// Заполнение вектора числами из файла
// Считывание только положительных целых чисел (т.е. натуральных без нуля) и
// пропуск всех других символов
{
    std::ifstream ifs {file_name};
    if (!ifs) throw std::runtime_error("Unable to open file " + file_name);

    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    double val;
    while (true) {
        ifs >> val;
    
        if (!ifs) { // Случай, когда данные не являются числом
            ifs.clear();
          for (char ch; ifs >> ch && !isdigit(ch);) { }
          if (ifs.eof()) return;
          ifs.unget();
          continue;
        }

        // Проверка, что число положительное и целое
        if (!is_int(val) || !is_positive(val)) continue;

        nums.push_back(val);
    }
}


int main() {
      std::string iname {"input.txt"};
      std::vector<int> nums;  // Вектор для считывания чисел из файла

      fill_from_file(nums, iname);
      print_value(nums);

      std::cout << "Sum of nums: " << sum(nums) << std::endl;
}