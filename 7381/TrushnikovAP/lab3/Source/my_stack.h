#include <iostream>

#ifndef MY_STACK_H
#define MY_STACK_H
class mystack_elem;

class mystack{   		
public:
    mystack_elem * root; //указатель на вершину стека
    int size;			// рзмер стека
    void push(char bracket); // метод, кладущий элемент в стек
    char pop();				 // метод, попоющий элемент из стека
    char top();			     // метод, возвращающий вершину стека
    bool empty();			 //метод, возвращающий true если стек не пуст
    int size_s();			 //метод, возвращающий разиер стека
    void print();
    mystack();				 // кнструктор класса
    ~mystack();				 // деструктор класса

};



class mystack_elem{
public:
    mystack_elem(char); // конструктор класса 
    mystack_elem * right; // указатель на следующий элемент стека
    char field; // поле элемента стека

    ~mystack_elem(); // деструктор класса
};

#endif // MY_STACK_H
