#include <iostream>
#include <stack>
#ifndef LISP_H
#define LISP_H
class Lisp{
public:
    class Lisp_Node *root;
    bool create_lisp(int len,char ** &in,class Lisp &lisp);
    void insert_atom_num(class Lisp_Node *father,int num);
    void create_temp(char ch,std::stack <class Lisp_Node *> &fathers,int &level,class Lisp_Node *father);
    void insert_atom_sign(class Lisp_Node *father,char sign);
    void insert_nill(class Lisp_Node *father);
    Lisp();// конструктор класса
    ~Lisp();// деструктор класса
};

class Lisp_Node{
public:
    struct s_expr{
        bool Nill;// true Nill
        bool tag; // true: atom, false: pair
        bool sign_check;//true sign, false num
        bool empty; // true empty
        int num;  // чсло атома
        char sign; // знак атома

    };
    class Lisp_Node *right;
    class Lisp_Node *bottom;
    s_expr s;

    void pair(Lisp_Node *s); // метод для создания pair
    void atom(Lisp_Node *s);       // метод создает пустой атом
    void atom_sign(Lisp_Node *s,char ch); // метод делает  атом атомом знака
    void atom_num(Lisp_Node *s,int num); // метод делает  атом атомом числа
    bool isAtom (Lisp_Node *s);          //метод возвращает true если это атом
    bool isEmptyAtom (Lisp_Node *s);    //метод возвращает true если это пустой атом
    bool isAtom_sign (Lisp_Node *s);   //метод возвращает true если это атом знака
    bool isAtom_num (Lisp_Node *s);    //метод возвращает true если это атом числа
    bool is_pair(Lisp_Node *s);        //метод возвращает true если это pair
    void Nill(Lisp_Node *s);          //метод  делает  атом Nill
    bool is_Nill(Lisp_Node *s);         //метод возвращает true если это Nill

    friend Lisp;

    ~Lisp_Node(); // деструктор класса

};

#endif // LISP_H
