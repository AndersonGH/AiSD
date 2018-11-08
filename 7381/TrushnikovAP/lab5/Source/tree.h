#include <iostream>
#include "header.h"
#include <cmath>
#ifndef TREE_H
#define TREE_H
class Tree_Node;

class Tree{
    Tree_Node * root;
public:
    // корень дерева
    Tree();
    void compression(Tree_Node *&,int,Info *&,size_t,size_t,size_t); // метод сжатия текста
    Tree_Node* &get_root(); // метод возращающий корень дерева
    void print(int &,Tree_Node *&,Info *&);
    ~Tree();
};

class Tree_Node{
    size_t INDEX_left; // индекс самого первого символа, хранящегося в дереве
    size_t INDEX_right;// идекс символа, перед которым хранится последний элемент в дереве
    Tree_Node * left; // указатель на левое поддерево
    Tree_Node * right;// указатель на правое поддерево

public:

    Tree_Node(size_t,size_t);
    Tree_Node* &get_left(); // метод возвращает указатель на левое поддерево
    Tree_Node* &get_right();// метод возвращает указатель на правое поддерево
    size_t get_INDEX_left();// метод возвращает индекс самого первого символа, хранящегося в дереве
    size_t get_INDEX_right();// метод возвращает идекс символа, перед которым хранится последний элемент в дереве

    ~Tree_Node();

};

#endif // TREE_H
