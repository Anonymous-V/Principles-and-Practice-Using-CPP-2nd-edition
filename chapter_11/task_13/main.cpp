/*
 * Описание задачи:
 * ================
 * Измените порядок следования слов (определенные как строки, разделенные
 * пробелами). Например, строка Norwegian Blue parrot пример вид parrot Blue
 * Norwegian. Можете считать, что все строки из файла могут поместиться в
 * памяти одновременно.
 *
 * Идея реализации:
 * ================
 * Для решения этой задачи использовалась предыдущая с некоторыми доработками,
 * а именно, изменен немного код и дописана фукнция rev, которая рекурсивно
 * обрабатывает строку, создавая новую строку в обратном порядке.
 * */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


std::string rev(std::istringstream& ist)
// Записать строку в обратном порядке (по словам)
{
    std::string st;
    ist >> st;
    if (!ist) return "";            // Условие выхода из функции
    return rev(ist)  + st + ' ';
}


void revers_str(std::vector<std::string>& v)
// Записывает строку в обратном порядке и добавляет в вектор
{
    std::vector<std::string> reverse;
    std::istringstream ist;

    for (std::string& line : v) {
        ist.str(line);
        reverse.push_back( rev(ist) );
        ist.clear();
    }
    v = reverse;
}


void fill_from_vector(std::string& oname, std::vector<std::string>& vect)
// Заполнить файл строками в обратном порядке
{
    std::ofstream ofs {oname};
    if (!ofs) throw std::runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    for (std::string& line : vect)
        ofs << line << '\n';
}


void fill_from_file(std::string& iname, std::vector<std::string>& vect)
// Считать данные из файла
{
    std::ifstream ifs {iname};
    if (!ifs) throw std::runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    for (std::string line; getline(ifs, line);)
        vect.push_back(line);
}


int main() {
    std::string iname {"input.txt"};
    std::string oname {"output.txt"};
    std::vector<std::string> full_file;

    fill_from_file(iname, full_file);
    revers_str(full_file);
    fill_from_vector(oname, full_file);

    return 0;
}