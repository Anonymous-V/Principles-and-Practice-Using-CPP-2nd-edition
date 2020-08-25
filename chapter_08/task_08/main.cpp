/*
 * Описание задачи:
 * ================
 * Напишите функцию, которая для двух данных объектов типа vector <double>
 * price и weight, вычисляет значение, равное сумме всех произведений
 * price[i] * weight[i]. Проверьте выполнение условия weight.size() == price.size().
 *
 * Идея реализации:
 * ================
 * Задача довольно тривиальна. Основные потребности возникают в проверке вводимых
 * значений. Ввод векторов можно было сделать двумя функциями, но в этот раз
 * решил поступить именно таким образом.
 * */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;


// Вычисление суммы произведений
double price_on_weight(const vector <double> &price, const vector <double> &weight)
{
    double sum = 0;
    for (int i = 0; i < price.size(); ++i)
        sum += price[i] * weight[i];

    return sum;
}


// Ввод векторов price и weight
void inp_price_weight(vector <double> &price, vector <double> &weight)
{
    double price_val, weight_val;

    cout << "Enter price and weight (-1 -1 to exit)" << std::endl;
    while (cin) {
        cin >> price_val >> weight_val;
        if (price_val == -1 && weight_val == -1) break;
        if (price_val < 0 || weight_val < 0) throw std::runtime_error("Invalid argument");
        price.push_back(price_val);
        weight.push_back(weight_val);
    }
}


// Подготовка векторов и вычисления суммы произведений
double calculate(vector <double> &price, vector <double> &weight)
{
    try {
        inp_price_weight(price, weight);
        double sum = price_on_weight(price, weight);
        return sum;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

}


int main() {
    try {
        vector <double> price;
        vector <double> weight;

        double sum = calculate(price, weight);
        cout << "Result: " << sum;

        return 0;
    } catch (...) {
        std::cerr << "Unknown error";
        return 1;
    }
}