#ifndef FILE_H
#define FILE_H
#pragma once

#include <string>
#include <fstream>

class File
{
    private: 
        std::string file_path;
        std::ofstream recv_file;
        std::ofstream ofs;
        char buf[1024] = {0};

    public: 
        // constructor
        File();
        File (std::string file_path);

        // destructor
        ~File();

        // copy 
        // void operator= (File& other);

        // get_function
        std::ofstream & get_ofs();

        // function 
        
        std::string get_file_name();
        int get_file_size();
        char * read_file_content();\
        std::ofstream& file_creation(char * file_name);
};

#endif