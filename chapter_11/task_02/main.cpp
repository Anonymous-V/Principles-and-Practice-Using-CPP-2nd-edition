/*
 * Описание задачи:
 * ================
 * Напишите программу, которая для данного имени файла и слова выводит все строки
 * файла, содержащие это слово, вместе с номерами строк. Указание: getline().
 *
 * Идея реализации:
 * ================
 * Для реализации программы необходимо считать данные в виде строки из входного файла,
 * удалить пунктуацию, т.к. при считывании строки пунктуация будет считываться
 * вместе с ними, например, "hello,". Также необходимо сохранить оригинальную
 * строку, чтобы вывести её на экран.
 * */

#include <iostream>
#include <fstream>
#include <sstream>

const std::string white {".,;?!()"};


bool is_whitespace(char c)
// Является ли символ 'c' спец.символом
{
    for (char w : white)
        if (c == w) return true;
    return false;
}


void clear_whitespace(std::string& line)
// Очистить спец. символы из строки
{
    for (char& i : line)
        if (is_whitespace(i)) i = ' ';
}


void pos_word(std::string& iname, const std::string& search_word)
// Вывести позиции найденных слов и вывести целую строку
{
    std::ifstream ifs {iname};      // Открытие входного файла
    if (!ifs) throw std::runtime_error("Unable to open file " + iname);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    std::stringstream str_stream;
    std::string line, copy_line;
    int inx {1};                    // Индекс первой строки

    while (!ifs.eof()) {

        getline(ifs, line);
        copy_line = line;           // Для вывода оригинальной строки
        clear_whitespace(line);  // удаляем спец.символы: запятая, точка и т.д.
        str_stream.str(line);       // Добавить строку в поток stringstream

        for (std::string word; str_stream >> word;)
            if (word == search_word) {
                std::cout << "Position: " << inx << "; string: " << copy_line << '\n';
                break;              // Выход из внутреннего цикла,
                                    // чтобы не дублировать содержимое
            }

        str_stream.clear();         // Восстанавливаем поток строк
        ++inx;
    }
}


int main() {
    std::string iname;
    std::string search_word;

    std::cout << "Enter input file" << std::endl;
    std::cin >> iname;
    std::cout << "Enter a search word:" << std::endl;
    std::cin >> search_word;

    pos_word(iname, search_word);
}