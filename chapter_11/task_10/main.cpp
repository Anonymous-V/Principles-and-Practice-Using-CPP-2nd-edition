/*
 * Описание задачи:
 * ================
 * Напишите функцию vector<string> split(const string& s), возвращающую вектор подстрок
 * аргумента s, разделенных пробельными символами.
 *
 * Идея реализации:
 * ================
 * Реализация довольно проста, если использовать поток stingstream. Думаю, в этом
 * случае лучше реализовать другой метод, например, искать пробел через и извлекать
 * подстроку из строки.
 * */

#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& s)
// Создать вектор подстрок из строки разделенных пробелами
{
    std::istringstream ist {s};
    std::vector<std::string> sp;

    for (std::string str; ist >> str;)
        sp.push_back(str);
    return sp;
}


int main() {
    std::string s {"Hello, World! It's a simple text"};
    std::vector<std::string> v {split(s)};

    for (std::string& s : v)
        std::cout << s << std::endl;
    return 0;
}