/*
 * Описание задачи:
 * ================
 * Реализуйте простую игру на угадывание "Быки и коровы". Программа должна хранить
 * вектор из четырех различных чисел в диапазоне от 0 до 9 (т.е., например,
 * 2345, но не 4455), а пользователь должен угадать загаданное число. Допустим,
 * программа загадала число 1234, а пользователь назвал число 1359; программа
 * должна ответить "1 бык и 1 корова", поскольку пользователь угадал одну
 * правильную цифру (1) в правильной позиции (бык) и одну правильную цифру (3)
 * в неправильной позиции (корова). Угадывание продолжается, пока пользователь
 * не получит четырех быков, т.е. не угадает четыре правильные цифры в четырех
 * правильных позициях.
 *
 * Идея реализации:
 * ================
 * Первым делом генерируется вектор с загаданными значенимями компьютера. Числа
 * в векторе не должны повторяться.
 *
 * Как вектор был сгенерирован начинается игра (цикл while). В нем пользователю
 * необходимо ввести значения в другой вектор. При этом значения также не должны
 * повторяться, потому что могут выдаваться неверные результаты в виде коров.
 *
 * После того, как пользователь ввел данные, необходимо проверить количество
 * угаданных быков и коров. Для этого используются соответствующие функции.
 * Быки должны совпадать на соответствующих позициях в векторах, а коровы должны
 * совпадать в любом значении, кроме одинаковых позиций.
 *
 * Также есть переменная step, которая считает количество попыток пользователя.
 * */

#include "../../std_lib_facilities.h"

// Функция проверки на совпадение коров
int check_cows(vector <int> animals, vector <int> answers) {
    int cnt_cows = 0;

    // Коровы должны совпадать на несоответствующих позициях
    for (int i = 0; i < answers.size(); ++i) {
        for (int j = 0; j < animals.size(); ++j)
            if (i != j && answers[i] == animals[j]) ++cnt_cows;
    }

    return cnt_cows;
}

// Функция проверки на совпадение быков
int check_bulls(vector <int> animals, vector <int> answers) {
    int cnt_bulls = 0;
    // Быки должны совпадать на соответствующих позициях
    for (int i = 0; i < answers.size(); ++i)
        if (answers[i] == animals[i]) ++cnt_bulls;

    return cnt_bulls;
}

// Функция создает вектор с ответами пользователя
vector <int> user_answer(int CNT_ANIMALS) {
    vector <int> answers;
    int answer;

    cout << "Your answer (" << CNT_ANIMALS
         << " numbers) " << endl;
    for (int i = 0; i < CNT_ANIMALS; ++i) {
        cin >> answer;
        for (int val : answers)
            // Необходима проверка, чтобы не было дубликатов, иначе
            // пользователю будет выдаваться неверный результат
            // в виде угаданных коров
            if (answer == val)
                throw runtime_error("There should be no duplicate numbers");
        answers.push_back(answer);
    }

    return answers;
}

vector <int> gen_animals(const int CNT_ANIMALS) {
    vector <int> animals;
    int rand_val;
    // Дает обозначение можно ли добавить значение в вектор
    bool add_num;

    // Необходимо для генерации новых чисел
    srand( time(0) );
    while (animals.size() < CNT_ANIMALS) {
        rand_val = rand() % 10;
        add_num = true;
        // Проверка на дубликаты
        for (int val : animals)
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
        vector<int> animals;
        // Ответы пользователя
        vector<int> answers;
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
    } catch(runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}