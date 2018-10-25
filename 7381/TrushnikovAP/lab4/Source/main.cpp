#include <iostream>
#include "stack.h"
#include "header.h"
#include "tree.h"
#include <vector>


int main(int argc, char* argv[]){
    char **in;
    char **postfix;
    std::vector <tree <char> *> trees;
    int first_len;
    int second_len;


    try {
        input(argc,argv,in,first_len,second_len);
    } catch (MyException e) {
        std::cout << e.get_what() << std::endl;
        for(int j =0; j < first_len; j++)
            if(in[j])
                delete [] in[j];

        return 0;
    }

    postfix = new char *[first_len];
    for(int j =0; j < first_len; j++)
        postfix[j] = nullptr;



    for(int j = 0 ; j < first_len; j++){
        if(in[j]){
            int tabs = 0;
            tree <char> *Tree = new tree <char>;
            trees.insert(trees.end(),Tree);
            infix_to_postfix(in[j],postfix[j]);

            size_t len = strlen(postfix[j])-1;
            Tree->makeTree(postfix[j],len,Tree->get_root());
            std::cout << std::endl;
            Tree->print(tabs,Tree->get_root());
        }
    }
    std::cout << std::endl;
    for(int j = 0; j < first_len;j++){
        if(in[j]){
            std::cout  << "Infix: " << in[j];
            std::cout  << " Postfix: " << postfix[j] << std::endl;
        }
    }


    for(int j =0; j < first_len; j++){
        if(in[j])
            delete [] in[j];
        if(postfix[j])
            delete [] postfix[j];
    }


    for(size_t j = 0; j < trees.size();j++){
        delete trees[j];
    }

    delete []postfix;
    delete []in;


    return 0;
}
