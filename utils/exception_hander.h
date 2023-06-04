#ifndef EXCEPTION_HANDER_H
#define EXCEPTION_HANDER_H

#include <string>

class exception_hander
{
    private:
        std::string str;

    public:
        // constructor 
        explicit exception_hander();
        explicit exception_hander(std::string str);

        static void print_and_exit(std::string str);
        static void judge_success_or_not(bool result, std::string succ, std::string fail);
};

#endif