/*
 * Описание задачи:
 * ================
 * Определите класс Name_value, хранящий строку и значение. Повторите упр. 19 из
 * главы 4, используя вместо двух векторов вектор vector<Name_value>.
 *
 * Идея реализации:
 * ================
 *
 * */

#include "../../std_lib_facilities.h"

class Name_value {
public:
    Name_value(string name, int score)
        :names(name), scores(score) { };
    string get_name() { return names; };
    int get_score() { return scores; };
private:
    string names;
    int scores;
};

bool check_name(vector <Name_value> names, string name) {
    for (Name_value vec_name : names)
        if (vec_name.get_name() == name) return false;
    return true;
}

int main() {
    vector <Name_value> names;

    // Переменные для ввода имени и значения
    string name;
    int val;

    cout << "Enter a name and positive number." << endl;
    cout << "To finish typing enter \"NoName 0\"" << endl;
    cin >> name >> val;
    while (name != "NoName" || val != 0) {

        if ( check_name(names, name) && val >= 0 )
            names.push_back( Name_value(name, val) );
        else cout << "Error: This name already exist "
                      "or the value is less than zero" << endl;

        cin >> name >> val;
    }

    for (int i = 0; i < names.size(); ++i)
        cout << "Name: "  << names[i].get_name() << "; "
             << "score: " << names[i].get_score() << endl;

    return 0;
}