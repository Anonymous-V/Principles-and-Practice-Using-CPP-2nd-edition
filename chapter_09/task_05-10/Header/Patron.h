/*
 * Класс для читателей библиотеки
 * У читателя имеется: имя, карточка читателя, размер членского взноса и
 * оплата членского взноса
 * */

#include <iostream>

namespace Patron_work {

    class Patron {
    public:
        Patron(std::string user, double fee);

        // Немодифицирующие операции:
        const std::string& get_user() const { return user; }
        unsigned int get_card() const { return card_number; }    // Номер библиотечной карточки
        double get_membership() const { return membership_fee; } // Размер членского взноса
        bool paid_fee() const { return membership_fee >= 0; } // Оплачен ли членский взнос

        // Модифицирующие операции:
        // Установить размер членского взноса
        void set_membership_fee(double fee) { membership_fee = fee; }
    private:
        std::string user;
        unsigned int card_number;   // Создается автоматически функцией init_card()
        double membership_fee; // Если значение < 0, то у пользователя задолженность
    };

    // Вспомогательные функции:
    unsigned int init_card(); // Присваивание уникального номера читателю
    bool operator == (const Patron_work::Patron& a, const Patron_work::Patron& b);
    bool operator != (const Patron_work::Patron& a, const Patron_work::Patron& b);
    std::ostream& operator <<(std::ostream& os, const Patron_work::Patron& patron);

} // Patron_work