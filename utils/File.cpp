#include <string>
#include <iostream>
#include <sys/stat.h> // for struct stat
#include <fstream>
#include <unistd.h>
#include <bits/stdc++.h> 

#include "File.h"

// constructor 
File::File (std::string file_path)
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
        // return recv_file;
    }
}
File::File(){}

// destructor
File::~File()
{
    ofs.close();
}

// get function 
std::ofstream & File::get_ofs()
{
    return this->ofs;
}
int File::get_size()
{
    return this->file_size;
}

// set function 
void File::set_size (int file_size)
{
    this->file_size = file_size;
}

std::string File::get_file_name()
{
    std::string::size_type iPos = file_path.find_last_of('/') + 1;
    std::string file_name = file_path.substr(iPos, file_path.length() - iPos);
    return file_name;
}

int File::get_file_size()
{
    char * cfile_path = (char *) file_path.data();
    if (NULL == cfile_path)
    {
        return 0;
    }

    struct stat statbuf;
    stat (cfile_path, &statbuf);
    size_t file_size = statbuf.st_size;
    return file_size;
}
