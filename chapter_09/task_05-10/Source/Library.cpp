#include "../Header/Library.h"

namespace Library_work {

    // Добавление книги в библиотеку
    void Library_work::Library::add_book(Book_work::Book& book)
    {
        if (check_book(book))  // Проверить, что книга ещё не была добавлена
            throw std::runtime_error("Book \"" + book.get_title() + "\" is already exist");
        book.set_in_library(); // Установить флажок, что книга добавлена
        books.push_back(book);
    }


    // Добавление пользователя в библиотеку
    void Library_work::Library::add_patron(const Patron_work::Patron& patron)
    {
        if (check_patron(patron)) // Проверить, что пользователь ещё не был добавлен
            throw std::runtime_error("Patron \"" + patron.get_user() + "\" is already exist");
        patrons.push_back(patron);
    }


    // Выдать книгу пользователю
    void Library_work::Library::add_transact(Book_work::Book& book,
                                             const Patron_work::Patron& patron,
                                             const Chrono::Date& date)
    {
        if (!check_book(book) || !book.get_in_library()) // Книга должна быть в библиотеке
            throw std::runtime_error("Library: Book \"" + book.get_title() + "\" is not found");
        if (!check_patron(patron))      // Пользователь должен быть зареган в библиотеке
            throw std::runtime_error("Library: Patron \"" + patron.get_user() + "\" is not found");
        if (check_give_book(book))      // Книга не должна быть уже выдана
            throw std::runtime_error("Library: The book \"" + book.get_title() + "\" is already been issued to the reader");
        if (!patron.paid_fee())         // Читатель не имеет задолженностей
            throw std::runtime_error("The reader \"" + patron.get_user() + "\" is in arrears");

        book.set_give_book(true); // Флажок, что книга выдана
        transactions.push_back({book, patron, date});
    }


    // Проверить наличие книги в библиотеке
    bool Library_work::Library::check_book(const Book_work::Book& book)
    {
        for (const Book_work::Book& b : books)
            if (b == book) return true;
        return false;
    }


    // Проверить наличие пользователя в библиотеке
    bool Library_work::Library::check_patron(const Patron_work::Patron& patron)
    {
        for (const Patron_work::Patron& p : patrons)
            if (p == patron) return true;
        return false;
    }


    // Проверить, выдана ли книга
    bool Library_work::Library::check_give_book(const Book_work::Book& book)
    {
        if (check_book(book)) return book.get_give_book();
        throw std::runtime_error("Book is not found");
    }


    // Вернуть вектор должников
    std::vector<Patron_work::Patron> Library_work::Library::get_debtors()
    {
        std::vector<Patron_work::Patron> pt;
        for (const Patron_work::Patron& p : patrons)
            if (!p.paid_fee()) pt.push_back(p); // У должников отрицательное значение
        return pt;
    }

}