/*
 * Описание задачи:
 * ================
 * Измените порядок следования символов в текстовом файле. Например, строка
 * asdfghjkl примет вид lkjhgfdsa. Предупреждение: не существует реально хорошего,
 * переносимого и эффективного способа чтения файла в обратном направлении.
 *
 * Идея реализации:
 * ================
 * Программа сделана так, чтобы можно было считать данные из файла, сделать обратный
 * порядок символов и записать в тот же файл обработанные данные.
 * Для этого потребовалось завести вектор, который будет хранить все строки из
 * файла.
 *
 * Для создания обратного порядка символов используется фукнция reverse_str,
 * которая посимвольно составляет новые строки в обратном порядке.
 * */

#include <iostream>
#include <vector>
#include <fstream>


void revers_str(std::vector<std::string>& v)
// Записывает строку в обратном порядке и добавляет в вектор
{
    std::vector<std::string> reverse;
    for (std::string& line : v) {
        std::string new_line;
        for (int i = line.size() - 1; i >= 0; --i) {
            new_line += line[i];
        }
        reverse.push_back(new_line);
    }
    v = reverse;
}


void fill_from_vector(std::string& oname, std::vector<std::string>& vect)
// Заполнить файл строками в обратном порядке
{
    std::ofstream ofs {oname};
    if (!ofs) throw std::runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    for (int i = vect.size() - 1; i >= 0; --i)
        ofs << vect[i] << '\n';
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