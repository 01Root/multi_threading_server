#include <string>
#include <iostream>
#include <sys/stat.h> // for struct stat
#include <fstream>
#include <unistd.h>
#include <bits/stdc++.h> 

#include "./file.h"

//init 
file::file (std::string file_path):file_size(0), file_path(file_path), close_status(false)
{
    // create a file
    const char* cfile_path = file_path.c_str();
    char cwd_buffer[1024] = {0};
    char * temp = nullptr; 
    if ((temp = getcwd(NULL, 0)) == NULL)
    {
        exception_hander::print_and_exit("getcwd fail.");
    }
    else
    {
        strcat(cwd_buffer, temp);
        strcat(cwd_buffer, "/recved_files/");
        strcat(cwd_buffer, cfile_path);
        ofs.open(cwd_buffer, std::ios::out | std::ios::binary);
        if (!ofs)
        {
            exception_hander::print_and_exit("create file fail.");
        }
    }
}

//move
file::file(file && other)
{
    this->file_path = std::move(other.file_path);
    this->file_size = std::move(other.file_size);
    this->ofs = std::move(other.ofs);
}

// closed
void file::closed()
{
    this->ofs.close();
    this->close_status = true;
}

// destructor
file::~file()
{
    if (!this->close_status)
    {
        try
        {
            this->ofs.close();
        }
        catch(...)
        {
            exception_hander::print_and_exit("close file fail.");
        }
    }
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


