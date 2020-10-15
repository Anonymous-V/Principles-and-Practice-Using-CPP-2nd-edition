/*
 * Описание задачи:
 * ================
 * Напишет функцию vector<string> split(const string& s, const string& w),
 * возвращающую вектор подстрок аргумента s, разделенных пробельными символами,
 * при условии, что в качестве пробельного символа могут использоваться как
 * "обычные" пробельные символы, так и символы из строки w.
 *
 * Идея реализации:
 * ================
 * Используя фукнцию split из предыдущей задачи можно расширить функционал
 * программы написав новую функцию split, котороая принимает в качестве
 * второго параметра пользовательские разделители.
 *
 * Для начала необходимо заменить пользовательские разделители на "стандартные
 * разделители", т.е. пробелы, а уже потом разделять строку на подстроки.
 * */

#include <iostream>
#include <vector>
#include <sstream>


std::vector<std::string> split(const std::string& s)
// Создать вектор подстрок из строки разделенных пробелами
{
    std::istringstream ist {s};
    std::vector<std::string> sp;

    for (std::string str; ist >> str;)
        sp.push_back(str);
    return sp;
}


void replace_whitespace(std::string& str, const std::string& whitespace)
// Заменяет пробельные символы пользователя на обычные пробелы
{
    for (const char& ch : whitespace) {
        int inx = str.find(ch);
        while (inx != std::string::npos) {  // В случае не вхождения символа ch
                                            // функция find возвращает std::string::npos
            str[inx] = ' ';
            inx = str.find(ch);
        }
    }
}


std::vector<std::string> split(const std::string& s, const std::string& w)
{
    std::vector<std::string> res;
    std::string ss {s};

    replace_whitespace(ss, w);  // Заменить пользовательские пробельные символы
    return split(ss);
}


int main() {
    std::string s {"L;orem ip,sum dolor sit,      amet, cons.ectetur; adip.iscing elit."};
    std::string delims {";,."};

    std::vector<std::string> res { split(s, delims) };
    for (std::string& str : res)
        std::cout << str << std::endl;

    return 0;
}