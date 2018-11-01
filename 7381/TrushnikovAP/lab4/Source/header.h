#include <iostream>
#include "stack.h"
#include <cstring>

#define INPUT_SIZE 10
#ifndef HEADER_H
#define HEADER_H
void input(int argc, char* argv[],char * &in, int &first_len); // функция, считывающая формулу T
void resize(char * &str, int &len);// функция, увеличивающая размер массива
void infix_to_postfix(char*&in, char*&postfix);// функция, трансформирующая инфиксную форму в постфиксную
int precedence(char ch);// функия, возвращающая значение от 1 до 3 в зависимости от важности знака
bool isSign(char ch);// вернет true если ch это знак
bool check (char ch);// функция, проверяющая корректность считываемого символа

class MyException{// класса используется для обработки исключений
    std::string str_what;
public:
    MyException(std::string);
    std::string get_what();
};


#endif // HEADER_H
