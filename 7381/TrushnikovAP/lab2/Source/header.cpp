#include "header.h"
#include <vector>
#include <cstring>



void numTostr(int num, char *str){
    int i =0;
    int divider=1;

    if(num>9)
        while(num/divider!=1){
            divider*=10;
        }

    while(divider!=0){
        int res;
        res = num/divider;
        if(res>=10)
            res %=10;

        char ch = res +'0';
        str[i] = ch;

        divider/=10;
        i++;
    }
    str[i] = '\0';

}

void syntax_check(class Lisp_Node *node,bool &check){
    if(node == NULL)
        return;

    if(node->is_pair(node) && !node->is_Nill(node)){
        std::cout<< "is pair" << std::endl;
    }
    else if(node->is_Nill(node)){
        std::cout<< "Nill "<< std::endl;

    }
    else if(node->isAtom_num(node)){
        std::cout<< "atom: " << node->s.num << std::endl;

    }
    else if(node->isAtom_sign(node)){
        std::cout<< "atom: " << node->s.sign << std::endl;
        if(node->s.sign == '/')
            if(node->right!=NULL && node->right->isAtom_num(node->right))
                if(node->right->s.num == 0)
                    check = false;

    }

    if(node->is_pair(node) && node->s.bottom!=NULL){
        if(node->s.bottom->is_Nill(node->s.bottom)){
            Lisp_Node * nill;
            nill = node->s.bottom;
            if(nill->right !=NULL)
                while(nill->right->is_Nill(nill->right))
                    nill=nill->right;


            if(nill->right!=NULL)
                if(nill->right->isAtom_num(nill->right))
                    check = false;
        }
        else{
            if(node->s.bottom->isAtom_num(node->s.bottom))
                check = false;
        }



    }



    syntax_check(node->s.bottom,check);
    syntax_check(node->right,check);


    return;
}


bool paste_node(class Lisp_Node *pred,class Lisp_Node *paste){

    class Lisp_Node *copy = new Lisp_Node;
    copy=pred->right;
    pred->right=paste;
    paste->right=copy;

    return true;

}

bool insert_nill(class Lisp_Node *father){

    if(father->isEmptyAtom(father) && !father->is_Nill(father))
        father->Nill(father);
    else{
        while(father->right!=NULL)
            father=father->right;

        class Lisp_Node *node = new Lisp_Node;
        node->Nill(node);
        father->right=node;

    }
    return true;
}

bool insert_atom_sign(class Lisp_Node *father,char sign){

    if(father->isEmptyAtom(father) && !father->is_Nill(father))
        father->atom_sign(father,sign);
    else{
        while(father->right!=NULL)
            father=father->right;

        class Lisp_Node *node = new Lisp_Node;
        node->atom_sign(node,sign);
        father->right=node;

    }
    return true;
}

bool insert_atom_num(class Lisp_Node *father,int num){

    if(father->isEmptyAtom(father) && !father->is_Nill(father))
        father->atom_num(father,num);

    else{
        while(father->right!=NULL)
            father=father->right;

        class Lisp_Node *node = new Lisp_Node;
        node->atom_num(node,num);
        father->right=node;

    }
    return true;
}

bool create_temp(char ch,std::stack <class Lisp_Node *> &fathers,int &level,class Lisp_Node *father){


    if(ch == ')'){
        level++;
        class Lisp_Node *node = new Lisp_Node;
        fathers.push(node);

        if(level - 1 !=0)
            node->creat_pair(node);


        if(father->right!=NULL && father->s.tag== true){
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



    return true;
}






void resize(int len,char *in[]){
    int l_copy = len;
    char *copy[l_copy];
    for(int i =0;i<len;i++){
        if(strlen(in[i]) == 1)
            copy[i] = new char [2];
        else
            copy[i] = new char [100];
        strcpy(copy[i],in[i]);
    }

    for(int i =0;i<len;i++){

        delete in[i];
    }
    //delete in;

    len=len*2;
    in = new char* [len];
    for(int i =0;i<l_copy;i++){
        if(strlen(copy[i]) == 1)
            in[i] = new char [2];
        else
            in[i] = new char [100];

        strcpy(in[i],copy[i]);
    }

    for(int i =0;i<l_copy;i++){
        delete copy[i];
    }




}

bool input(int argc, char* argv[], std:: stack <char> &brackets,char **in,int &len){
   bool check_for_brackets=true;
   if(argc > 1){
    char ch;
       for(int i=1; i < argc; i++){
           ch= *argv[i];

           if(ch == '('){

                    check_for_brackets=false;
                    brackets.push('(');

                }
            else if(ch == ')'){
                if(brackets.empty()){
                    return false;
                }
                if(brackets.top() == '(')
                    brackets.pop();

            }

     }
       for(int i =1 ;i<argc;i++){
           in[i]=argv[i];
       }
   }

    else{
        int num,i=1;
        char ch;

        while(1){

            if(i+1>len){
                resize(len,in);
            }

            std::cin >> ch;

            if(check_for_number(ch)){
                std::cin.unget();
                std::cin >> num;
                char str[100];
                numTostr(num, str);
                str[strlen(str)] = '\0';

                in[i] = new char[100];
                strcpy(in[i],str);
                in[i][strlen(in[i])] = '\0';
                i++;



                if(std::cin.peek() == '\n'){
                    len = i;
                    break;
                }
                continue;

            }
            else{


                if(ch == '('){
                    check_for_brackets=false;
                    brackets.push('(');
                }
                else if(ch == ')'){
                    if(brackets.empty()){
                        return false;
                    }
                    if(brackets.top() == '(')
                        brackets.pop();
                 }
                char str1[2];
                str1[0]=ch;
                str1[1]='\0';

                in[i] = new char [1];
                strcpy(in[i],str1);

                i++;

                if(std::cin.peek() == '\n'){
                    if(!brackets.empty()){
                        return false;
                    }
                    len = i;
                    break;
                }
                continue;

            }

        }

   }
   if(check_for_brackets)
       return false;
   return true;
}
int isSign(char ch){
    if(ch=='+' || ch == '-' || ch == '/' || ch == '*')
        return 1;
    else
        return 0;
}
int check_for_number(char ch){
    if((isdigit(ch)) || (isSign(ch) && std::cin.peek() != ' ' &&std::cin.peek() != '\n')
       && std::cin.peek()!='(' && std::cin.peek() != ')')
        return 1;

    return 0;
}
