#include "Money.h"

namespace Money {

    Money::Money(std::string currency, double money)
        :currency{currency}, money{money}
    {
        if (!is_money(money)) throw std::runtime_error("Negative value of money");
        if (!is_currency(currency))
            throw std::runtime_error("Unknown currency: " + std::string(currency));
        cents = to_cents(currency, money);
    }


    // Валюта доступная для преобразования
    const std::vector<std::string>& default_currency()
    {
        // Доллар, рубль, датский крон, евро, фунт стерлингов
        static std::vector<std::string> currency {"USD", "RUB", "DKK", "EUR", "GBR"};
        return currency;
    }

    // Проверка на положительные значения
    bool is_money(double money)
    {
        return money >= 0;
    }


    // Проверка, что валюта имеется в векторе
    bool is_currency(const std::string& currency)
    {
        for (const std::string& cur : default_currency())
            if (cur == currency) return true;
        return false;
    }


    // Получить валюту в формате enum из string
    Currency get_currency(const std::string& cur)
    {
        for (int i = 0; i < default_currency().size(); ++i)
            if (default_currency()[i] == cur) return Currency(i);
        throw std::runtime_error("Unknown currency");
    }


    // Получить коэффициент валюты для перевода в центы
    double get_coef(const std::string& currency)
    {
        Currency cur = get_currency(currency);
        switch (cur) {
            case Currency::USD: return 100;
            case Currency::RUB: return 1.33;
            case Currency::DKK: return 15.98;
            case Currency::EUR: return 118.92;
            case Currency::GBR: return 128.97;
            default: throw std::runtime_error("Unknown currency");
        }
    }


    // Перевод доллары и центы в центы
    // (0.5 и больше - округление до 1; иначе - округление до 0)
    long int to_cents(const std::string& currency, double money)
    {
        // Необходимо для выделения последнего числа
        long int cents = trunc(get_coef(currency) * money * 10); // Другие числа не важны
        int rounding = cents % 10;  // Выделение последнего числа для округления
        cents /= 10;                // Убираем лишнее значение

        if (rounding >= 5) ++cents;
        return cents;
    }

    // Перевод центы в доллары
    double to_dollars(long int money)
    {
        return double(money) / 100;
    }


    // Переопределение оператора сложения
    double operator + (Money& a, Money& b)
    {
        return to_dollars(a.get_cents() + b.get_cents());
    }


    // Переопределение оператора вычитания
    double operator - (Money& a, Money& b)
    {
        return to_dollars(a.get_cents() - b.get_cents());
    }


    // Переопределение оператора умножения
    double operator * (Money& a, Money& b)
    {
        return to_dollars(a.get_cents() * b.get_cents());
    }


    // Переопределение оператора деления
    double operator / (Money& a, Money& b)
    {
        if (b.get_cents() == 0) throw std::runtime_error("Division by zero");
        return to_dollars(a.get_cents() / b.get_cents());
    }


    // Переопределение оператора вывода
    std::ostream& operator << (std::ostream& os, Money& m)
    {
        return os << m.get_currency() << " " << m.get_money();
    }


    // Переопределение оператора ввода; формат: <валюта><лит_с_плав_точкой>
    std::istream& operator >> (std::istream& is, Money& m)
    {
        double money;
        char sym;
        std::string currency;

        for (int i = 0; i < 3; ++i) {    // Считать из потока валюту (формат string)
            is >> sym;
            currency += sym;
        }
        is >> money;

        if (!is_money(money)) return is;  // Значение должно быть положительным
        if (!is) return is;

        m = Money {currency, money};      // Проверка валюты в конструкторе
        return is;
    }
} // Money namespace