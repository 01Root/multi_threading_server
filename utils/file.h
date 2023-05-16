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

    public: 
        // init
        explicit file () = delete;
        explicit file (std::string file_path);

        // copy, copy assign, move, move assign 
        file(const file &other) = delete;
        file & operator = (const file &other) = delete;
        file (file && other);
        file & operator = (const file &&other) = delete;

        // destructor
        ~file();

        // get_function
        std::ofstream & get_ofs();
        int get_size();

        // set function 
        void set_size (int file_size);
};

#endif