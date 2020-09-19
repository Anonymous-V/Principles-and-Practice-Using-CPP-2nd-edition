#include "Chrono.h"

namespace Chrono {
    // Определение класса-члена:
    Date::Invalid::Invalid(std::string er) :err{er} { };
    Date::Invalid::Invalid() :err{"Date: Unknown error"} { };


    // Определения функций-членов:
    Date::Date(int yy, Month mm, int dd)
            :y {yy}, m {mm}, d {dd}, zero_days {0}
    {
        if (!is_date(yy, mm, dd)) throw Invalid{"Invalid date"};
        zero_days = to_zero_days(yy, mm, dd);
    }


    // Дата по умолчанию
    const Date& default_date()
    {
        static Date dd {1970, Month::jan, 1};
        return dd;
    }


    // Конструктор даты по умолчанию
    Date::Date()
        :y {default_date().year()},
        m {default_date().month()},
        d {default_date().day()},
        zero_days {0}
    {}


    // Добавить дни
    void Date::add_day(int n)
    {
        if (n < 0) throw std::runtime_error("Add day: Negative n");
        n += d;     // Прибавить текущее количество дней

        int days = days_in_month(y, m);

        while (n > days) { // Разделение дней на месяцы и дни
            add_month(1);
            n -= days;
            days = days_in_month(y, m);
        }
        d = n;
    }


    // Добавить месяцы
    void Date::add_month(int n)
    {
        if (n < 0) throw std::runtime_error("Add month: Negative n");
        n += int(m);    // Прибавить текущее количество месяцев

        int years = n / 12;
        n = n - years * 12;

        m = static_cast<Month>(n);  // Преобразовать в enum Month
        add_year(years);
    }


    // Добавить года
    void Date::add_year(int n)
    {
        if (m == Month::feb && d == 29 && !leapyear(y + n)) {
            m = Month::mar;
            d = 1;
        }
        y += n;
    }


    // Вспомогательные функции:
    // Проверка даты на валидность
    bool is_date(int y, Month m, int d)
    {
        if (y < 1970) return false;
        if (d < 0) return false;      // d должно быть положительным
        if (m < Month::jan || Month::dec < m) return false;

        int days_in_m = days_in_month(y, m);

        return days_in_m >= d;
    }


    // Перевод даты в дни от нулевого дня (01.01.1970)
    long int to_zero_days(int yy, Month mm, int dd)
    {
        int days {0};
        for (int i = 1970; i < yy; ++i) { // Пройтись по годам
            if (leapyear(i)) ++days;
            days += 365;
        }

        for (int i = 1; i < int(mm); ++i) // Пройтись по месяцам
            days += days_in_month(yy, static_cast<Month> (i));
        days += dd;

        return days;
    }


    // В случае високосного года возвращает true
    bool leapyear(int y)
    {
        if (y % 4   != 0) return false;
        if (y % 100 != 0) return true;
        return y % 400 == 0;
    }


    // Возвращает количество дней в месяце
    int days_in_month(int year, Month month)
    {
        int days = 31;              // В месяце не более 31 дня
        switch (month) {
            case Month::feb:        // Длина февраля бывает разной
                days = ( leapyear(year) ) ? 29 : 28;
                break;
            case Month::apr: case Month::jun:
            case Month::sep: case Month::nov:
                days = 30;          // В этих месяцах 30 дней
                break;
        }
        return days;
    }


    // Перечисление типа дня недели
    enum class Day {
        sunday, monday, tuesday, wednesday,
        thursday, friday, saturday
    };


    // Возвращает номер недели (предполагается, что год начинает с 1 января и
    // первый день недели - понедельник
    int week_of_year(Date& date)
    {
        int days = 0;
        Date d {date.year(), Month::jan, 1}; // Начало года

        for (int i = 1; i < int(date.month()); ++i)
            days += days_in_month(date.year(), static_cast<Month> (i));

        days += date.day(); // Прибавить дни текущего месяца
        int weeks = days / 7 + 1;
        if (days % 7 == 0) --weeks; // Случай, когда конец недели

        return weeks;
    }

    // Для получения дня недели используется формула Зеллера
    // https://yandex.ru/q/question/science/est_li_kakaia_to_metodika_opredeleniia_v_ff3a9d82/?utm_source=yandex&utm_medium=wizard&answer_id=dde75719-71f0-4c89-a065-282189ef0a3b#dde75719-71f0-4c89-a065-282189ef0a3b
    Day day_of_week(const Date& d)
    {
        int year = d.year();
        int month = int(d.month());

        if (d.month() <= Month::feb) {
            --year;
            month += 10;
        } else month -= 2;

        int day = d.day() + 31 * month / 12 + year + year / 4 - year / 100 + year / 400;
        day %= 7;

        return static_cast<Day> (day); // Преобразование в enum Day
    }


    // Следующий рабочий день недели (кроме воскресенья и субботы)
    Date next_workday(Date& date)
    {
        Date date_copy = date;
        date_copy.add_day(1);
        Day day = day_of_week(date_copy);      // Получить день недели
        while (day == Day::sunday || day == Day::saturday) {
            date_copy.add_day(1);
            day = day_of_week(date_copy);
        }
        return date_copy;
    }


    // Перегрузка оператора == для Date
    bool operator == (const Date& a, const Date& b)
    {
        return a.get_zero_days() == b.get_zero_days();
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