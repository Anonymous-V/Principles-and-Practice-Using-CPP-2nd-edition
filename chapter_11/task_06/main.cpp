/*
 * Описание задачи:
 * ================
 * Напишите программу, заменяющую знаки пунктуации пробелами. Считайте таковыми
 * точку (.), точку с запятой (;), запятую (,), вопросительный знак (?), дефис (-),
 * одинарные кавычки ('). Не изменяйте символы, находящиеся между парами двойных
 * кавычек ("). Например, строка " - don't use the as-if rule." должна принять
 * вид "   don t use the as if rule ".
 *
 * Идея реализации:
 * ================
 * Как и в предыдущих файлах идея и реализация довольно проста - необходимо
 * считать данные из одного файла, удалить знаки пукнтуации и записать измененную
 * строку в другой файл.
 *
 * Для удаления знаков пунктуации необходимо проверять каждый символ в строке со
 * строкой puncts.
 * */

#include <iostream>
#include <fstream>

const std::string puncts {".;,?-'"};


bool is_punctuation(char ch)
// Является ли ch символом пунктуации
{
    for (char p : puncts)
        if (p == ch) return true;
    return false;
}


void replace_str(std::string& iname, std::string& oname)
// Считывание данных из файла и запись в другой файл
// при этом удаляя знаки пунктуации puncts
{
    std::ifstream ifs {iname};
    if (!ifs) throw std::runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    std::ofstream ofs {oname};
    if (!ofs) throw std::runtime_error("Unable to create file " + oname);
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    for (std::string line; getline(ifs, line);) {
        for (char &ch : line)
            if (is_punctuation(ch)) ch = ' ';
        ofs << line << '\n';
    }
}


int main() {
    std::string iname {"input.txt"};
    std::string oname {"output.txt"};

    replace_str(iname, oname);
}