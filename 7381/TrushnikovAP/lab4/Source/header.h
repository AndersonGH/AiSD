#include <iostream>
#include "stack.h"
#include <cstring>

#define FIRST_INPUT_SIZE 1
#define SECOND_INPUT_SIZE 10
#ifndef HEADER_H
#define HEADER_H
void input(int argc, char* argv[],char ** &in, int &first_len, int &second_len);
void resize1(char * &str, int &len);
void infix_to_postfix(char*&in, char*&postfix);
int precedence(char ch);
bool isSign(char ch);
void resize2(int &len,char ** &in);
bool check (char ch);
class MyException{
    std::string str_what;
public:
    MyException(std::string);
    std::string get_what();
};


#endif // HEADER_H
