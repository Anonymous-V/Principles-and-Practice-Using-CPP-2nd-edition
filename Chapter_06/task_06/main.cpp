/*
 * Описание задачи:
 * ================
 * Напишите программу, проверяющую корректность предложений в соответствии с
 * правилами "английской грамматики" из раздела 6.4.1. Будем считать, что каждое
 * предложение заканчивается точкой, окруженной пробельными символами. Например,
 * фраза birds fly but the fish swim . является предложением, а фразы but birds fly
 * but the fish swim (пропущена точка) и birds fly but the fish swim. (перед точкой
 * нет пробела) - нет. Для каждого введенного предложения программа должна просто
 * отвечать "Да" или "Нет". Указание: не возитесь с лексемами, просто считывайте
 * данные в объект string с помощью оператора >>.
 *
 * Идея реализации:
 * ================
 * Воспользуемся грамматикой из предыдущего упражнения.
 * Чтобы распознать предложение на корректность оно должно обработаться в следующем порядке:
 * Артикль -> Существительное -> Глагол -> Союз. Для них написаны соответствующие функции.
 * Все эти функции возвращают булево значение, т.е. является ли слово корректным в данном
 * предложении. Если нет, то возвращается false и программа завершает свою работу.
 *
 * Т.к. предложение может не содержать артикля, то в функции article() проверяется
 * наличие существительного.
 * Также в функции проверки союза необходима проверка точки, чтобы программа могла выдать
 * верные результаты.
 *
 * В данной реализации есть функция check_word для проверки принадлежности слова к
 * определенной группе (существительные, глаголы и т.д.). Вектора передаются копированием,
 * но лучше было бы передавать их по ссылке.
 *
 * Также добавив значения в вектора можно расширить допустимые значения слов.
 * */

#include "../../std_lib_facilities.h"

class String_token {
public:
    String_token()
        :full(false), buffer("") { };
    string get();
    void putback(string st);
private:
    bool full {false};
    string buffer;
};

string String_token::get() {
    if (full) {
        full = false;
        return buffer;
    }
    string str;
    cin >> str;
    return str;
}

void String_token::putback(string st) {
    if (full) error("putback() into a full buffer");
    buffer = st;
    full = true;
}

String_token ts;

const vector <string> article_vec {"the"};
const vector <string> noun_vec {"birds", "fish", "C++"};
const vector <string> verb_vec {"rules", "fly", "swim"};
const vector <string> conjuct_vec {"and", "or", "but"};

bool check_word(const vector <string> vect, string word) {
    for (string str : vect) {
        if (str == word) return true;
    }
    return false;
}

bool article();


bool conjunction() {
    string str = ts.get();
    // Проверка, что слово является союзом
    if ( check_word(conjuct_vec, str) ) return article();
    else if (str == ".") {
        ts.putback(str);
        return true;
    }
    else return false;
}

bool verb() {
    string str = ts.get();
    // Проверка, что слово является глаголом
    if ( check_word(verb_vec, str) ) return conjunction();
    else return false;
}

bool noun() {
    string str = ts.get();
    // Проверка, что слово является существительным
    if ( check_word(noun_vec, str) ) return verb();
    else return false;
}


bool article() {
    string str = ts.get();
    // Проверка, что слово является артиклем
    if ( check_word(article_vec, str) ) return noun();
    // Проверка, что слово является существительным
    else if ( check_word(noun_vec, str) ) {
        ts.putback(str);
        return noun();
    }
    else return false;
}

int main() {
    try {
        bool res{true};
        cout << "Enter sentence: " << endl;
        while (res) {
            string str = ts.get();

            if (str == ".") {
                cout << "Yes" << endl;
                break;
            } else ts.putback(str);

            res = article();
            if (!res) {
                cout << "No" << endl;
                break;
            }
        }
    }
    catch (...) {
        cerr << "Unknown exception" << endl;
    }

    return 0;
}