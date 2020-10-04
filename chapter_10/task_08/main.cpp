/*
 * Описание задачи:
 * ================
 * Напишите программу, принимающую на вход имена двух файлов и создающую новый
 * файл, в котором за содержимым первого файла следует содержимое второго; иначе
 * говоря, программа должна конкатенировать два файла.
 *
 * Идея реализации:
 * ================
 * Задача довольно тривиальная и состоит в том, чтобы считать данные из файлов в
 * один вектор и записать этот вектор в файл. Либо же, можно создать два вектора
 * и также записать их в один файл, но в этом случае необходимо в выходной поток
 * добавить добавить std::ios_base::app, которое откроет выходной файл и переставит
 * каретку в конец файла.
 * */

#include <iostream>
#include <fstream>
#include <vector>

void fill_from_file(std::vector<std::string>& v, std::string& file_name)
// Заполнить вектор данными из файла
{
    std::ifstream ifs {file_name};
    if (!ifs) throw std::runtime_error("Unable to open file " + file_name);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);


    for (std::string str; ifs >> str;)
        v.push_back(str);
}


void fill_from_vector(std::vector<std::string>& vect, std::string& file_name)
// Заполнить файл из вектора
{
    std::ofstream ofs {file_name};
    if (!ofs) throw std::runtime_error("Unable to create " + file_name);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    for (std::string& str : vect)
        ofs << str << '\n';
}

int main() {

    // Открытие первого входного файла
    std::vector<std::string> v;
    std::string iname_one {"input_one.txt"};
    fill_from_file(v, iname_one);


    // Открытие второго входного файла
    std::string iname_two {"input_two.txt"};
    fill_from_file(v, iname_two);


    // Открытие выходного файла
    std::string oname {"output.txt"};
    fill_from_vector(v, oname);

    return 0;
}