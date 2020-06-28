/*
 * Описание задачи:
 * ================
 * Напишите программу, выполняющую самые простые функции калькулятора. Ваш
 * калькулятор должен выполнять четыре основные арифметические
 * операции - сложение, вычитание, умножение и деление. Программа должна
 * предлагать пользователю ввести три аргумента: два значения типа double и
 * символ операции. Если входные аргументы равны 35.1 24.1 и '+', то программа
 * должна вывести на экран строку "Сумма 35.6 и 24.1 равна 59.7".
 *
 * Идея реализации:
 * ================
 * Ввести необходимые значения в переменные и через switch реализовать
 * необходимые операции. После switch вывести результат.
 *
 * P.S. Так же необходимо учитывать, что деление на ноль запрещено.
 * */

#include "../../std_lib_facilities.h"

int main() {
    double val_one {0}, val_two {0};
    char sym {'+'};
    double res {0};
    // Строка для обозначения операции над числами; используется в выводе
    string str_out;

    cout << "Enter two numbers and an operation:" << endl;
    cin >> val_one >> val_two >> sym;

    switch (sym) {
        case '+':
            res = val_one + val_two;
            str_out = "sum";
            break;
        case '-':
            res = val_one - val_two;
            str_out = "sub";
            break;
        case '*':
            res = val_one * val_two;
            str_out = "mul";
            break;
        case '/':
            if (val_two == 0)
                simple_error("Division by zero is forbidden");
            res = val_one / val_two;
            str_out = "div";
            break;
        default:
            simple_error("I don't know of such an operation");
    }

    cout << "The " << str_out << " of "
         << val_one << " and " << val_two
         << " is equal " << res << endl;

    return 0;
}