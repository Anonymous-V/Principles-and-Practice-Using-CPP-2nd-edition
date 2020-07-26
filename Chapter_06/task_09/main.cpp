/*
 * Описание задачи:
 * ================
 * Напишите программу, считывающую цифры и составляющую из них целые числа.
 * Например, число 123 считывается как последовательность символов 1, 2 и 3.
 * Программа должна вывести на экран сообщение "123 - это 1 сотня, 2 десятки и
 * 3 единицы". Число должно быть выведено как значение типа int. Обрабатывайте
 * числа, состоящие из одной цифры, двух, трех и четырех цифр. Указание: для того,
 * чтобы получить число 5 из символа '5', вычтите из него символ '0', иначе
 * говоря, '5' - '0' == 5.
 *
 * Идея реализации:
 * ================
 * При считывании символов необходимо уделить внимание тому факту, что:
 * 1. Символы должны быть числами, т.е. при преобразовании являлись числами
 * 2. Их количество должно быть не более LENGTH_NUM, т.е. четырех
 * Для этого в цикле считываются символы и сразу проверяются на наличие чисел.
 * Если символ не является числом, то проиходит выход из цикла и производятся
 * дальнейшие вычисления.
 *
 * Т.к. в векторе числа хранятся в символьном представление числа, то для того, чтобы
 * преобразовать все цифры в единое число, необходимо символ преобразовать в число,
 * т.е. sym - '0' и умножить на 1, 10, и т.д. (в зависимости от разряда),
 * сложенное с предыдущим значением.
 *
 * Для вывода числа с разрядами используются 2 вектора: с символами-числами и
 * разрядами. Для того, чтобы верно выводили разряды используется разница между
 * длинами векторов и прибавляется i-е значение символа.
 * */

#include "../../std_lib_facilities.h"

// Функция проверки символа на число
bool is_num(char sym) {
    int num = sym - '0';
    return num >= 0 && num <= 9;
}

int main() {
    try {
        // Вектор для хранения символов-чисел
        vector<char> nums;
        // Максимальная длина числа
        const int LENGTH_NUM = 4;
        // Вектор для хранения числовых единиц измерения
        vector <string> measure {"thousand", "hundred", "ten", "unit"};

        cout << "Enter a number up to " << LENGTH_NUM << " digits long:" << endl;
        cout << "Enter any other character to exit" << endl;
        // Считываются символы в вектор
        for (char sym; cin >> sym;) {
            // Проверка, что символ является числом
            bool check_sym = is_num(sym);
            // Если символ число, то он добавляется в вектор
            if (check_sym) nums.push_back(sym);
            // иначе происходит выход из цикла
            else break;
        }

        // Проверка, что количество символов в векторе не больше LENGTH_NUM
        if (nums.size() > LENGTH_NUM) throw length_error("Too big number");
        // Проверка, было ли введено хотя бы одно число
        if (nums.size() == 0) throw length_error("There is no numbers");

        // Формирование число из вектора символов-чисел
        int p = 1;
        int res_num = 0;
        for (int i = (nums.size() - 1); i >= 0; --i) {
            res_num = res_num + (nums[i] - '0') * p;
            p *= 10;
        }

        // Вывод чисел по разрядам
        cout << res_num << " - is ";
        for (int i = 0; i < nums.size(); ++i) {
            cout << nums[i] << " " << measure[measure.size() - nums.size() + i] << " ";
        }

        return 0;
    } catch (length_error &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}