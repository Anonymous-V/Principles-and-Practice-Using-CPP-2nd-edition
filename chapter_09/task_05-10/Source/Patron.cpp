#include "../Header/Patron.h"

namespace Patron_work {

    // Конструктор класса
    Patron_work::Patron::Patron(std::string user, double fee)
        : user{user}, membership_fee{fee}
    {
        card_number = init_card();
    }


    bool operator == (const Patron_work::Patron& a, const Patron_work::Patron& b)
    {
        return a.get_card() == b.get_card();
    }


    std::ostream& operator <<(std::ostream& os, const Patron_work::Patron& patron)
    {
        return os << "Name: " << patron.get_user() << '\n'
                  << "ID:   " << patron.get_card();
    }


    unsigned int init_card()
    {
        static unsigned int id = 0;
        ++id;
        return id;
    }

} // Patron_work