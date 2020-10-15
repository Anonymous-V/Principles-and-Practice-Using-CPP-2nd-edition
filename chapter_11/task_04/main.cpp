/*
 * Описание задачи:
 * ================
 * Напишите программу под названием multi_input.cpp, которая предлагает
 * пользователю ввести несколько целых восьмеричных, десятичных и
 * шестнадцатиричных чисел в любом сочетании, используя
 * суффиксы 0 и 0x: правильно интерпретируйте эти числа и преобразуйте
 * их в десятичных вид. Ваша программа должна выводить на экран
 * примерно такие результаты:
 *
 * 0x43 (шестнадцатеричное) превращается в десятичное 67
 * 0123 (восьмеричное)      превращается в десятичное 83
 * 65   (десятичное)        превращается в десятичное 65
 *
 *
 * Идея реализации:
 * ================
 * Идея состоит в том, чтобы заполнить вектор числами в string-значения,
 * затем эти значения присвоить в поток stringstream и вывести в 10-й системе
 * счисления.
 *
 * Для правильного преобразования необходимо понимание, какой формат числа
 * хранится в векторе. Эту задачу выполняет функция get_number_system(),
 * которая принимает string-значение числа и возвращает значение перечисления
 * Number_system.
 *
 * Кроме того, для вывода по столбцам необходимо знать длину максимально
 * длинного числа (точнее сколько знаков в поле это число занимает). Для
 * этого используется функция set_max_length.
 * */

#include <iostream>
#include <vector>
#include <iomanip>


const std::string oct_str {"octal"};
const std::string dec_str {"decimal"};
const std::string hex_str {"hexadecimal"};
int max_length {0};


enum Number_system { // Представление числа в 8-, 10- и 16-ой системе счисления
    oct, dec, hex
};


Number_system get_number_system(std::string& num)
// Вернуть систему счисления числа
{
    if (num.empty()) throw std::runtime_error("Invalid number");

    if (num[0] == '0' && num.length() > 1) {
        if (num[1] == 'x') return Number_system {Number_system::hex}; // Шестнадцатиричная
        else return Number_system {Number_system::oct};               // Восьмеричная
    } else return Number_system {Number_system::dec};                 // Десятичная
}


std::string get_number_system_str(std::string& num)
// Вернуть название системы счисления
{
    Number_system ns {get_number_system(num)};
    switch (ns) {
        case Number_system::oct: return oct_str;
        case Number_system::dec: return dec_str;
        case Number_system::hex: return hex_str;
        default: throw std::runtime_error("Invalid number");
    }
}


void format_out(std::string& num_str, long long int val)
// Форматированный вывод в шестнадцатеричную систему счисления
{
    std::string ns {'(' + get_number_system_str(num_str) + ')'};
    std::cout << std::showbase;         // Вывести основание системы счисления
    std::cout << std::setw(max_length) << std::left << num_str
              << std::setw(14)      << std::left << ns
              << "convert to decimal " << val << std::endl;
}


void change_ist(std::istringstream& ist, std::string& num)
// Сменить режим ввода на другую систему счисления
{
    Number_system ns {get_number_system(num)};
    switch (ns) {
        case Number_system::oct: ist >> std::oct;
        case Number_system::dec: ist >> std::dec;
        case Number_system::hex: ist >> std::hex;
    }
}


void set_max_length(std::vector<std::string>& nums)
// Вычислить максимальную длину строки для корректного вывода
{
    for (std::string& num : nums)
        if (num.length() > max_length)      // max_length - глобальная переменная
            max_length = num.length() + 3;
}


void val_to_dec(std::vector<std::string>& nums)
// Вывод чисел в десятичной системе счисления
{
    std::istringstream ist;         // Поток stringstream для перевода в 10-ю с.с.
    std::string num_system;
    long long int val;
    set_max_length(nums);       // Вычисление максимального отступа
                                   // для выыода по столбцам

    for (std::string& s : nums) {
        change_ist(ist, s); // Изменить поток ввода: 10-, 8-, 16-я с.с.

        ist.str(s);
        ist >> val;

        format_out(s, val);    // Вывод в 10-ой с.с.
        ist.clear();
    }
}


int main() {
    std::cout << "Enter values (oct, dec or hex):" << std::endl;
    std::string num_str;
    std::vector<std::string> nums;

    while(std::cin >> num_str)
        nums.push_back(num_str);

    val_to_dec(nums);
}