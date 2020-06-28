/*
 * Описание задачи:
 * ===============
 * Напишите программу, в которую сначала вводится набор пар, состоящих из имени
 * и значения, например, Joe 17 и Barbara 22. Для каждой пары занесите имя в
 * вектор names, а число - в вектор scores (в соответствующие позиции, так что
 * если names[7] == "Joe, то scores[7] == 17. Прекратите ввод, встретив строку
 * ввода NoNames 0. Убедитесь, что каждое имя единственное, и выведите сообщение
 * об ошибке, если имеется имя, введенное дважды. Выведите на печать все пары
 * (имя, баллы) под одной в строке.
 *
 * Идея реализации:
 * ================
 * При вводе нового значения проверяется, что имя не содержится дважды. Для этого
 * проверяется введенное имя со всеми значениями векторе в функции check_name.
 * Если есть совпадения, то выводится сообщение об ошибке (в данном случае просто
 * сообщение, что имя уже существует; некорректно прекращать программу из-за
 * неверного значения).
 * Так же учитывается баллы при вводе - они не должны быть отрицательными.
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

    for (int i = 0; i < names.size(); ++i)
        cout << "Name: " << names[i] << "; score: " << scores[i] << endl;

    return 0;
}