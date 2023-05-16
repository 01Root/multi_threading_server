#ifndef EXCEPTION_HANDER_H
#define EXCEPTION_HANDER_H

#include <string>

class exception_hander
{
    private:
        std::string str;

    public:
        explicit exception_hander();
        explicit exception_hander(std::string str);

        void print_and_exit(std::string str);
};

#endif