/*
 * Класс для хранения даты
 * Дата хранится в формате: (int год, Month::месяц, int день)
 * */

#include <iostream>

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

    private:
        int y;
        Month m;
        int d;
    };

    bool is_date(int y, Month m, int d);      // true для корректной даты
    bool leapyear(int y);                     // true для високосного года
    bool operator == (const Date& a, const Date& b);
    bool operator != (const Date& a, const Date& b);
    std::ostream& operator << (std::ostream& os, const Date& d);
    std::istream& operator >> (std::istream& is, Date& dd);
} // Chrono