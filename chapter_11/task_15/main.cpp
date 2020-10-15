/*
 * Описание задачи:
 * ================
 * Напишите программу, считывающую из файла числа, разделенные пробельными символами,
 * и выводящую в другой файл числа, используя научный формат и точность, равную
 * восьми, в четырех полях по двадцать символов в строке.
 *
 * Идея реализации:
 * ================
 * Реализация допольно простая. Необходимо настроить поток вывода и учесть
 * переносы строк, когда значений будет 4 цифры в одной строке
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


void write_value(std::ofstream& ofs, double num)
// Вывод значений в файл в 4 столбца по 20 символов в строке
{
    ofs << std::scientific
        << std::setprecision(8)
        << std::setw(20)
        << std::left
        << num;
}


void to_table(std::string& iname, std::string& oname)
// Вывод значений из файла в виде таблицы с 4-мя столбцами
{
    std::ifstream ifs {iname};
    if (!ifs) throw std::runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    std::ofstream ofs {oname};
    if (!ofs) throw std::runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    int inx {0};
    for (double num; ifs >> num;) {
        write_value(ofs, num);
        ++inx;
        if (inx % 4 == 0) ofs << '\n';
    }
}


int main() {
    std::string iname {"input.txt"};
    std::string oname {"output.txt"};

    to_table(iname, oname);
}