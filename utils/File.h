#pragma once
#include <string>
#include <fstream>

class File
{
    private: 
        std::string file_path;
        std::ifstream ifs;
        std::ofstream recv_file;
        char buf[1024] = {0};

    public: 
        // constructor
        File();
        File (std::string file_path);

        // destructor
        ~File();

        // function 
        
        std::string get_file_name();
        int get_file_size();
        char * read_file_content();\
        std::ofstream& file_creation(char * file_name);
};