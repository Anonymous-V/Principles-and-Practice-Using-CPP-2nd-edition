#include "print_str.h"

void print(const std::string &label, const std::vector <std::string> &v)
{
    std::cout << label << ": ";
    for (std::string val : v)
        std::cout << val << " ";
}