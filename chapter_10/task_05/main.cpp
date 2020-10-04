/*
 * Описание задачи:
 * ================
 * Напишите функцию print_year(), упомянутую в разделе 10.11.2.
 *
 * Идея реализации:
 * ================
 * Здесь написана не только функция, выводящая результат, но и вся программа,
 * описанная в главе.
 * Функция print_year() выводит информацию в структурированном виде. Результат
 * представлен в файле .txt. Замечу, что функция print_year() выводит только
 * года, остальные данные (месяцы, дни, данные о часах и температурах) выводят
 * соответствующие функции: print_month() и print_day().
 * */

#include <iostream>
#include <vector>
#include <fstream>


const int not_a_reading = -7777; // Ниже абсолютного нуля
const int not_a_month = -1;
constexpr int implausible_min = -200;
constexpr int implausible_max = 200;
const std::vector<std::string> month_input_tb1 = {
        "jan", "feb", "mar", "apr", "may", "jun",
        "jul", "aug", "sep", "oct", "nov", "dec"
};
const std::vector<std::string> month_print_tb1 = {
        "January", "February", "March", "April",
        "May", "June", "July", "August", "September",
        "October", "November", "December"
};


struct Day {
    bool available {false};           // Обозначает наличие данных в данном дне
    int day;                          // Текущий день
    std::vector<double> hour {std::vector<double>(24, not_a_reading)};
};

struct Month {                        // Месяц
    int month {not_a_month};          // [0,11] (январю соответствует 0)
    std::vector<Day> day {32};     // [1,31] по одному вектору на день
};

struct Year {                         // Год состоит из месяцев
    int year;                         // Положительное значение
    std::vector<Month> month {12}; // [0,11] (январю соответствует 0)
};

struct Reading {
    int day;
    int hour;
    double temperature;
};

std::string int_to_month(int i);   // Объявление функции


void end_of_loop(std::istream& ist, char term, const std::string& message)
// Проверка корректности окончания записи данных
{
    if (ist.fail()) { // Используем term как символ
                      // завершения ввода и/или разделитель
        ist.clear();
        char ch;
        if (ist >> ch && ch == term) return;    // Все хорошо
        throw std::runtime_error(message);
    }
}


/*
 * --------------------------------------------------------------------------------
 * Структурные вывод данных в файл
 * --------------------------------------------------------------------------------
 * */


void print_day(std::ofstream& ost, Day& d)
{
    ost << "    Day " << d.day << '\n';
    for (int i = 0; i < d.hour.size(); ++i)
        if (d.hour[i] != not_a_reading)
            ost << "      " << i << " " << d.hour[i] << '\n';
}


void print_month(std::ofstream& ost, Month& m)
{
    ost  << "  Month " << int_to_month(m.month) << '\n';
    for (Day& d : m.day)
        if (d.available)
            print_day(ost, d);
}


void print_year(std::ofstream& ost, Year& y)
{
    ost << "Year " << y.year << '\n';
    for (Month& m : y.month)
        if (m.month != not_a_month)  // Не записывать в файл "пустые" данные месяца
            print_month(ost, m);
    ost << '\n';
}


/*
 * --------------------------------------------------------------------------------
 * Вспомогательные функции:
 * - проверка валидности дней
 * - преобразование из числа в месяц и обратно
 * --------------------------------------------------------------------------------
 * */


bool is_valid(const Reading& r)
// Грубая проверка
{
    if (r.day  < 1 || 31 < r.day) return false;
    if (r.hour < 0 || 23 < r.hour) return false;
    if (r.temperature < implausible_min ||
        implausible_max < r.temperature)
        return false;
    return true;
}


int month_to_int(std::string& s)
// Является ли s названием месяца? Если да, возвращаем
// индекс в диапазоне [0,11], в противном случае - -1
{
    for (int i = 0; i < 12; ++i)
        if (month_input_tb1[i] == s) return i;
    return -1;
}


std::string int_to_month(int i)
// Месяц в диапазоне [0, 11]
{
    if (i < 0 || 12 <= i) throw std::runtime_error("Invalid index of month");
    return month_print_tb1[i];
}


