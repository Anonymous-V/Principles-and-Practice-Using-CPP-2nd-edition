/*
 * Описание задачи:
 * ================
 * Напишите программу, удаляющую из файла все гласные буквы. Например,
 * фраза Once upon a time! принимает вид nc pn tm!. Удивительно часто
 * результат остается вполне удобочитаемым; проверьте это на своих друзьях
 *
 * Идея реализации:
 * ================
 * Для начала необходимо определить строку со всеми гласными буквами.
 * После чего происходит обработка этих символов, а именно:
 * открытие файлов, проверка каждого символа на принадлежность к
 * гласным буквам и удаление их из считанной строки файла.
 *
 * Также необходимо учитывать, что лишние пробелы необходимо удалять
 * из выходной строки. Если этого не сделать, то следующий пример
 * будет выглядеть так: "aaa aa aa aa a aaa." -> "     .", что не
 * является верным решением.
 * */

#include <iostream>
#include <fstream>

const std::string vowels {"aeiouy"};        // Латинские гласные буквы


bool is_lowels(char ch)
// Является ли символ гласной буквой
{
    for (char w : vowels)
        if (tolower(ch) == w) return true;
    return false;
}


void clear_whitespace(std::string& s)
// Убрать лишние пробелы в строке
{
    std::string str;
    for (int i = 0; i < s.length(); ++i) {
        if (str.empty() && s[i] == ' ') continue; // Не учитывать ведущие пробелы
        if ( !(s[i] == ' ' && s[i + 1] == ' ') ) str += s[i]; // Пропустить рядом стоящие пробелы
    }
    s = str;
}


void fill_from_file(std::string& iname, std::string& oname)
// Заполнить выходной файл содержимым входного файла
// не содержащего гласные буквы
{
    std::ifstream ifs {iname};
    if (!ifs) throw std::runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    std::ofstream ofs {oname};
    if (!ofs) throw std::runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    std::string line;
    while (getline(ifs, line)) {
        std::string new_line;
        for (char ch : line)
            if ( !is_lowels(ch) ) new_line += char(ch);
        clear_whitespace(new_line); // Убрать лишние пробелы
        ofs << new_line << '\n';
    }
}


int main() {
    std::string iname = "input.txt";
    std::string oname = "output.txt";
    fill_from_file(iname, oname);
}