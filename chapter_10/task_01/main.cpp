/*
 * Описание программы:
 * ===================
 * Напишите программу, вычисляющую сумму всех целых чисел, записанных в файле и
 * разделенных пробелами.
 *
 * Идея реализации:
 * ================
 * Идея состоит в том, чтобы считать файл только с целыми числами. При этом в
 * файле могут находиться данные и других типов: числа с плавающей точкой, строки и т.д.
 *
 * При чтении файла необходимо проверять состояние потока. Если оно окажется "плохим",
 * то поток необходимо вернуть в состояние good() и считать все данные не подходящие
 * под целые числа, затем продолжить чтение целых чисел.
 * */

#include <iostream>
#include <fstream>
#include <vector>


void skip_not_int(std::ifstream& ifs)
// Пропустить все нечисловые символы
{
    if (ifs.fail()) {
        ifs.clear(); // Вернуть поток в состояние good()
        for (char ch; ifs >> ch && isalpha(ch);) { } // Отбросить все не числа
        ifs.unget(); // Вернуть цифру в поток для следующего считывания
    }
}


bool is_int(double val)
// Проверка, является ли число целым
{
    return int(val) - val == 0;
}


void fill_from_file(std::vector<int>& nums, const std::string& file_name)
// Заполнение вектора числами из файла
// Считывает все целые числа, пропуская остальные данные
{
    std::ifstream ifs {file_name}; // Открытие файла для чтения
    if (!ifs) throw std::runtime_error("Unable to open file " + file_name);

    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    double num;
    while (true){
        if (ifs >> num) {
            if (is_int(num)) nums.push_back(num);
        } else skip_not_int(ifs);
        if (ifs.eof()) return; // Условие выхода из цикла
    }
}

int sum_of_vector(std::vector<int>& v)
// Вычисляет сумму вектора
{
    int sum {0};
    for (int val : v)
        sum += val;
    return sum;
}


int main() {
    try {
        std::vector<int> nums;
        fill_from_file(nums, "input.txt");

        for (int val : nums)
            std::cout << val << " ";

        std::cout << '\n';
        std::cout << "Sum of vector: " << sum_of_vector(nums) << std::endl;

        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}