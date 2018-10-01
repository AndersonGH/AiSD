#include <iostream>
#include <stack>
#include "lisp.h"
#ifndef HEADER_H
#define HEADER_H

void numTostr(int num, char *str);
void syntax_check(class Lisp_Node *node,bool &check);
bool paste_node(class Lisp_Node *pred,class Lisp_Node *paste);
bool input(int argc, char* argv[], std:: stack <char> &brackets,char **in,int &len);
bool create_lisp(int len,char **in,class Lisp &lisp);
int isSign(char ch);
bool create_temp(char ch,std:: stack <class Lisp_Node *> &fathers,int &level,class Lisp_Node *father);
int check_for_number(char ch);
bool insert_atom_sign(class Lisp_Node *father,char sign);
bool insert_atom_num(class Lisp_Node *father,int num);
#endif // HEADER_H
