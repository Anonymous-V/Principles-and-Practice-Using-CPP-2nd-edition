#include "Header/Library.h"

int main() {
    try {
        // Объект библиотеки
        Library_work::Library lib;

        // Создание объектов книг
        Book_work::Book book_conan {
            Book_work::ISBN{1, 1, 1, "A"},
            "The Adventure of Sherlock Holmes",
            "Sir Arthur Conan Doyle",
            Chrono::Date{2020, Chrono::Month::feb, 29},
            Book_work::Genre::fantasy
        };

        Book_work::Book book_hill {
            Book_work::ISBN{1, 1, 1, "B"},
            "Think and Grow Rich",
            "Napoleon Hill",
            Chrono::Date{2019, Chrono::Month::sep, 11},
            Book_work::Genre::biography
        };

        // Создание объектов пользователей
        Patron_work::Patron Vitaliy_user {"Vitaliy",0};
        Patron_work::Patron Alex_user {"Alex",50};
        Patron_work::Patron Elena_user {"Elena",-10};

        // Добавление книг в библиотеку
        lib.add_book(book_conan);
        lib.add_book(book_hill);

        // Добавление пользователей в библиотеку
        lib.add_patron(Vitaliy_user);
        lib.add_patron(Alex_user);
        lib.add_patron(Elena_user);

        // Выдача книг читателям
        lib.add_transact(book_conan, Vitaliy_user,
                         Chrono::Date{2020, Chrono::Month::feb, 29});
        lib.add_transact(book_hill, Alex_user,
                         Chrono::Date{2020, Chrono::Month::mar, 5});

        // Вывод всех читателей-должников
        std::vector<Patron_work::Patron> patron_debt;
        patron_debt = lib.get_debtors();

        std::cout << "Debtors:" << std::endl;
        for (const Patron_work::Patron& patron : patron_debt)
            std::cout << patron << std::endl;

        return 0;
    } catch (Chrono::Date::Invalid &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 3;
    }
}