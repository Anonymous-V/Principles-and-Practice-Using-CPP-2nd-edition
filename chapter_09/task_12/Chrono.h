/*
 * Класс для хранения даты
 * Дата хранится в формате: (int год, Month::месяц, int день)
 * */

#include <iostream>
#include <vector>

namespace Chrono {

    // Перечисление месяцев
    enum class Month {
        jan = 1, feb, mar, apr, may, jun,
        jul, aug, sep, oct, nov, dec
    };


    class Date {
    public:
        class Invalid {
        public:
            Invalid(std::string er);   // Передача ошибки в Invalid
            Invalid();                 // Ошибка по умолчанию: неизвестная ошибка
            std::string what() const { return err; }
        private:
            std::string err;           // Информация об ошибке
        };            // Для генерации исключений

        Date(int y, Month m, int d);  // Проверка корректности и инициализации
        Date();                       // Конструктор по умолчанию
        // Копировние по умолчанию нас не устраивает

        // Немодифицируемые операции:
        int day()     const { return d; }
        Month month() const { return m; }
        int year()    const { return y; }
        long int get_zero_days() const { return zero_days; }

        // Модифицирующие операции:
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

    private:
        int y;
        Month m;
        int d;
        long int zero_days;
    };

    bool is_date(int y, Month m, int d);     // true для корректной даты
    long int to_zero_days(int yy, Month mm, int dd);// Перевод даты в дни от даты (01.01.1970)
    bool leapyear(int y);                    // true для високосного года
    int days_in_month(int year, Month month);// Получить количество дней в месяце
    Date next_workday(Date& date);           // Следующий рабочий день (кроме сб, вс)
    int week_of_year(Date& date);            // Номер недели в году

    bool operator == (const Date& a, const Date& b);
    bool operator != (const Date& a, const Date& b);
    std::ostream& operator << (std::ostream& os, const Date& d);
    std::istream& operator >> (std::istream& is, Date& dd);
} // Chrono