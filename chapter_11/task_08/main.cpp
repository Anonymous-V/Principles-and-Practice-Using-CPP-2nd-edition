/*
 * Описание задачи:
 * ================
 * Используйте программу из предыдущего упражнения для создания словаря
 * (в качестве альтернативы подходу, описанному в разделе 11.7).
 * Примените ее к многостраничному текстовому файлу, проанализируйте
 * результат и подумайте, можно ли улучшить эту программу, чтобы получить
 * более качественный словарь.
 *
 * Идея реализации:
 * ================
 * По сравнению с предыдущей версией здесь использование string-потока является
 * преимуществом, т.к. при считывании из него строки игнорируются пробелы и нет
 * необходимости в дополнительной обработки строки от пробелов.
 *
 * Также немного изменилась логика работы: теперь сначала считывается вся строка,
 * из нее удаляются символы пунктуации и она добавляется в поток stringstream.
 * После чего происходит считывание из этого потока string-значений. Если слово
 * является сокращением, то оно преобразовывается в полное слово. После чего
 * слово добавляется в вектор. Вектор сортируется и в файл выводится словарь.
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

const std::string puncts {"\".;:()[],?!-"};

const std::vector<std::string> reduction {
        "i'm", "it's", "aren't", "can't", "don't",
        "isn't", "won't", "i'd", "haven't", "we've"};
const std::vector<std::string> reduction_full {
        "i am", "it is", "are not", "cannot", "do not",
        "is not", "will not", "i had", "have not", "we have"
};


void replace_reduction(std::string& s)
// Заменить слова-сокращения на их полный эквивалент
{
    for (int i = 0; i < reduction.size(); ++i)
        if (reduction[i] == s) s = reduction_full[i];
}


bool is_punctuation(char ch)
// Является ли ch символом пунктуации
{
    for (char p : puncts)
        if (p == ch) return true;
    return false;
}


void clear_punctuation(std::string& s)
// Очистить символы пунктуации из строки
// Пропустить апострофы (') и дефисы между букв
{
    for (int i = 0; i < s.length(); ++i) {
        s[i] = tolower(s[i]);
        if (s[i] == '-' && i > 0 && i < s.length() - 1)
            if ( isalpha(s[i - 1]) && isalpha(s[i + 1]) )
                continue;                       // Пропускаем дефисы только находящиеся
        // между буквами, остальные заменяем
        if ( is_punctuation(s[i]) ) s[i] = ' ';
    }
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


    std::istringstream ist;
    std::vector<std::string> dict;

    for (std::string line; getline(ifs, line);) {
        clear_punctuation(line);        // Удаляем из строки символы пунктуации
                                           // за исключением апострофа и дефиса между букв
        ist.str(line);
        for (std::string str; ist >> str;) {
            replace_reduction(str);     // Заменяем слова-сокращения
            dict.push_back(str);
        }
        ist.clear();
    }

    std::sort(dict.begin(), dict.end());

    for (int i = 0; i < dict.size(); ++i)
        if (i == 0 || dict[i] != dict[i - 1])
            ofs << dict[i] << '\n';
}


int main() {
    std::string iname {"input.txt"};
    std::string oname {"output.txt"};

    replace_str(iname, oname);
}