#include "my_stack.h"

void mystack::print(){ // метод, печатающий стек
    bool printed = false;
    mystack_elem *out = root;
    if(out)
        std::cout << "Stack contents ";
    while(out!=nullptr){ // печатем пока не дойдем до последнего элемента
        printed = true;
        std::cout << "---> ";
        std::cout << out->field << " ";
        out=out->right;
    }
    if(printed)// печатаем симол окончания строки, если стек был напечатан
        std::cout<<std::endl;

}
mystack::~mystack(){ // деструктор стека
    delete root;
}

mystack_elem::~mystack_elem(){ // дестуктор элемента стека
    if(right)
        delete right;
}

mystack::mystack(){// конструктор стека
    this->size = 0;
    this->root = NULL;
}

mystack_elem::mystack_elem(char field){ // конструктор элемента класса
    this->field = field;
}

int mystack::size_s(){
    return size;
}

bool mystack::empty(){// возвращает false - полон
    if(size <= 0)
        return true;
    return false;
}
void mystack::push(char field){ 
    mystack_elem * elem = new mystack_elem(field); // создаем новый элемент стека
    elem->right = this->root; // указатель корня стека теперь указывает на созданный элемент
    this->root = elem;
    size++;
}
char mystack::top(){
    if(size <= 0)
        return false;
    return this->root->field; // возвращает элемент лежащий на вершине стека
}

char mystack::pop(){
    if(size <= 0)
       return 0;

    char ch;
    ch = this->root->field; // сохраняем поле элемента лежащего на вершине стека
    mystack_elem * elem = this->root; // преставляем указатель корня на след элемент в стеке

    this->root = this->root->right;
    elem->right = nullptr;
    delete elem; // удаляем элемент

    size--; // уменьшаяем размер стека
    return ch;
}
