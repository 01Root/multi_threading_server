#include <string>
#include <iostream>
#include <sys/stat.h> // for struct stat
#include <fstream>
#include <unistd.h>
#include <bits/stdc++.h> 

#include "file.h"

//init 


// constructor 
file::file (std::string file_path)
{
    this->file_path = file_path;

    // create a file
    const char* cfile_path = file_path.c_str();
    char cwd_buffer[1024] = {0};
    char * temp;
    if ((temp = getcwd(NULL, 0)) == NULL)
    {
        perror("getcwd fail");
        exit(EXIT_FAILURE);
    }
    else
    {
        strcat(cwd_buffer, temp);
        strcat(cwd_buffer, "/recved_files/");
        strcat(cwd_buffer, cfile_path);
        ofs.open(cwd_buffer, std::ios::out | std::ios::binary);
        if (!ofs)
        {
            perror("create file fail");
            exit(EXIT_FAILURE);
        }
    }
}
file::file(){}

// destructor
file::~file()
{
    ofs.close();
}

// get function 
std::ofstream & file::get_ofs()
{
    return this->ofs;
}
int file::get_size()
{
    return this->file_size;
}

// set function 
void file::set_size (int file_size)
{
    this->file_size = file_size;
}


