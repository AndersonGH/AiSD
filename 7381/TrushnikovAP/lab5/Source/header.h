#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#ifndef HEADER_H
#define HEADER_H

class MyException{// класс используется для обработки исключений
    std::string str_what;
public:
    MyException(std::string);
    std::string get_what();
};

struct Info{
    char symbol;
    double freq;
    char cipher[100];
    size_t cipher_index;
};

int struct_cmp_by_freq(const void *a, const void *b);
void input(int argc, char* argv[],Info *&info,size_t &info_size,std::string&);
int cmp_double( const void *a, const void *b );
#endif // HEADER_H
