/*
 * Класс библиотеки
 * Включает в себя классы: Book, Patron
 * */

#include "Book.h"
#include "Patron.h"
#include <vector>

namespace Library_work {

    // Структура для хранения выданных книг
    struct Transaction {
        Book_work::Book book;
        Patron_work::Patron patron;
        Chrono::Date date;
    };

    class Library {
    public:
        Library() { };

        // Немодифицирующие операции:
        bool check_book(const Book_work::Book& book);        // Принадлежность книги библиотеке
        bool check_patron(const Patron_work::Patron& patron);// Принадлежность читателя библиотеке
        bool check_give_book(const Book_work::Book& book);   // Выдана ли книга
        std::vector<Patron_work::Patron> get_debtors();      // Вектор должников

        // Модифицирующие операции:
        void add_book(Book_work::Book& book);                // Добавить книгу в библиотеку
        void add_patron(const Patron_work::Patron& patron);  // Добавить пользователя в библиотеку
        // Выдача книги пользователю
        void add_transact(Book_work::Book& book,
                          const Patron_work::Patron& patron,
                          const Chrono::Date& date);
    private:
        std::vector<Book_work::Book> books;                  // Книги в библиотеке
        std::vector<Patron_work::Patron> patrons;            // Пользователи в библиотеке
        std::vector<Library_work::Transaction> transactions; // Все выдачи книг читателям
    };

} // Library_work