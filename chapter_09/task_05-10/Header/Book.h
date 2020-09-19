/*
 * Класс Book для создания книг
 * Включает в себя класс для хранения даты из главы 9
 * */

#include "Chrono.h"

namespace Book_work {

    // Структура для хранения кода ISBN
    // n-n-n-x, где n - число, x - число или буква
    struct ISBN {
        int val_one   {0},
            val_two   {0},
            val_three {0};
        std::string sym {'0'};
        ISBN(int vl_one, int vl_two, int vl_three, std::string sm)
            :val_one{vl_one}, val_two{vl_two}, val_three{vl_three}, sym{sm} {};
    };


    // Жанр книг: фантастика, проза, периодические издания,
    // биография, детская литература
    enum class Genre {
        fantasy, prose, periodical, biography, children
    };


    class Book {
    public:
        Book(ISBN isbn, std::string title, std::string author,
                Chrono::Date date, Genre genre);

        // Немодифицируемые операции:
        const std::string& get_ISBN() const { return isbn_str; }
        const std::string& get_title() const { return title; }
        const std::string& get_author() const { return author; }
        const Chrono::Date& get_date() const { return reg_date; }
        bool get_give_book() const { return give_book; }    // true - книга выдана
        bool get_in_library() const { return in_library; }

        // Модифицирующие операции:
        void set_give_book(bool gv_book) { give_book = gv_book; } // Устанавливает выдачу книги
        void set_in_library() { in_library = true; }    // Книга добавлена в библиотеку

    private:
        std::string isbn_str;     // Код книги ISBN
        std::string title;        // Название книги
        std::string author;       // Автор книги
        Chrono::Date reg_date;    // Дата регистрации авторских прав
        bool give_book { false }; // Выдана ли книга на руки
        bool in_library { false };// Находится ли книга в библиотеке
    };

    // Функция проверки, выдана книга или нет
    bool is_isbn(int val_one, int val_two, int val_three, std::string str); // Проверка ISBN
    bool is_genre(Genre gen);       // Проверка принадлежности жанру
    bool operator == (const Book& a, const Book& b);
    bool operator != (const Book& a, const Book& b);
    std::ostream& operator << (std::ostream& os, const Book& a);
}