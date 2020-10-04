/*
 * Описание задачи:
 * ================
 * Напишите программу, принимающую на вход два файла, содержащие лексикографически
 * упорядоченные слова, разделенные пробелами, и объедините их, сохранив упорядочение.
 *
 * Идея реализации:
 * ================
 * Самый тривиальный случай объединить два отсортированных файла - это считать всё в один вектор,
 * произвести сортировку и вывести в файл. Этот случай довольно трудозатратный, а именно,
 * сортировка вектора.
 * Вместо этого реализован другой метод - через цикл происходит сравнение считанных значений
 * из обоих файлов и сравниваются между собой и меньшее значение добавляется в итоговый файл.
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


void merge_sorted_vectors(std::vector<std::string>& merged,
                          std::vector<std::string>& v1,
                          std::vector<std::string>& v2)
// Объединение отсортированных векторов
{
    int inx_one = 0,    // Индекс первого вектора
        inx_two = 0;    // Индекс второго вектора
    bool access_v1 {inx_one < v1.size()}; // Не исчерпан ли первый вектор
    bool access_v2 {inx_two < v2.size()}; // Не исчерпан ли второй вектор

    while (access_v1 || access_v2) {

        if (access_v1) { // Означает, что из первого вектора считаны не все данные
            if (v1[inx_one] <= v2[inx_two] || !access_v2) { // Строки меньше или вектор 2 исчерпан
                merged.push_back(v1[inx_one]);
                access_v1 = inx_one < v1.size() - 1;
                if (access_v1) ++inx_one; // Дополнительная проверка, чтобы в дальнейшем
                                          // не было выхода за диапазон
            }
        }

        // Аналогично коду выше
        if (access_v2) {
            if (v1[inx_one] >= v2[inx_two] || !access_v1) {
                merged.push_back(v2[inx_two]);
                access_v2 = inx_two < v2.size() - 1;
                if (access_v2) ++inx_two;
            }
        }

    }
}


int main() {

    // Открытие первого входного файла
    std::vector<std::string> v1;
    std::string iname_one {"input_one.txt"};
    fill_from_file(v1, iname_one);


    // Открытие второго входного файла
    std::vector<std::string> v2;
    std::string iname_two {"input_two.txt"};
    fill_from_file(v2, iname_two);


    std::vector<std::string> v3;
    merge_sorted_vectors(v3, v1, v2); // Объединение отсортированных векторов

    // Открытие выходного файла
    std::string oname {"output.txt"};
    fill_from_vector(v3, oname);

    return 0;
}