/*
 * Основная задача:
 * ================
 * Переработайте две программы, написанные вами при выполнении упраждениний к
 * главам 4 и 5. Приведите в порядок их код в соответствии с правилами, описанными
 * в данной главе. Посмотрите, не нашлись ли в процессе наведения порядка какие-либо
 * ошибки в ваших исходных текстах
 *
 * История изменений:
 * 09.08.2020 - Код разбит на функции и добавлены комментарии к программе;
 *              ошибок замечено не было.
 *
 * Описание задачи:
 * ================
 * Напишите программу для игры "Камень, ножницы, бумага". Если вы не знаете
 * правил этой игры, попробуйте выяснить их у друзей или помощью Google (поиск
 * информации - обычное занятие программистов). Для решения поставленной задачи
 * используйте инструкцию switch. Кроме того, машина должна давать случайные
 * ответы (т.е. выбирать камень, бумагу или ножницы на следующем ходу
 * случайным образом). Написать настоящий генератор случайных чисел прямо сейчас
 * вам будет довольно тяжело, поэтому заранее заполните вектор последовательностью
 * значений. Если встроить этот вектор в программу, то она всегда будет играть
 * одну и ту же игру, поэтому целесообразно позволить пользователю самому вводить
 * некоторые значения. Попробуйте помешать пользователю легко угадывать
 * следующий ход машины.
 *
 * Идея реализации:
 * ================
 * Для хранения ответов компьютера будет использоваться вектор в который
 * пользователь будет вводить значения (камень (r) - rock, ножницы (s) - scissors,
 * бумага (p) - paper). Все значения хранятся в типе char.
 *
 * Чтобы пользователь не играл одну и ту же игру, т.е. чтобы вектор значений был
 * не статичен, произведено перемешивание значений с помощью функции rand().
 * Цикл с количеством элементов n будет запускаться n * 10 раз. Это нужно для
 * того, чтобы значения хорошо перемешались.
 * На каждом шаге цикла создаются 2 случайных числа (не выходящие за границы
 * вектора) и значения на соответствующих позициях меняются местами.
 *
 * Сама игра происходит следующим образом: цикл проходит один раз по значениям
 * вектора. Пользователь вводит символ и этот символ проверяется, является ли
 * он p, r или s. Если нет, то запускается инструкция continue и пользователь
 * снова вводит значение.
 * Если всё корректно, то выполняется switch. Сначала проверяется разница по
 * значениям вектора и введенного пользователем. Если символы одинаковые, то
 * выполняется default, если же разные, то необходимо проверить кто и какие
 * символы "ввел". Для этого используется функция check_won, которая и выводит
 * соответствующие результаты.
 * */

#include "../../std_lib_facilities.h"


// * * * Вспомогательные функции для корректной работы игры * * *
//------------------------------------------------------------------------------


// Вычисление разности между ответами пользователя и компьютера
int sub_response(char val_one, char val_two) {
    return abs(val_one - val_two);
}


// Проверка, что символы введены корректно
bool is_valid_answer(char answer_usr) {
    // Проверка, что введены символы s, r или p
    return answer_usr >= 'p' && answer_usr <= 's' && answer_usr != 'q';
}


// Проверка ответа и определение победителя
string check_won(char answer_pc, char answer_usr) {
    switch (sub_response(answer_pc, answer_usr)) {
        // Случаи, когда выпали разные значения
        case 'r' - 'p': case 's' - 'p': case 's' - 'r':
            if (answer_pc == 'p' && answer_usr == 's') return "user";
            else if (answer_pc == 's' && answer_usr == 'p') return "PC";

            // Условие подходит для камней + бумаги и ножниц + камней
            if (answer_pc - answer_usr > 0) return "user";
            // Когда ни одно из условий не подходит
            return "PC";
            // Случаи, когда выпали одинаковые значения
        default:
            return "No one";
    }
}


// * * * Игровой процесс: чтение и перемешивание ответов, игра пользователя * * *
//------------------------------------------------------------------------------


// Игра пользователя и компьютера
void start_game(const vector <char> &elems) {
    char answer_usr;

    for (char answer_pc : elems) {
        try {
            cout << "Enter rock (r), scissors (s) or paper (p):" << endl;
            cin >> answer_usr;

            cout << "PC entered: " << answer_pc << '\n'
                 << "User entered: " << answer_usr << endl;

            if (!is_valid_answer(answer_usr)) error("Start_game: invalid character");

            cout << check_won(answer_pc, answer_usr) << " won" << endl;
            cout << endl;
        } catch (exception &e) {
            cerr << "Error inner: " << e.what() << endl;
        }
    }
}


// Перемешивание ответов компьютера
void shuffle_answers(vector <char> &elems) {
    int val_one, val_two;
    for (int i = 0; i < elems.size() * 10; ++i) {
        // Получаем случайные позиции элементов
        val_one = rand() % elems.size();
        val_two = rand() % elems.size();
        // Перестановка элементов стандартной функцией swap
        swap(elems[val_one], elems[val_two]);
    }
}


// Чтение ответов пользователя (для компьютера)
void read_answers_pc(vector <char> &elems) {
    // Заполнение ответами вектор
    for (char sym; cin >> sym;) {
        try {
            if (sym == '|') return;
            if ( is_valid_answer(sym) ) elems.push_back(sym);
            else error("Read_answer: invalid character");
        } catch (exception &e) {
            cerr << e.what() << endl;
        }
    }
}


// Подготовка игры: чтение ответов, перемешивание и сама игра
void play_game() {
    // Вектор с элементами: камень (r - rock),
    // ножницы (s - scissors) и бумага (p - paper)
    vector <char> elems;

    read_answers_pc(elems);
    shuffle_answers(elems);
    start_game(elems);
}


// Вызов справки
void help() {
    cout << "Enter the answers for the computer \n"
            "(r - rock, s - scissors, p - paper) \n"
            "When you're done typing the pipe character |:" << endl;
}


// Главная функция запуска игры
int main() {
    try {
        help();
        play_game();

        return 0;
    } catch (exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
}