/*
 * Описание задачи:
 * ================
 * Напишите программу, считывающую тексовый файл и записывающую в другой файл
 * количество каждой категории (см. раздел 11.6).
 *
 * Идея реализации:
 * ================
 * Программа сделана на основе задачи 5 этой главы. Только в этом варианте в
 * функции character_type производится множественная проверка символа и
 * результат сразу присваивается в вектор с количеством соответствующих символов
 * */

#include <iostream>
#include <fstream>
#include <vector>


enum Character {
    space, alpha, digit, xdigit, upper,
    lower, cntrl, punct, print
};

const std::vector<std::string> characters_str {
    "spaces", "letters", "numerics", "alphanumerics",
    "letters is upper case", "letters is lower case",
    "control characters", "puncts", "prints"
};


void character_type(std::vector<int>& v, char ch)
// Определение категории символа
{
    if ( isspace(ch) )  ++v[Character::space];   // Пробелы
    if ( isalpha(ch) )  ++v[Character::alpha];   // Буква заглавные и малые
    if ( isdigit(ch) )  ++v[Character::digit];   // Обычное десятичное число
    if ( isxdigit(ch) ) ++v[Character::xdigit];  // Шестнадцатеричное число
    if ( isupper(ch) )  ++v[Character::upper];   // Буква в верхнем регистре
    if ( islower(ch) )  ++v[Character::lower];   // Буква в нижнем регистре
    if ( iscntrl(ch) )  ++v[Character::cntrl];   // Управляющий символ
    if ( ispunct(ch) )  ++v[Character::punct];   // Не буква, не цифра, не разделитель,
                                                 // не невидимый управляющий символ
    if ( isprint(ch) )  ++v[Character::print];   // Выводящиеся на печать символы
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


    std::vector<int> character_cnt (characters_str.size(), 0); // Инициализация вектора
                                                                     // элементами со значениями ноль
    for (char ch; ifs.get(ch);)
        character_type(character_cnt, ch);

    for (int i = 0; i < character_cnt.size(); ++i) {
        ofs << character_cnt[i] << "\t- " << characters_str[i] << '\n';
    }
}


int main() {
    std::string iname {"input.txt"};
    std::string oname {"output.txt"};

    fill_from_file(iname, oname);
}