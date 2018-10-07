#include <iostream>
#include <stack>
#include "lisp.h"
#ifndef HEADER_H
#define HEADER_H

void resize(int &len,char ** &in); // функция увеличения размера двумерного массива
void numTostr(int num, char *str); //функция преобразовывает int в char *
void syntax_check(class Lisp_Node *node,bool &check);//функция для проверки на корректность ариф выражения
void paste_node(class Lisp_Node *pred,class Lisp_Node *paste);// функция вставляет атом или pair между двумя другими
bool input(int argc, char* argv[],char ** &in,int &len);// функция для считывания входной строки
bool isSign(char ch);// вернет true если char знак
bool check_for_number(char ch);// проверяет наличие числа во входном потоке
#endif // HEADER_H
