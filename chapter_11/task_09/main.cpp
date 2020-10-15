/*
 * Описание задачи:
 * ================
 * Разделите программу ввода-вывода из раздела 11.3.2 на две: одна программа пусть
 * конвертирует обычный тектовый файл в бинарный, а другая считывает бинарный файл
 * и преобразует его в тектовый. Протестируйте эти программы, сравнивая текстовые файлы
 * до и после преобразования в двоичный файл и обратно
 *
 * Идея реализации:
 * ================
 * Для удобства программа была собрана в одну. Сначала считываются данные из одного
 * файла (текстового) и записываются в бинарный. Затем открывается этот бинарный файл
 * и из него считываются данные и записываются в новый тектовый файл. Можно, конечно,
 * было бы записать конечные данные в первый входной файл.
 *
 * Кстати функции as_bytes в стандартной библиотеке нет, поэтому подключил заголовочный
 * файл std_lib_facilities.h. Хотя, на самом, деле можно было бы разобраться, как работать
 * с бинарными файлами
 * */

#include "../../std_lib_facilities.h"


void create_binary(string& iname, string& oname)
// Считать данные из текстового файла и записать их в бинарный
{
    ifstream ifs {iname};
    if (!ifs) throw runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    ofstream ofs {oname, ios_base::binary};
    if (!ofs) throw runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | ios_base::badbit);

    for (int x; ifs >> x;)
        ofs.write(as_bytes(x), sizeof(int));
}


void create_text(string& iname, string& oname)
// Считать данные из бинарного файла и записать их вс текстовый
{
    ifstream ifs {iname, ios_base::binary};
    if (!ifs) throw runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    ofstream ofs {oname};
    if (!ofs) throw runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | ios_base::badbit);


    for (int x; ifs.read(as_bytes(x), sizeof(int));)
        ofs << x << ' ';
}


int main() {
    string iname {"input.txt"};
    string oname {"output.txt"};
    create_binary(iname, oname);

    string iname2 {"output.txt"};
    string oname2 {"output_new.txt"};
    create_text(iname2, oname2);

    return 0;
}