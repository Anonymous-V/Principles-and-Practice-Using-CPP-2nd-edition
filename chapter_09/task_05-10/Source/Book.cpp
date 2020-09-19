#include "../Header/Book.h"

namespace Book_work {

    // Конструктор Book
    Book::Book(Book_work::ISBN isbn, std::string title, std::string author,
               Chrono::Date date, Book_work::Genre genre)
        :title{title}, author{author}, reg_date{date}
    {
        if ( !is_isbn(isbn.val_one, isbn.val_two, isbn.val_three, isbn.sym) )
            throw std::runtime_error("Invalid ISBN");
        if ( !is_genre(genre) )
            throw std::runtime_error("Invalid genre");
        isbn_str = std::to_string(isbn.val_one)   + '-' +
                   std::to_string(isbn.val_two)   + '-' +
                   std::to_string(isbn.val_three) + '-' +
                   isbn.sym;
    }


    // Вспомогательные функции:
    bool is_isbn(int val_one, int val_two, int val_three, std::string str)
    {
        try {
            // Числа должны быть положительными
            if (val_one <= 0 || val_two <= 0 || val_three <= 0) return false;
            if (str.length() == 1 && isalpha(str[0])) return true;  // Является ли буквой
            return std::stoi(str) > 0; // Если не буква, то число > 0
        } catch (...) {
            return false;
        }
    }

    // Проверка на принадлежность Genre
    bool is_genre(Book_work::Genre genre)
    {
        return !(genre < Genre::fantasy || Genre::children < genre);
    }


    // Проверка кодов ISBN у двух книг
    bool operator == (const Book& a, const Book& b)
    {
        return a.get_ISBN() == b.get_ISBN();
    }


    // Проверка кодов ISBN у двух книг
    bool operator != (const Book& a, const Book& b)
    {
        return !(a == b);
    }


    // Вывод: название книги, фамилия автора и код ISBN
    std::ostream& operator << (std::ostream& os, const Book& a)
    {
        return os << a.get_title()  << '\n'
                  << a.get_author() << '\n'
                  << a.get_ISBN();
    }
} // Book_work