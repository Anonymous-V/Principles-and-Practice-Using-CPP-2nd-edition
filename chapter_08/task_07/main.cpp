/*
 * Описание задачи:
 * ================
 * Считайте пять имен в вектор vector <string> name, затем предложите пользователю
 * указать возраст названных людей и запишите их в вектор vector <double> age.
 * Затем выведите на печать пять пар (name[i], age[i]). Отсортируйте имена
 * (sort(name.begin(), name.end())) и выведите на экран пары (name[i], age[i]).
 * Сложность здесь заключается в том, чтобы получить вектор age, в котором порядок
 * следования элементов соответствовал бы порядку следования элементов вектора name.
 * Указание: перед сортировкой вектора name создайте его копию и используйте ее
 * для получения упорядоченного вектора age после сортировки вектора name. Затем
 * выполните упражнение снова, разрешив использование произвольного количества имен.
 *
 * Идея реализации:
 * ================
 * Основная идея - это сортировать вектор с возрастами. Это делается с помощью
 * двойного цикла, где берется каждое значение из сортированного вектора и
 * проверяется по всем значениям несортированного вектора имен. При нахождении
 * совпадения меняется местами значения несортированного вектора имен и вектора
 * с возрастами.
 * */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;


// Функция ввода имен в вектор
void inp_name(vector <string> &names)
{
    cout << "Enter names (| to exit):" << endl;
    string name;

    while (name != "|") {
        cin >> name;
        if (name == "|") break;
        names.push_back(name);
    }
}


// Ввод возрастов: предусловие - возраст положительный и вектор не пуст
void inp_age(const vector <string> &names, vector <int> &ages)
{
    int cnt_names = names.size();
    if (cnt_names == 0) throw std::runtime_error("Vector is empty");

    int age;
    for (int i = 0; i < cnt_names; ++i) {
        cout << "Enter age for " << names[i] << ":";
        cin >> age;
        if (age < 0) throw std::runtime_error("Negative age");
        if (!cin) throw std::runtime_error("Invalid argument");
        ages.push_back(age);
    }
}


// Вывод пар (имя - возраст) на экран
void print_pair(const vector <string> &names, const vector <int> &ages)
{
    cout << "( name - age )" << endl;
    for (int i = 0; i < names.size(); ++i)
        cout << "(" << names[i] << " - " << ages[i] << ")" << endl;
    cout << endl;
}


// Сортировка возрастов
void sort_ages(const vector <string> &names, vector <string> &names_copy, vector <int> &ages)
{
    for (int i = 0; i < names.size(); ++i)
        for (int j = 0; j < names_copy.size(); ++j)
            if (names[i] == names_copy[j]) {
                // Поменяться должен не только вектор возрастов, но и копия имен
                std::swap(ages[i], ages[j]);
                std::swap(names_copy[i], names_copy[j]);
                continue;
            }

}


// Обработка данных: сортировка возрастов после сортировки имен
void calculate(vector <string> &names, vector <int> &ages)
{
    vector <string> names_copy = names;
    std::sort(names.begin(), names.end());
    sort_ages(names, names_copy, ages);
}


// Подготовка всех данных и передача на обработку
void prepare(vector <string> &names, vector <int> &ages)
{
    try {
        inp_name(names);
        inp_age(names, ages);

        print_pair(names, ages);
        calculate(names, ages);
        print_pair(names, ages);
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << endl;
    }
}


int main() {
    try {
        vector<string> names;
        vector<int> ages;

        prepare(names, ages);
        return 0;
    } catch (...) {
        std::cerr << "Unknown exception" << endl;
        return 1;
    }
}