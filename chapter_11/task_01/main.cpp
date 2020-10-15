/*
 * Описание задачи:
 * ================
 * Напишите программу, читающую тектовый файл и записывающую его
 * содержимое в новый файл в нижнем регистре.
 *
 * Идея реализации:
 * ================
 * Довольно простенькая программа. Достаточно открыть файлы и в
 * выходной записать данные в нижнем регистре (функция tolower)
 * */

#include <iostream>
#include <fstream>


void fill_from_file(std::string& iname, std::string& oname)
// Копирование содержимое одного файла в другой
// и преобразование в нижный регистр
{
    std::ifstream ifs {iname};  // Открытие входного файла
    if (!ifs) throw std::runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    std::ofstream ofs {oname};  // Открытие выходного файла
    if (!ofs) throw std::runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);


    for (char ch; ifs.get(ch);)
        ofs << char(tolower(ch)); // Преобразовать число в символ и вывести в файл
}


int main() {
    std::string iname;
    std::string oname;

    std::cout << "Enter input file" << std::endl;
    std::cin >> iname;
    std::cout << "Enter output file" << std::endl;
    std::cin >> oname;

    fill_from_file(iname, oname);
}