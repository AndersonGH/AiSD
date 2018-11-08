#include <iostream>
#include "header.h"
#include "tree.h"


int main(int argc, char* argv[]){
    Tree tree;
    Info *info;
    size_t info_size;
    std::string text;
    int tabs = 0;
    try {
    input(argc,argv,info,info_size,text); // считываю входящий текст
    }catch (MyException e) {
        std::cout << e.get_what() << std::endl; // если не удалось открыть файл
        return 0;
    }
    std::cout << "Symbols and their probabilities:" << std::endl; // вывожу символы и их вероятности встречания
    for(size_t j = 0;j < info_size; j++)
        if(info[j].symbol == ' ')
            std::cout << std::endl <<"space: " << info[j].freq;
        else
            std::cout << std::endl << info[j].symbol <<": " << info[j].freq;


    std::cout << std::endl<< std::endl  << "Starting to build a tree of characters: "<< std::endl << std::endl;
    tree.compression(tree.get_root(),3,info,0,info_size,info_size); // записываю шифры символов
    std::cout<< std::endl << "Printing tree: " << std::endl<< std::endl;
    tree.print(tabs,tree.get_root(),info);
    for(size_t j = 0; j < info_size; j++)
        info[j].cipher[info[j].cipher_index] = '\0';


    std::cout << std::endl << "Characters and their probabilities and cipher:" << std::endl; // вывожу символы с их шифром

    for(size_t j = 0;j < info_size; j++)
        if(info[j].symbol == ' ')
            std::cout << std::endl <<"space: " << info[j].freq << " cipher: " << info[j].cipher;
        else
            std::cout << std::endl << info[j].symbol <<": " << info[j].freq << " cipher: " << info[j].cipher;

    std::cout << std::endl << std::endl << "Source text:";// вывожу исходный текст
    std::cout << std::endl << text;

    std::cout << std::endl << std::endl << "Post-compression text:" << std::endl;
    for(size_t i = 0; i < text.size(); i++){ // вывожу защифрованный текст

        for(size_t j = 0; j < info_size;j++)
            if(text[i] == info[j].symbol)
                std::cout << info[j].cipher;
    }
    std::cout << std::endl;

    delete []info;
    return 0;
}
