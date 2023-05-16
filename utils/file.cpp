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

//move
file::file(file && other)
{
    this->file_path = std::move(other.file_path);
    this->file_size = std::move(other.file_size);
    this->ofs = std::move(other.ofs);
}

// destructor
file::~file()
{
    try
    {
        ofs.close();
    }
    catch(...)
    {
        perror("close file fail!");
        exit(EXIT_FAILURE);
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


