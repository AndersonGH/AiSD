#include "lisp.h"
#include "header.h"

bool Lisp::create_lisp(int len,char **in,class Lisp &lisp){
    char ch=' ';
    int i = len-1;
    int level = 0;
    std::stack <class Lisp_Node *> fathers;

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

        if(in[i][0] =='(' && ch == ')'){
            i--;
            lisp.insert_nill(father);
        }
        else if(ch==')' || ch == '('){
            lisp.create_temp(ch,fathers,level,father);
        }
        else if(isdigit(ch)){
            int num = atoi(in[i+1]);
            lisp.insert_atom_num(father,num);
        }
        else if(isSign(ch))
            lisp.insert_atom_sign(father,ch);
    }

    return true;
}

void Lisp_Node::creat_pair(Lisp_Node *s){
    s->s.tag = false;
    s->s.empty = false;
    s->right=NULL;
    s->s.bottom=NULL;
}
void Lisp::insert_nill(class Lisp_Node *father){

    if(father->isEmptyAtom(father) && !father->is_Nill(father))
        father->Nill(father);
    else{
        while(father->right!=NULL)
            father=father->right;

        class Lisp_Node *node = new Lisp_Node;
        node->Nill(node);
        father->right=node;

    }
}


void Lisp::insert_atom_sign(class Lisp_Node *father,char sign){

    if(father->isEmptyAtom(father) && !father->is_Nill(father))
        father->atom_sign(father,sign);
    else{

        if(father->is_Nill(father)){

        Lisp_Node * check = father;
        while(check->right!=NULL)
            check=check->right;

        class Lisp_Node *node = new Lisp_Node;
        node->atom_sign(node,sign);
        father = check;
        check->right=node;
        }
        else{
            while(father->right!=NULL)
                father=father->right;

            class Lisp_Node *node = new Lisp_Node;
            node->atom_sign(node,sign);
            father->right=node;
        }



    }

}

bool Lisp_Node::is_pair(Lisp_Node *s){
    if(!s->s.tag && !s->s.empty)
        return true;
    return false;
}

void Lisp::create_temp(char ch,std::stack <class Lisp_Node *> &fathers,int &level,class Lisp_Node *father){
    if(ch == ')'){
        level++;
        class Lisp_Node *node = new Lisp_Node;
        fathers.push(node);

        if(level - 1 !=0)
            node->creat_pair(node);

        if(father->is_Nill(father)&&father->right!=NULL)
            father=father->right;
        if(father->right!=NULL){
            paste_node(father,node);
        }

        else {
            while(father->right!=NULL)
                father=father->right;
            father->right=node;
        }

        if(level - 1 !=0){
            class Lisp_Node *node_b = new Lisp_Node;
            node_b->atom(node_b);

            fathers.push(node_b);

            node->s.bottom=node_b;
        }

    }
    else{
        if(level - 1 !=0 && !father->is_Nill(father)){
            int j = level -1;
            while(j>0){
                fathers.pop();
                j--;
            }
        }
        level--;
    }
}


void Lisp::insert_atom_num(class Lisp_Node *father,int num){

    if(father->isEmptyAtom(father) && !father->is_Nill(father))
        father->atom_num(father,num);

    else{
        while(father->right!=NULL)
            father=father->right;

        class Lisp_Node *node = new Lisp_Node;
        node->atom_num(node,num);
        father->right=node;

    }
}


bool Lisp_Node::is_Nill(Lisp_Node *s){
    if(!s->s.tag && s->s.empty)
        return true;
    else
        return false;
}

void Lisp_Node::Nill(Lisp_Node *s){
    s->s.tag = false;
    s->s.empty=true;
    s->right=NULL;
    s->s.bottom=NULL;
}


void Lisp_Node::atom(Lisp_Node *s){
    s->s.empty=true;
    s->s.tag = true;
    s->right=NULL;
    s->s.bottom=NULL;
}

void Lisp_Node::atom_sign(Lisp_Node *s,char ch){
    s->s.tag = true;
    s->s.empty=false;
    s->s.sign_check=true;
    s->s.sign=ch;
    s->right=NULL;
    s->s.bottom=NULL;
}

bool Lisp_Node::isAtom_num(Lisp_Node *s){
    return !s->s.sign_check;
}
bool Lisp_Node::isEmptyAtom(Lisp_Node *s){
    return s->s.empty;
}

bool Lisp_Node::isAtom_sign(Lisp_Node *s){
    if(s->s.sign_check && !s->s.empty && s->s.tag)
        return true;
    return false;
}

void Lisp_Node::atom_num(Lisp_Node *s,int num){
    s->s.tag = true;
    s->s.empty=false;
    s->s.sign_check=false;
    s->s.num=num;
    s->right=NULL;
    s->s.bottom=NULL;
}

bool Lisp_Node::isAtom (Lisp_Node *s){
    if(s->s.tag)
        return true;
    else
        return false;
}
