/*
 * Описание задачи:
 * ================
 * Напишите функцию, принимающую аргумент типа vector <string> и возвращающую объект
 * типа vector <int>, содержащий количество символов в каждой строке. Кроме того,
 * найдите самую короткую и самую длинную строки, а также лексикографически первую
 * и последнюю строки. Сколько отдельных функций вы использовали бы для решения
 * этих задач? Почему?
 *
 * Идея реализации:
 * ================
 * В этой задаче было использовано 5 функций (за исключением функции вывода
 * print_elems):
 * 1. Вычисление длин строк
 * 2. Поиск самой короткой строки
 * 3. Поиск самой длинной строки
 * 4. Поиск строки лексикографически первой
 * 5. Поиск строки лексикографически последней
 *
 * Это сделано по той причине, что каждая функция должна выполнять только одно
 * вычисление, как говорилось в предыдущих главах. Если же функцция выполняет
 * несколько действий, то такая функция реализована неверно.
 * Также можно было бы разделить функцию main() на две отдельные функции и вынести
 * код вычислений, но в этом случае необходимо было бы реализовать структуру struct
 * или передавать значения по ссылке, что не очень удобно.
 * Кроме того, функции вычисления можно вынести в заголовочный файл.
 * */


#include <iostream>
#include <vector>

using std::vector;
using std::string;


// Вычисления длин строк
vector <int> size_elems(const vector <string> &elems)
{
    vector <int> elems_size {};
    for (string str: elems)
        elems_size.push_back(str.size());

    return elems_size;
}


// Поиск самой короткой строки
string min_str(const vector <string> &elems)
{
    if (elems.empty()) return "Vector is empty";

    string mx_str = elems[0];
    for (string str : elems)
        if (str.size() < mx_str.size()) mx_str = str;

    return mx_str;
}


// Поиск самой длинной строки
string max_str(const vector <string> &elems)
{
    if (elems.empty()) return "Vector is empty";

    string mn_str = elems[0];
    for (string str : elems)
        if (str.size() > mn_str.size()) mn_str = str;

    return mn_str;
}


// Поиск строки лексикографически первой
string first_str(const vector <string> &elems)
{
    if (elems.empty()) return "Vector is empty";

    string f_str = elems[0];
    for (string str : elems)
        if (str < f_str) f_str = str;

    return f_str;
}


// Поиск строки лексикографически последней
string last_str(const vector <string> &elems)
{
    if (elems.empty()) return "Vector is empty";

    string l_str = elems[0];
    for (string str : elems)
        if (str > l_str) l_str = str;

    return l_str;
}


// Вывод строк и их размеров
void print_elems(const vector <string> &elems, const vector <int> &elems_size)
{
    for (int i = 0; i < elems.size(); ++i)
        std::cout << elems[i] << " " << elems_size[i] << std::endl;
}


int main() {
    vector <string> elems {"one", "two", "three", "four", "five"};
    vector <int> elems_size {};

    elems_size = size_elems(elems);
    string mn_str = min_str(elems);
    string mx_str = max_str(elems);
    string f_str = first_str(elems);
    string l_str = last_str(elems);
    print_elems(elems, elems_size);

    std::cout
            << "Min str:\t"   << mn_str << '\n'
            << "Max str:\t"   << mx_str << '\n'
            << "First str:\t" << f_str  << '\n'
            << "Last str:\t"  << l_str  << '\n';

    return 0;
}