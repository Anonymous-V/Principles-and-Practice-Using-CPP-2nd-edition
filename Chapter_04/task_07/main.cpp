/*
 * Описание задачи:
 * ================
 * Модифицируйте мини-калькулятор, описанный в упр. 5, так, чтобы он принимал
 * на вход цифры, записанные как в числовом, так и в строковом формате.
 *
 * Идея реализации:
 * ================
 * Цифры вводятся в строковом варианте, т.е. "one" или "1".
 *
 * Сначала проверяется были ли числа введены в обычном (числовом) формате. Для
 * этого используется функция check_number. В ней проверяется условие, что длинна
 * строки равна 1. Если это так, значит, скорее всего, было введено обычное
 * десятичное число. Производится дальнейшая проверка, что действительно это было
 * число, а не другой символ. Если проверка выполняется, то возвращается числовое
 * значение числа (т.к. функция типа int).
 *
 * Дальше проводится проверка на ввод числа в строковом варианте. Здесь необходимо
 * просто пройтись один раз по вектору подготовленных значений.
 *
 * Последняя проверка (if val_one != -1 ...) говорит о том, что были ли два числа
 * введены корректно, либо в числовом формате, либо в строковом, т.е. изменились
 * ли начальные значения -1. Если не изменились, значит введенные значения были
 * введены некорректно.
 * Если проверка пройдена успешно, то выполняется соответствующая операция (конечно,
 * если введена корректно) и выводится результат.
 * */

#include "../../std_lib_facilities.h"

// Функция возвращает значение строкового представления цисла от 0 до 9,
// либо, в случае неудачи, значение -1
int check_number(string str_num) {
    if (str_num.length() == 1)
        if (str_num[0] >= '0' && str_num[0] <= '9')
            return str_num[0] - '0';
    return -1;
}

int main() {
    const vector <string> nums {"zero", "one", "two",
                                "three", "four", "five", "six",
                                "seven", "eight", "nine"};
    // Переменные для ввода чисел (в стровом варианте или числовом)
    string str_num_one, str_num_two;
    string str_out;
    double res = 0;
    char operation;
    int val_one = -1, val_two = -1;

    cout << "Enter a number from 0 to 9 in the string view or"
            "numeric view and the operation sign (+, -, *, /):" << endl;

    cin >> str_num_one >> str_num_two >> operation;

    // Проверка, являются ли строки обычными числами
    val_one = check_number(str_num_one);
    val_two = check_number(str_num_two);

    // Проверка, являются ли строки цифрами в строковом представлении
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == str_num_one) val_one = i;
        if (nums[i] == str_num_two) val_two = i;
    }

    if (val_one != -1 && val_two != -1) {
        switch (operation) {
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
                res = val_one * 1.0 / val_two;
                str_out = "div";
                break;
            default:
                simple_error("I don't know of such an operation");
        }
    } else simple_error("Invalid values entered");

    cout << "The " << str_out << " of "
         << val_one << " and " << val_two
         << " is equal " << res << endl;

    return 0;
}