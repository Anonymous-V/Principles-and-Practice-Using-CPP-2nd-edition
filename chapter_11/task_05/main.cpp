/*
 * Описание задачи:
 * ================
 * Напишите программу, считывающую строки и выводящую категории каждого символа
 * в соответствии с правилами, описанными в разделе 11.6. Помните, что один и тот
 * же символ может относиться к разным категориям (например, х - это и буквенный,
 * и буквенно-цифровой символ).
 *
 * Идея реализации:
 * ================
 * Каждый символ может принадлежать нескольким категориям символов,
 * поэтому функция character_type имеет несколько условий проверок.
 * При этом, в главе 11.6 таких проверок существует больше, но их
 * проверять не стоит, т.к. они представляют собой комбинацию из
 * используемых в этой функции.
 * */

#include <iostream>
#include <fstream>


void character_type(std::ofstream& ofs, char ch)
// Определение категории символа
{
    if ( isspace(ch) )  return;   // Пробелы пропускаем
    if ( isalpha(ch) )  ofs << ch << " - alpha" << '\n';             // Буква заглавные и малые
    if ( isdigit(ch) )  ofs << ch << " - number" << '\n';            // Обычное десятичное число
    if ( isxdigit(ch) ) ofs << ch << " - alphanumeric" << '\n';      // Шестнадцатеричное число
    if ( isupper(ch) )  ofs << ch << " - letter is upper" << '\n';   // Буква в верхнем регистре
    if ( islower(ch) )  ofs << ch << " - letter is lower" << '\n';   // Буква в нижнем регистре
    if ( iscntrl(ch) )  ofs << ch << " - control symbol" << '\n';    // Управляющий символ
    if ( ispunct(ch) )  ofs << ch << " - punct symbol" << '\n';      // Не буква, не цифра, не разделитель,
                                                                     // не невидимый управляющий символ
    ofs << '\n';
}


void fill_from_file(std::string& iname, std::string& oname)
// Открытие файлов для ввода и вывода данных
{
    std::ifstream ifs {iname};
    if (!ifs) throw std::runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    std::ofstream ofs {oname};
    if (!ofs) throw std::runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    for (char ch; ifs.get(ch);)
        character_type(ofs, ch);
}


int main() {
    std::string iname {"input.txt"};
    std::string oname {"output.txt"};

    fill_from_file(iname, oname);
}