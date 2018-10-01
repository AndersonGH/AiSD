#include <iostream>

#include "header.h"


int main(int argc, char* argv[]){

    Lisp lisp;
    int len_in=30;
    std:: stack <char> Stack;

    if(argc>1)
        len_in=argc;

    char *in[len_in];


    if(!input(argc,argv,Stack,in,len_in))
        std::cout <<"Oshibka skobok. " ;
    else{
        //for(int i = 1;i<len_in;i++)
            //std::cout << in[i] << std::endl;


        create_lisp(len_in,in,lisp);


        bool check = true;
        if(lisp.root->isAtom_num(lisp.root)){
                std::cout << "Incorrect expression" << std::endl;
        }

        else{
            syntax_check(lisp.root,check);
        }
        if(check)
            std::cout << "Correct" << std::endl;
        else
            std::cout << "Incorrect expression" << std::endl;

    }

    /*
    for(int i = 1;i<len_in;i++)
        std::cout << in[i] << std::endl;
    */


    return 0;
}
