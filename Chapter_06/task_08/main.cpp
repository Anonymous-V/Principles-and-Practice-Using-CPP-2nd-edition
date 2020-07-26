/*
 * Описание задачи:
 * ================
 * Повторите упр. 12 из главы 5 (игра "Коровы и быки"), используя четыре буквы,
 * а не четыре цифры.
 *
 * Идея реализации:
 * ================
 * Для решения этой задачи потребовалось только поменять тип данных под char и
 * немного изменить генерацию цисел - теперь генерируется число в диапазоне
 * от 0 до 26 (количество букв в английском алфавите) и прибавляется число,
 * соответствующее букве 'A', т.к. в данной задаче используются буквы A..Z.
 *
 * Генератор выглядит следующим образом:
 * letters_en = 26
 * rand_val = rand() % letters_en + 'A';
 *
 * В остальном реализация не менялась.
 * */

#include "../../std_lib_facilities.h"

// Функция проверки на совпадение коров
int check_cows(vector <char> animals, vector <char> answers) {
    int cnt_cows = 0;

    // Коровы должны совпадать на несоответствующих позициях
    for (int i = 0; i < answers.size(); ++i) {
        for (int j = 0; j < animals.size(); ++j)
            if (i != j && answers[i] == animals[j]) ++cnt_cows;
    }

    return cnt_cows;
}

// Функция проверки на совпадение быков
int check_bulls(vector <char> animals, vector <char> answers) {
    int cnt_bulls = 0;
    // Быки должны совпадать на соответствующих позициях
    for (int i = 0; i < answers.size(); ++i)
        if (answers[i] == animals[i]) ++cnt_bulls;

    return cnt_bulls;
}

// Функция создает вектор с ответами пользователя
vector <char> user_answer(int CNT_ANIMALS) {
    vector <char> answers;
    char answer;

    cout << "Your answer (" << CNT_ANIMALS
         << " letters A..Z) " << endl;
    for (int i = 0; i < CNT_ANIMALS; ++i) {
        cin >> answer;
        for (char val : answers)
            // Необходима проверка, чтобы не было дубликатов, иначе
            // пользователю будет выдаваться неверный результат
            // в виде угаданных коров
            if (answer == val)
                throw runtime_error("There should be no duplicate numbers");
        answers.push_back(answer);
    }

    return answers;
}

vector <char> gen_animals(const int CNT_ANIMALS) {
    vector <char> animals;
    int rand_val;
    // Дает обозначение можно ли добавить значение в вектор
    bool add_num;
    // Количество букв в английском алфавите
    int letters_en = 26;

    // Необходимо для генерации новых чисел
    srand( time(0) );
    while (animals.size() < CNT_ANIMALS) {
        // Используются буквы от 'A' до 'Z'
        rand_val = rand() % letters_en + 'A';
        add_num = true;
        // Проверка на дубликаты
        for (char val : animals)
            if (rand_val == val) add_num = false;
        if (add_num) animals.push_back(rand_val);
    }

    return animals;
}

int main() {
    try {
        // Количество коров и быков в векторе
        constexpr int CNT_ANIMALS = 4;
        // Загаданный вектор
        vector<char> animals;
        // Ответы пользователя
        vector<char> answers;
        // Количество угаданных быков и коров
        int bulls = 0, cows = 0;
        // Количество попыток потребуемое для угадывания всех быков
        int step = 0;
        // Генерируется вектор быков и коров
        animals = gen_animals(CNT_ANIMALS);

        // Начало игры
        while (bulls < CNT_ANIMALS) {
            // Создание вектора с ответами пользователя
            answers = user_answer(CNT_ANIMALS);
            // Сравнение векторов пользователя и компьютера
            // Сравнение на совпадение быков
            bulls = check_bulls(animals, answers);
            // Сравнение на совпадение коров
            cows = check_cows(animals, answers);

            cout << bulls << " bulls and "
                 << cows << " cows" << endl;

            ++step;
        }

        cout << "Congratulations! "
                "You guessed all the bulls in "
             << step << " steps" << endl;

        return 0;
    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}