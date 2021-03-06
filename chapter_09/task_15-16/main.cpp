/*
 * Описание задачи 15:
 * ===================
 * Доработайте класс Money, добавив в него валюту (как аргумент конструктора).
 * Разрешите использовать инициализаторы с плавающей точкой, если эти значения
 * точно представимы с помощью типа long int. Не допускайте некорректных операций.
 * Например, выражение Money*Money не имеет смысла, а USD1.23+DKK5.00 имеет смысл,
 * только если существует таблица преобразования, определяющая обменный курс между
 * американскими долларами (USD) и датскими кронами (DKK).
 *
 * Описание задачи 16:
 * ===================
 * Определите оператор ввода >>, который считывает денежные суммы с указанием
 * валют (например, USD1.23 или DKK5.00) в переменную типа Money. Определите также
 * соответствующий оператор вывода <<.
 *
 * Идея реализации:
 * ===================
 * Идея работы программы состоит в том, чтобы преобразовать введенную валюту в
 * центы и дальнейшую работу производить именно с центами. Также необходимо
 * сохранить оригинальное значение валюты для более удобного вывода её на печать.
 *
 * На этапе создания валюты происходит её преобразование и округление. При этом
 * лишняя часть отбрасывается функцией trunc.
 * Для преобразования валюты в центы использованы готовые коэффициенты, которые
 * можно получить из фукнции get_coef.
 * Остальное описание и работу кода можно посмотреть в самом коде.
 * */

#include "Money.h"

int main() {
    try {
        Money::Money m{"RUB", 100};
        Money::Money n{"EUR", 63};
        Money::Money p{"DKK", 164};
        Money::Money x{"USD", 23};
        Money::Money g{"GBR", 380};

        std::cout << m << " + " << n <<  " = " << '$' << m + n << std::endl;
        std::cout << n << " - " << x <<  " = " << '$' << n - x << std::endl;
        std::cout << m << " * " << p <<  " = " << '$' << m * p << std::endl;
        std::cout << g << " / " << x <<  " = " << '$' << g / x << std::endl;

        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}