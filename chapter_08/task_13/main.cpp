/*
 * Описание задачи:
 * ================
 * Можно ли объявить константный аргумент функции, который передается не по ссылке
 * (например, void f(const int);? Что это значит? Зачем это нужно? Почему такая
 * конструкция практически не применяется? Испытайте ее; напишите несколько
 * маленьких программ, чтобы увидеть, как она работает.
 *
 * Идея реализации:
 * ================
 * Да, можно. Это означает, что параметр является неизменяемым. Возможно, такое
 * необходимо в задачах, чтобы предотвратить изменение значения в каких-либо
 * вычислениях. Думаю, такое используется редко, т.к. нет необходимости в
 * использовании; в данном случае параметр передается по значению, а значит
 * изменить передаваемую переменную не сможет.
 * */

#include <iostream>

void f(const int a)
{
    std::cout << a << std::endl;
}

int main() {
    f(5);
    return 0;
}