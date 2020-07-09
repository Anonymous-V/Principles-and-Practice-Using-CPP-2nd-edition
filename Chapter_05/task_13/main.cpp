/*
 * Описание задачи:
 * ================
 * Следующая программа довольно сложная. Создайте вариант, в котором игрок может
 * играть постоянно (без остановки и повторного запуска) и в каждой новой игре
 * генерируются новые четыре цифры. Четыре случайные цифры можно сгенерировать
 * с помощью четырех вызовов генератора случайных целых чисел randint(10) из
 * заголовочного файла std_lib_facilities.h. Обратите внимание на то, что при
 * повторном выполнении программы вы каждый раз будете получать одинаковые
 * последовательности из четырех цифр. Для того чтобы избежать этого, предложите
 * пользователю ввести любое число и до вызова функции randint(10) вызовите
 * функцию srand(n), где n - число, введеное пользователем. Такое число n
 * называется начальным значением (seed), причем разные начальные значения
 * приводят к разным последовательностям случайных чисел.
 *
 * Идея реализации:
 * ================
 * Идея и реализация осталась той же, только в этом решение для бесконечной
 * игры потребовалось обернуть цикл начала игры ещё в один цикл. В нем происходит
 * генерация нового вектора с ответами и обнуление переменных bulls, cows, step.
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

        // Для бесконечной игры
        while (true) {
            bulls = 0;
            cows = 0;
            step = 0;
            // Генерируется вектор быков и коров
            animals = gen_animals(CNT_ANIMALS);

            for (int val : animals)
                cout << val << " ";

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

        }
        return 0;
    } catch(runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}