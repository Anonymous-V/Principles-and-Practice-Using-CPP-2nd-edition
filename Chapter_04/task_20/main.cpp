/*
 * Описание задачи:
 * ===============
 * Измените программу из упр. 19 так, чтобы при вводе имени она выводила
 * соответствующее количество баллов или сообщение "Имя не найдено".
 *
 * Идея реализации:
 * ================
 * Программа и идея остается той же, только теперь вместо вывода всех значений
 * будет выводиться только то, что соответствует запросу или сообщение, что имя
 * не найдено.
 * */

#include "../../std_lib_facilities.h"

bool check_name(vector <string> names, string name) {
    for (string vec_name : names)
        if (vec_name == name) return false;
    return true;
}

int main() {
    vector <string> names;
    vector <int> scores;

    // Переменные для ввода имени и значения
    string name;
    int val;

    cout << "Enter a name and positive number." << endl;
    cout << "To finish typing enter \"NoName 0\"" << endl;
    cin >> name >> val;
    while (name != "NoName" || val != 0) {

        if ( check_name(names, name) && val >= 0 ) {
            names.push_back(name);
            scores.push_back(val);
        } else cout << "Error: This name already exist "
                       "or the value is less than zero" << endl;

        cin >> name >> val;
    }

    // Переменная, с помощью которой будет выводиться сообщение "Имя не найдено"
    bool allow_cout = true;
    // Воспользуемся той же переменной, которой вводились имена
    cout << "Enter the desired name" << endl;
    cin >> name;
    for (int i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            cout << "Name: " << name << "; score: " << scores[i] << endl;
            allow_cout = false;
            // Дальнейшая проверка не важна; выход из цикла
            break;
        }
    }

    if (allow_cout) cout << "Name " << name << " not found" << endl;

    return 0;
}