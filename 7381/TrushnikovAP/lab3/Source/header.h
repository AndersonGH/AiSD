#include <iostream>
#include "my_stack.h"
#include <vector>
#include <iterator>
#include <algorithm>
#ifndef HEADER_H
#define HEADER_H

void input(int argc, char* argv[],char * &in); // функция для считывания формулы
void resize(char * &str, int &len);			   // функция для увеличения размера char *
bool checkform(std::vector<int> &pos, char * &in);// функция проверки на корректность формулы
bool isSign(char ch); // функция возвращает true если считанный символ - знак
bool isName(char ch); // функция возвращает true если считанный символ - имя
bool O_bracket(char ch); // функция возвращает true если считанный символ - открывающая скобка
bool Cl_bracket(char ch); // функция возвращает true если считанный символ - закрывающая скобка
#endif // HEADER_H
