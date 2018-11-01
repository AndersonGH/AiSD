#include <iostream>
#include "header.h"
#include "tree.h"


int main(int argc, char* argv[]){
    char *in;
    char *postfix;
    int tabs = 0;
    int first_len;
    bool check_opened_br = true;

    try {
        input(argc,argv,in,first_len);
    } catch (MyException e) {
        std::cout << e.get_what() << std::endl;
        delete [] in;
        return 0;
    }


    postfix = new char[strlen(in)+1];
    memset(postfix,'\0',strlen(in)+1);
    tree <char> Tree;    

    infix_to_postfix(in,postfix);
    size_t len = strlen(postfix)-1;
    Tree.makeTree(postfix,len,Tree.get_root());
    std::cout << std::endl;
    while(check_opened_br){
        check_opened_br = false;
        Tree.open_brackets(Tree.get_root(),check_opened_br);
    }
    Tree.print(tabs,Tree.get_root());
    std::cout << "\nFormula T:" << std::endl;
    Tree.printF(Tree.get_root());
    std::cout << "\nPrefix:" << std::endl;
    Tree.prefix(Tree.get_root());
    std::cout << "\nPostfix:" << std::endl;
    Tree.postfix(Tree.get_root());
    std::cout << std::endl;

    delete []postfix;
    delete []in;


    return 0;
}
