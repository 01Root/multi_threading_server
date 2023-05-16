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