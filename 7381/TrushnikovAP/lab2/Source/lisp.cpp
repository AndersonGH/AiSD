#include "lisp.h"
#include "header.h"


bool Lisp::create_lisp(int len,char **in,class Lisp &lisp){
    char ch=' ';
    int i = len-1;
    int level = 0;
    std:: stack <class Lisp_Node *> fathers;

    while(1){
        ch=' ';
        while(i>0){

            ch = in[i][0];
            i--;
            break;
        }
        if(i==0)
            break;

        class Lisp_Node * father;
        if(i==len-2){
            class Lisp_Node * node = new Lisp_Node;
            node->atom(node);
            lisp.root = node;
            level++;
            fathers.push(node);
            continue;

        }

        else
            father = fathers.top();

        if(in[i][0] =='(' && ch == ')')
            insert_nill(father);
        else if(ch==')' || ch == '('){
            create_temp(ch,fathers,level,father);
        }
        else if(isdigit(ch)){
            int num = atoi(in[i+1]);
            insert_atom_num(father,num);
        }
        else if(isSign(ch))
            insert_atom_sign(father,ch);

    }


    return true;




}




bool Lisp_Node::creat_pair(Lisp_Node *s){
    s->s.tag = false;
    s->right=NULL;
    s->s.bottom=NULL;
    return true;
}

bool Lisp_Node::is_pair(Lisp_Node *s){

    return !s->s.tag;

}


bool Lisp_Node::is_Nill(Lisp_Node *s){
    return s->s.Nill;
}

bool Lisp_Node::Nill(Lisp_Node *s){
    s->s.Nill = true;
    s->right=NULL;
    s->s.bottom=NULL;
    return true;
}


bool Lisp_Node::atom(Lisp_Node *s){
    s->s.empty=true;
    s->s.tag = true;
    s->s.Nill = false;
    s->right=NULL;
    s->s.bottom=NULL;
    return true;
}
bool Lisp_Node::atom_sign(Lisp_Node *s,char ch){
    s->s.tag = true;
    s->s.Nill = false;
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
    s->s.Nill = false;
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
