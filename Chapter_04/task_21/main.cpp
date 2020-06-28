/*
 * Описание задачи:
 * ===============
 * Измените программу из упр. 19 так, чтобы при вводе целого числа она выводила
 * имена всех студентов, получивших указанное количество баллов, или сообщение
 * "Баллы не найдены".
 *
 * Идея реализации:
 * ================
 * Программа похожа на упр. 20, за исключением того, что выводиться могут
 * несколько значений. В данном случае достаточно в последнем цикле поправить
 * условие и убрать break.
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
    // Воспользуемся той же переменной, которой вводились значения
    cout << "Enter the desired score" << endl;
    cin >> val;
    for (int i = 0; i < names.size(); ++i) {
        if (scores[i] == val) {
            cout << "Name: " << names[i] << "; score: " << scores[i] << endl;
            allow_cout = false;
        }
    }

    if (allow_cout) cout << "Points " << val << " not found" << endl;

    return 0;
}