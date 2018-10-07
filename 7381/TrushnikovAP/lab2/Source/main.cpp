#include <iostream>

#include "header.h"


int main(int argc, char* argv[]){
    Lisp lisp;
    int len_in=20;

    if(argc > 1){
        len_in=argc;
    }
    else
        argc = 0;

    char **in = new char* [len_in];


    if(!input(argc,argv,in,len_in)){ // функция считывания данных
        argc = 1;				     // вернет false при неправильной расстановке скобок
        std::cout <<"Oshibka skobok."<< std::endl << std::endl;		
	}		
    else{
        bool check = true;// индикатор корректности ариф выражения true если оно корректно
        lisp.create_lisp(len_in,in,lisp); //вызов  метода класса lisp для создания иерархического списка
        std::cout<<std::endl;
		if(len_in > 3){     //выполним проверку первого атома на наличие атома знака
			Lisp_Node *node = lisp.root;// если количество элементов ариф варажения больше 2

			if(node->is_Nill(node)) // если у нас певый элемент списка - Nill идем в право от него пока не встретим первый атом
				while(node->is_Nill(node))
					node = node->right;

			if(node->isAtom_num(node))//если первый атом число - выражение арифметическое некорректно
				check = false;
		}
		if(len_in == 4 )// если кол во элементов равно 4 значит это либо (знак) либо (число), что некорректно
			check = false;

        syntax_check(lisp.root,check);//вызов функции проверки на корректность иерархического списка

        if(check)
            std::cout << "Correct" << std::endl << std::endl;
        else
            std::cout << "Incorrect expression" << std::endl << std::endl;

    }

    if(argc == 0)
        for( int i = 0 ; i < len_in; i++){ // очищаем двумерный массив входных данных
            delete  [] in [i]; 			   // если память под него выделялась динамически
        }

    delete  [] in;

    Lisp_Node *del = lisp.root;
    if(del)				//вызов деструктора иерархического списка
        delete del;

    return 0;
}
