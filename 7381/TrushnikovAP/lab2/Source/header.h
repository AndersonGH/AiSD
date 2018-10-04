#include <iostream>
#include <stack>
#include "lisp.h"
#ifndef HEADER_H
#define HEADER_H

void numTostr(int num, char *str);
void syntax_check(class Lisp_Node *node,bool &check);
void paste_node(class Lisp_Node *pred,class Lisp_Node *paste);
bool input(int argc, char* argv[],char **in,int &len);
bool isSign(char ch);
bool check_for_number(char ch);
#endif // HEADER_H
