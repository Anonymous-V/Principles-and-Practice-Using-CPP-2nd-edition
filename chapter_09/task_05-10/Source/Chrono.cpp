#include "../Header/Chrono.h"

namespace Chrono {
    // Определение класса-члена:
    Date::Invalid::Invalid(std::string er) :err{er} { };
    Date::Invalid::Invalid() :err{"Date: Unknown error"} { };


    // Определения функций-членов:
    Date::Date(int yy, Month mm, int dd)
            :y {yy}, m {mm}, d {dd}
    {
        if (!is_date(yy, mm, dd)) throw Invalid{"Invalid date"};
    }

    // Дата по умолчанию
    const Date& default_date()
    {
        static Date dd {2001, Month::jan, 1};
        return dd;
    }

    // Конструктор даты по умолчанию
    Date::Date()
        :y {default_date().year()},
        m {default_date().month()},
        d {default_date().day()}
    {}


    // Вспомогательные функции:
    // Проверка даты на валидность
    bool is_date(int y, Month m, int d)
    {
        // Полагаем y корректным
        if (d < 0) return false;      // d должно быть положительным
        if (m < Month::jan || Month::dec < m) return false;

        int days_in_month = 31;       // В месяце не более 31 дня
        switch (m) {
            case Month::feb:            // Длина февраля бывает разной
                days_in_month = ( leapyear(y) ) ? 29 : 28;
                break;
            case Month::apr: case Month::jun:
            case Month::sep: case Month::nov:
                days_in_month = 30;       // В этих месяцах 30 дней
                break;
        }

        return days_in_month >= d;
    }


    // В случае високосного года возвращает true
    bool leapyear(int y)
    {
        if (y % 4   != 0) return false;
        if (y % 100 != 0) return true;
        return y % 400 == 0;
    }


    // Перегрузка оператора == для Date
    bool operator == (const Date& a, const Date& b)
    {
        return    a.year()  == b.year()
               && a.month() == b.month()
               && a.day()   == b.day();
    }


    // Перегрузка оператора != для Date
    bool operator != (const Date& a, const Date& b)
    {
        return !(a == b);
    }


    // Перегрузка оператора << для Date
    std::ostream& operator << (std::ostream& os, const Date& d)
    {
        return os << '(' << d.year()
                  << ',' << int(d.month())
                  << ',' << d.day() << ')';
    }


    // Перегрузка оператора >> для Date
    std::istream& operator >> (std::istream& is, Date& dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is) return is;

        if (ch1 != '(' || ch2 != ',' ||
            ch3 != ',' || ch4 != ')') {        // Ошибка формата
            is.clear(std::ios_base::failbit);  // Устанавливаем бит ошибки
            return is;
        }
        dd = Date(y, Month(m), d);             // Обновляем  dd
        return is;
    }
} // Chrono