#include <iostream>
#include <stack>
#ifndef LISP_H
#define LISP_H
class Lisp{
public:
    class Lisp_Node *root;
    bool create_lisp(int len,char **in,class Lisp &lisp);
    bool insert_atom_num(class Lisp_Node *father,int num);
    bool create_temp(char ch,std::stack <class Lisp_Node *> &fathers,int &level,class Lisp_Node *father);
    bool insert_atom_sign(class Lisp_Node *father,char sign);
    bool insert_nill(class Lisp_Node *father);
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

    bool creat_pair(Lisp_Node *s); // метод для создания pair
    bool atom(Lisp_Node *s);       // создает пустой атом
    bool atom_sign(Lisp_Node *s,char ch); // делает  атом атомом знака
    bool atom_num(Lisp_Node *s,int num); // делает  атом атомом числа
    bool isAtom (Lisp_Node *s);          // возвращает true если это атом
    bool isEmptyAtom (Lisp_Node *s);    // возвращает true если это пустой атом
    bool isAtom_sign (Lisp_Node *s);   // возвращает true если это атом знака
    bool isAtom_num (Lisp_Node *s);    // возвращает true если это атом числа
    bool is_pair(Lisp_Node *s);        // возвращает true если это pair
    bool Nill(Lisp_Node *s);          //  делает  атом Nill
    bool is_Nill(Lisp_Node *s);         // возвращает true если это Nill

    friend Lisp;

};

#endif // LISP_H
