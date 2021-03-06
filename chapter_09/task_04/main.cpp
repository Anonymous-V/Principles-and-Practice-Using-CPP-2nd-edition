/*
 * Описание задачи:
 * ================
 * Посмотрите на "головоломный" пример из раздела 8.4. Корректно расставьте в нем
 * отступы и поясните смысл каждой конструкции. Заметим, что этот код не делает
 * никаких осмысленных операций; это просто "запудривание мозгов".
 *
 * Идея реализации:
 * ================
 * Довольно запутанный код, но получилось разобраться. На каждую строчку комментарий
 * */

#include <iostream>

struct X {                 // Определена структура Х

    void f(int x) {        // Внутри структуры X определена функция f с параметром х

        struct Y {         // Внутри функции определена структура Y
            int f() {      // Внутри структуры Y определена функция f
                return 1;  // Функция f возвращает значение 1
            } // int f()
            int m;         // В структуре Y объявлена переменная m
        }; // struct Y

        int m;             // В функции f объявлена переменная m
        m = x;             // Переменной m присваивается значение параметра x из функции f
        Y m2;              // Объявление переменной типа структуры Y
        return f(m2.f());  // Рекурсивный вызов: всегда вызов происходит со значением 1
                           // который получается из m2.f()
    } // void f(int x)

    int m;                 // В структуре Х объявлена переменная m
    void g(int m) {        // В структуре X определена функция g с параметром m
        if (m) f(m + 2);// Если m истино, то вызовется функция f из структуры X
        else {
            g(m + 2);   // Иначе рекурсивно вызовется функция g
        }
    }   // void g(int m)

    X() { };        // Конструктор структуры X

    void m3() { };  // Определена функция m3

    void main() {   // Определена функция main()
        X a;        // Определена переменна типа структуры X
        a.f(2);  // Вызов функции void f(int x) из структуры X
    } // main()
}; // struct X


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}