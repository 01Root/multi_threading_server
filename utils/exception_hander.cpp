#include <iostream>
#include "exception_hander.h"

// constructor 
exception_hander::exception_hander():str("")
{
}
exception_hander::exception_hander(std::string str)
{
    this->str = str;
}

// print and exit 
void exception_hander::print_and_exit(std::string str)
{

    perror(str.c_str());
    exit(EXIT_FAILURE);
}

// judge result is true or not, if result is true, print succ. if result is false, print fail.
void exception_hander::judge_success_or_not(bool result, std::string succ, std::string fail)
{
    if (result)
    {
        std::cout << succ << std::endl;
    }
    else 
    {
        std::cout << fail << std::endl;
    }
}
