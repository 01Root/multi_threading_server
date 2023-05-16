#ifndef FILE_H
#define FILE_H
#pragma once

#include <string>
#include <fstream>

class file
{
    private: 
        int file_size;
        std::string file_path;
        std::ofstream ofs;
        char buf[1024];

    public: 
        // init
        explicit file (std::string file_path);

        // destructor
        ~file();

        // get_function
        std::ofstream & get_ofs();
        int get_size();

        // set function 
        void set_size (int file_size);
};

#endif