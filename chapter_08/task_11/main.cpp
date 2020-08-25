/*
 * Описание задачи:
 * ================
 * Усовершенствуйте функцию print_until_s() из раздела 8.5.2. Протестируйте ее.
 * Какие наборы данных лучше всего подходят для тестирования? Укажите причины.
 * Затем напишите функцию print_until_ss(), которая выводит строки, пока не
 * обнаружит второе вхождение строки аргумента quit.
 *
 * Идея реализации:
 * ================
 * В функции print_until_s параметры передаются по ссылке и константами; исправлен
 * цикл.
 * Функция print_until_ss осуществляет выход по второму вхождению quit. Для этого
 * веден параметр ext, который осуществляет выход, когда значение будет равняться нулю.
 *
 * Какие наборы данных лучше всего подходят для тестирования? Укажите причины.
 * Считаю, что под любые наборы данных можно использовать функцию print_until_s,
 * если переделать под конкретный тип. Конечно, всё зависит от требований к входным
 * данным. Строки можно ограничить, как "quit", числа - нулем, булево значение - false.
 * Все зависит от конкретной задачи.
 * */


#include <iostream>
#include <vector>


// Исправленная функция print_until_s
void print_until_s(const std::vector <std::string> &v, const std::string &quit)
{
    for (std::string s : v) {
        if (s == quit) return;
        std::cout << s << '\n';
    }
}


// Выход из функции по второму вхождению quit
void print_until_ss(const std::vector <std::string> &v, const std::string &quit)
{
    // условие выхода из функции
    int ext = 2;
    for (std::string s : v) {
        if (s == quit) --ext;
        if (!ext) return;
        std::cout << s << '\n';
    }
}


int main() {
    std::vector <std::string> elems {"one", "two", "quit", "quit", "four"};
    std::string quit {"quit"};

    print_until_s(elems, quit);
    print_until_ss(elems, quit);

    return 0;
}