#ifndef FILE_H
#define FILE_H
#pragma once

#include <string>
#include <fstream>

class File
{
    private: 
        int file_size;
        std::string file_path;
        std::ofstream ofs;
        char buf[1024] = {0};

    public: 
        // constructor
        File();
        File (std::string file_path);

        // destructor
        ~File();

        // get_function
        std::ofstream & get_ofs();
        int get_size();

        // set function 
        void set_size (int file_size);

        // function 
        
        std::string get_file_name();
        int get_file_size();
        char * read_file_content();\
        std::ofstream& file_creation(char * file_name);
};

#endif