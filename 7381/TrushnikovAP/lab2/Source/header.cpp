#include "header.h"
#include <vector>
#include <cstring>

void numTostr(int num, char *str){ // функция преобразования int в char*
    int i =0;
    bool neg = false;
    int divider=1;
    int count = 1;
    if(num < 0){ // если число отрицаиельное делаем его положительным
        num=abs(num);
        neg = true;
        i++;
    }

    if(num>9){  // если число больше девяти определяем количество десятков в нем
        while(count !=0){
            divider*=10;
            count = num/divider;

        }
    divider/=10;
    }
    while(divider!=0){ // предобразовываем число в строку
        int res;
        res = num/divider;
        if(res>=10)
            res %=10;

        char ch = res +'0';
        str[i] = ch;

        divider/=10;
        i++;
    }
    if(neg)
        str[0] = '-';
    str[i] = '\0';

}

void syntax_check(class Lisp_Node *node,bool &check){//функция для проверки на корректность ариф выражения
    if(node == NULL){
        std::cout<< "Null" << std::endl;
        return;
    }

    if(node->is_pair(node)){
        std::cout<< "is pair" << std::endl;
    }
    else if(node->is_Nill(node)){
        std::cout<< "Nill "<< std::endl;
    }
    else if(node->isAtom_num(node)){
        std::cout<< "atom num: " << node->s.num << std::endl;
    }
    else if(node->isAtom_sign(node)){
        std::cout<< "atom sign: " << node->s.sign << std::endl;
    }

    if(node->isAtom_sign(node) && check){ // если встретили знак деления проверяем нету ли нуля правее него
        if(node->s.sign == '/'){
            Lisp_Node *error = node;
            while(error != NULL){
                if(error->isAtom_num(error) && error->s.num == 0){
                    check = false;
                    break;
                }
                error = error->right;
            }

        }


    }

    if(node->isAtom_num(node) && check){   //если встретили число проверяем нету ли знака правее него
         Lisp_Node *error = node;
         while(error != NULL){
             if(error->isAtom_sign(error)){
                 check = false;
                 break;
             }
             error = error->right;
         }


    }

    if(node->is_pair(node) ){ // если встретили pair проверяем является ли его нижний элемент знаком
        if(node->right == NULL)
            check = false;

        if(node->is_Nill(node->bottom)){
            Lisp_Node *error = node->bottom;
            while(error->is_Nill(error)){
                error = error->right;
                if(error == NULL){
                    check = false;
                    break;
                }
            }
            if(check){
                if(error->isAtom_num(error) || error->is_pair(error))
                    check = false;

            }

        }
    }

    std::cout << "go bottom -> ";
    syntax_check(node->bottom,check);
    std::cout << "go right  -> ";
    syntax_check(node->right,check);


    return;
}


void paste_node(class Lisp_Node *pred,class Lisp_Node *paste){ // функция вставляет атом или pair между двумя другими

    class Lisp_Node *copy = new Lisp_Node;
    copy=pred->right;
    pred->right=paste;
    paste->right=copy;
}


void resize(int &len,char ** &in){// функция увеличения размера двумерного массива
    int l_copy = len;

    char **copy = new char* [l_copy];

    for(int i =1;i<len;i++){
        if(strlen(in[i]) == 1)
            copy[i] = new char [2];
        else
            copy[i] = new char [100];
        strcpy(copy[i],in[i]);
    }

    for(int i = 0;i<len;i++){
         delete [] in[i];
    }
    delete  [] in;

    len=len*2;
    in = new char* [len];
    for(int i =1;i<l_copy;i++){
        if(strlen(copy[i]) == 1){
            in[i] = new char [2];
            strcpy(in[i],copy[i]);
        }
        else{
            in[i] = new char [100];
            strcpy(in[i],copy[i]);
        }



    }

    for(int i =0;i<l_copy;i++){
        delete [] copy[i];
    }
    delete  [] copy;
}

bool input(int argc, char* argv[],char ** &in,int &len){

   std:: stack <char> brackets;
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
bool isSign(char ch){
    if(ch=='+' || ch == '-' || ch == '/' || ch == '*')
        return true;
    else
        return false;
}
bool check_for_number(char ch){
    if((isdigit(ch)) || (isSign(ch) && std::cin.peek() != ' ' &&std::cin.peek() != '\n')
       && std::cin.peek()!='(' && std::cin.peek() != ')')
        return true;

    return false;
}
