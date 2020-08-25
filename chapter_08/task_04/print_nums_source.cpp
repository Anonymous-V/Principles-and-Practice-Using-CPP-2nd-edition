#include "print_nums.h"

void print(const std::string &label, const std::vector <int> &v)
{
    std::cout << label << ": ";
    for (int val : v)
        std::cout << val << " ";
}