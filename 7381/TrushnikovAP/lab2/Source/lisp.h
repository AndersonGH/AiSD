#include <iostream>
#ifndef LISP_H
#define LISP_H

/*
class lisp
{
public:
    lisp();
};
*/


class Lisp{


public:
    class Lisp_Node *root;

};

class Lisp_Node{
public:
    struct s_expr{
        bool tag; // true: atom, false: pair
        class Lisp_Node *bottom;
        bool sign_check;//true sign, false num
        bool empty; // true empty
        int num;
        char sign;

    };
    class Lisp_Node *right;
    s_expr s;

    bool creat_pair(Lisp_Node *s);
    bool atom(Lisp_Node *s);
    bool atom_sign(Lisp_Node *s,char ch);
    bool atom_num(Lisp_Node *s,int num);
    bool isAtom (Lisp_Node *s);
    bool isEmptyAtom (Lisp_Node *s);
    bool isAtom_sign (Lisp_Node *s);
    bool isAtom_num (Lisp_Node *s);
    bool is_head(Lisp_Node *s);
    bool is_pair(Lisp_Node *s);

    friend Lisp;

};

#endif // LISP_H
