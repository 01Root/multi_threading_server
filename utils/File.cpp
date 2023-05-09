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
}
File::File(){}

// destructor
File::~File()
{
    ifs.close();
    recv_file.close();
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

char * File::read_file_content()
{
    ifs.open(file_path, std::ios::in);

    if (!ifs.is_open())
    {
        std::cout << "read fail" << std::endl;
    }


    while (ifs.getline(buf, sizeof(buf)))
    {
        // std::cout << buf << std::endl;
        return buf;
    }
}

std::ofstream& File::file_creation(char * file_name)
{
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
        strcat(cwd_buffer, file_name);
        recv_file.open(cwd_buffer, std::ios::out);
        return recv_file;
    }
}