/*
 * --------------------------------------------------------------------------------
 * Перегрузка операторов ввода и вывода для файлов
 * --------------------------------------------------------------------------------
 * */


std::istream& operator >> (std::istream& is, Reading& r)
// Считываемт показания температуры из потока is в r
// Формат: ( 3 4 9.7 )
// Проверяем формат, но не корректность данных
{
    char ch1;
    if (is >> ch1 && ch1 != '(') { // Может ли это быть Reading?
        is.unget();
        is.clear(std::ios_base::failbit);
        return is;
    }

    char ch2;
    int d;
    int h;
    double t;
    is >> d >> h >> t >> ch2;
    if (!is || ch2 != ')')
        throw std::runtime_error("Invalid record"); // Некорректная запись
    r.day = d;
    r.hour = h;
    r.temperature = t;
    return is;
}


std::istream& operator >> (std::istream& is, Month& m)
// Считываем объект класса Month из потока is в объект m
// Формат: { month feb ... )
{
    char ch = 0;
    if (is >> ch && ch != '{') {
        is.unget();
        is.clear(std::ios_base::failbit); // Ошибка ввода Month
        return is;
    }

    std::string month_marker;
    std::string mm;
    is >> month_marker >> mm;
    if (!is || month_marker != "month")
        throw std::runtime_error("Wrong start of Month");
    m.month = month_to_int(mm);

    Reading r;
    int duplicates = 0;
    int invalids = 0;
    for (Reading r; is >> r;) {
        if (is_valid(r)) {
            if (m.day[r.day].hour[r.hour] != not_a_reading)
                ++duplicates;
            m.day[r.day].hour[r.hour] = r.temperature;

            m.day[r.day].available = true;
            m.day[r.day].day = r.day;
        }
        else ++invalids;
    }

    if (invalids)
        throw std::runtime_error("Invalid data in Month, total "
                                + std::to_string(invalids));
    if (duplicates)
        throw std::runtime_error("Repeated reading in Month, total "
                                + std::to_string(duplicates));
    end_of_loop(is, '}', "Wrong end of Month");
    return is;
}


std::istream& operator >> (std::istream& is, Year& y)
// Считываем объект класса Year из потока is в объект y
// Формат: { year 1972 ... }
{
    char ch;
    is >> ch;
    if (ch != '{') {
       is.unget();
       is.clear(std::ios_base::failbit);
       return is;
    }

    std::string year_marker;
    int yy;
    is >> year_marker >> yy;
    if (!is || year_marker != "year")
        throw std::runtime_error("Wrong start of Year");
    y.year = yy;
    while (true) {
        Month m; // Каждый раз создаем новый объект m
        if (!(is >> m)) break;
        y.month[m.month] = m;
    }

    end_of_loop(is, '}', "Wrong end of Year");
    return is;
}


/*
 * --------------------------------------------------------------------------------
 * Функция начала работы:
 * - открытие файлов ввода и вывода
 * - чтение произвольного количества лет из файла
 * - вывод количества считанных лет
 * - вывод всех считанных данных в файл
 * --------------------------------------------------------------------------------
 * */


int main() {
    // Открываем файл ввода
    std::cout << "Enter input file name" << std::endl;
    std::string iname {"input.txt"};
    //std::cin >> iname;
    std::ifstream ist {iname};
    if (!ist) throw std::runtime_error("Unable to open input file " + iname);

    // Генерация исключения в случая состояние bad()
    ist.exceptions(ist.exceptions() | std::ios_base::badbit);

    // Открываем файл вывода
    std::cout << "Enter output file name" << std::endl;
    std::string oname {"output.txt"};
    //std::cin >> oname;
    std::ofstream ost {oname};
    if (!ost) throw std::runtime_error("Unable to open output file " + oname);

    // Чтение произвольного количества лет
    std::vector<Year> ys;
    while (true) {
        Year y;     // На каждой итерации получаем вновь
                    // инициализированный объект типа Year
        if (!(ist >> y)) break;
        ys.push_back(y);
    }

    std::cout << "Read out " << ys.size() << " annual records" << std::endl;

    for (Year& y : ys) print_year(ost, y);
    return 0;
}