/*
 * Описание задачи:
 * ================
 * Модифицируйте программу из предыдущего упражнения, чтобы она заменяла
 * сокращения don't словами do not, can't - cannot и т.д.: дефисы внутри
 * слов не трогайте (таким образом, мы получим строку "   do not use
 * the as-if rule "); переведите все символы в нижний регистр.
 *
 * Идея реализации:
 * ================
 * Идея состоит в том, чтобы считывать символы из файла посимвольно (для
 * разграничения пробела и слов. Если считано слово, то его необходимо
 * обработать, а именно: удалить символы пунктуации и перевести слово
 * из сокращенного вида в его полный эквивалент (при необходимости).
 *
 * Также необходимо учесть, что символы дефиса, находящиеся между слов
 * не должны быть удалены. Для этого есть проверка - находится ли символ
 * дефиса между буквами в функции clear_punctuation().
 *
 * Изначально была реализация считывания строк через поток istringstream,
 * т.е. считывалась целая строка getline(ifs, line) в поток istringstream
 * и дальше она обрабатывалась, но мне показалось такое действие
 * избыточным, поэтому отказался от потока istringstream и считывание
 * происходит напрямую из файлового потока. Насколько такое решение
 * является корректным - пока не знаю, но предполагаю, что такое дейсвие
 * лучше реализовывать через string-поток. Возможно, возврат в файловый
 * поток символа более затратный, чем возврат символа в тот же stringstream
 * */

#include <iostream>
#include <fstream>
#include <vector>

const std::string puncts {".;:()[],?!-"};

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

    for (char ch; ifs.get(ch);) {
        if ( !isspace(ch) ) {
            ifs.unget();                // Возвращаем символ ch в поток ifs
            std::string s;
            ifs >> s;
            clear_punctuation(s);    // Убираем символы пунктуации
            replace_reduction(s);    // Заменяем слова сокращения
            ofs << s;
        } else ofs << ch;
    }
}


int main() {
    std::string iname {"input.txt"};
    std::string oname {"output.txt"};

    replace_str(iname, oname);
}