/*
 * Класс Money для хранения денежной единицы - центов. Ввод и вывод осуществляется
 * в формате: $<литерал_с_плавающей_точкой>.
 * При инициализации доллары с центами переводятся в центы.
 * Переопределены некоторые операторы для удобной работы.
 * */

#include <iostream>

namespace Money {
  class Money {
  public:
    Money() :cents{0} { };  // Конструктор по умолчанию
    Money(double money);

    // Немодифицирующие функции:
    int get_cents() const { return cents; }
  private:
    long int cents;
  };

  // Вспомогательные функции
  bool is_money(double money);     // Проверка, что значение не отрицательное
  long int to_cents(double money); // Перевод долларов и центов в центы
  double to_dollars(double money); // Перевод из центов в доллары

  // Перегрузка операторов
  double operator + (Money& a, Money& b);
  double operator - (Money& a, Money& b);
  double operator * (Money& a, Money& b);
  double operator / (Money& a, Money& b);
  std::ostream& operator << (std::ostream& os, Money& m);
  std::istream& operator >> (std::istream& is, Money& m);

} // Money namespace