#include "lisp.h"

bool Lisp_Node::creat_pair(Lisp_Node *s){
    s->s.tag = false;
    s->right=NULL;
    s->s.bottom=NULL;
    return true;
}

bool Lisp_Node::is_pair(Lisp_Node *s){

    return !s->s.tag;

}

bool Lisp_Node::atom(Lisp_Node *s){
    s->s.empty=true;
    s->s.tag = true;
    s->right=NULL;
    s->s.bottom=NULL;
    return true;
}
bool Lisp_Node::atom_sign(Lisp_Node *s,char ch){
    s->s.tag = true;
    s->s.empty=false;
    s->s.sign_check=true;
    s->s.sign=ch;
    s->right=NULL;
    s->s.bottom=NULL;
    return true;
}
bool Lisp_Node::isAtom_num(Lisp_Node *s){

    return !s->s.sign_check;
}
bool Lisp_Node::isEmptyAtom(Lisp_Node *s){

    return s->s.empty;
}

bool Lisp_Node::isAtom_sign(Lisp_Node *s){

    return s->s.sign_check;
}
bool Lisp_Node::atom_num(Lisp_Node *s,int num){
    s->s.tag = true;
    s->s.empty=false;
    s->s.sign_check=false;
    s->s.num=num;
    s->right=NULL;
    s->s.bottom=NULL;
    return true;
}
bool Lisp_Node::isAtom (Lisp_Node *s){
    if(s->s.tag)
        return true;
    else
        return false;
}
