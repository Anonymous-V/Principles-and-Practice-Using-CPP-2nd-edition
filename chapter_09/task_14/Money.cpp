#include "Money.h"

namespace Money {

  Money::Money(double money)
  {
    if (!is_money(money)) throw std::runtime_error("Negative value of money");
    cents = to_cents(money);
  }


  // Проверка на положительные значения
  bool is_money(double money) { return money >= 0; }


  // Перевод доллары и центы в центы
  // (0.5 и больше - округление до 1; иначе - округление до 0)
  long int to_cents(double money)
  {
    long int cents = money * 1000;   // Необходимо для выделения последнего числа
    int rounding = cents % 10;  // Округление
    cents /= 10;                // Убираем лишнее значение

    if (rounding >= 5) ++cents;
    return cents;
  }

  // Перевод центы в доллары
  double to_dollars(double money)
  {
    return money / 100.0;
  }


  // Переопределение оператора сложения
  double operator + (Money& a, Money& b)
  {
    return to_dollars( a.get_cents() + b.get_cents() );
  }


  // Переопределение оператора вычитания
  double operator - (Money& a, Money& b)
  {
    return to_dollars( a.get_cents() - b.get_cents() );
  }


  // Переопределение оператора умножения
  double operator * (Money& a, Money& b)
  {
    return to_dollars( a.get_cents() * b.get_cents() / 100 );
  }


  // Переопределение оператора деления
  double operator / (Money& a, Money& b)
  {
    if (b.get_cents() == 0) throw std::runtime_error("Division by zero");
    return to_dollars( double(a.get_cents()) / b.get_cents() );
  }


  // Переопределение оператора вывода
  std::ostream& operator << (std::ostream& os, Money& m)
  {
    return os << '$' << to_dollars( m.get_cents() );
  }


  // Переопределение оператора ввода; формат: $<лит_с_плав_точкой>
  std::istream& operator >> (std::istream& is, Money& m)
  {
    char dollar_sym;
    double money;

    is >> dollar_sym >> money;
    if (!is_money(money)) return is;    // Значение должно быть положительным
    if (!is) return is;
    if (dollar_sym != '$') {            // Ошибка формата
      is.clear(std::ios_base::failbit); // Установка бита ошибки
      return is;
    }
    m = Money{money};
    return is;
  }
} // Money namespace