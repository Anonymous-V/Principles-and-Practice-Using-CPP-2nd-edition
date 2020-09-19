/*
 * Класс Money для хранения денежной единицы - центов. Ввод и вывод осуществляется
 * в формате: $<литерал_с_плавающей_точкой>.
 * При инициализации любая валюта переводится в центы. Дальнейшние вычисления
 * также происходят с центами.
 * При выводе центы переводятся в соответствующую валюту.
 * Переопределены некоторые операторы для удобной работы.
 * */

#include <iostream>
#include <vector>
#include <cmath>

namespace Money {

    // Валюты: доллар, рубль, датский крон, евро, фунт стерлингов
    enum class Currency {
        USD, RUB, DKK, EUR, GBR
    };

    class Money {
    public:
      Money() :cents{0}, money{0}, currency{"USD"} { }; // Конструктор по умолчанию
      Money(std::string currency, double money);

      // Немодифицирующие функции:
      int get_cents() const { return cents; }
      std::string get_currency() const { return currency; }
      double get_money() const { return money; }

    private:
      long int cents;
      double money;
      std::string currency;
    };

    // Вспомогательные функции
    bool is_money(double money);                   // Проверка, что значение не отрицательное
    bool is_currency(const std::string& currency); // Проверка наличия валюты в векторе
    long int to_cents(const std::string& currency, double money); // Перевод долларов и центов в центы

    // Перегрузка операторов
    double operator + (Money& a, Money& b);
    double operator - (Money& a, Money& b);
    double operator * (Money& a, Money& b);
    double operator / (Money& a, Money& b);
    std::ostream& operator << (std::ostream& os, Money& m);
    std::istream& operator >> (std::istream& is, Money& m);

} // Money namespace