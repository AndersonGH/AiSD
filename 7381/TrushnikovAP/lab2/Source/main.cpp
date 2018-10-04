#include <iostream>

#include "header.h"


int main(int argc, char* argv[]){

    Lisp lisp;
    int len_in=30;

    if(argc>1)
        len_in=argc;

    char *in[len_in];


    if(!input(argc,argv,in,len_in)){ // функция считывания данных
        std::cout <<"Oshibka skobok."<< std::endl << std::endl;
		
	}		// вернет false при неправильной расстановке скобок
    else{
        lisp.create_lisp(len_in,in,lisp); // метод класса lisp для создания иерархического списка
        bool check = true;

        if(lisp.root->isAtom_num(lisp.root)){
                std::cout << "Incorrect expression" << std::endl << std::endl;
				 return 0;
        }
        else{
            syntax_check(lisp.root,check);
        }
        if(check)
            std::cout << "Correct" << std::endl << std::endl;
        else
            std::cout << "Incorrect expression" << std::endl << std::endl;

    }

    return 0;
}
