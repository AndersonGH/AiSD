#include <cstddef>
#include <iostream>
#include <cstring>
#ifndef TREE_H
#define TREE_H

template <typename T> class tree{

    size_t size;
    size_t root;

public:
    T *data;
    tree();
    size_t get_size_tree();// вернет размер дерева
    size_t get_root();     //вернет индекс корня дерева
    void tree_insert(T field, size_t pos);// вставляем поле field на позицию pos в дереве
    void resize_tree(); // увеличивает размер дерева
    T tree_field(size_t pos);// возвращает элемент дерева
    bool empty(size_t pos);
    void makeTree(char *&in,size_t &index_in, size_t tree);// создает дерево
    void print(int &tabs,size_t tree);// печатает дерево
    size_t left(size_t father);// возвращает индекс правого поддерева
    size_t right(size_t father);// возвращает индекс левого поддерева
    void printF(size_t tree);// печатает формулу дерева T
    void prefix(size_t tree);// выводит дерево в префиксном виде
    void postfix(size_t tree);// выводит дерево в постфиксном виде
    void copy_tree(size_t tree, char *&copy,size_t &index_in);// копирует дерево, начиная с индекса index_in
    void open_brackets(size_t tree,bool &check_opened_br);// открывает скобки в дереве
    ~tree();


};


template <typename T> size_t tree <T>::get_size_tree(){
    return size;
}

template <typename T> void tree <T>::open_brackets(size_t tree,bool &check_opened_br){
    if(empty(tree))
        return;

    if(tree_field(tree) == '*'){
        if(tree_field((right(tree)))=='+' && tree_field((left(tree)))=='+'){
            check_opened_br = true; // если левое правое поддеревья знак
            tree_insert(tree_field(right(tree)),tree);

            T *copy1 = new T[size];// копия левого поддерева
            T *copy2 = new T[size];// копия левого поддервева правого поддерева корня дерева
            size_t index_in = 0;
            copy_tree(left(tree),copy1,index_in);
            copy1[index_in] = '\0';
            index_in = 0;
            copy_tree(left(right(tree)),copy2,index_in);
            copy2[index_in] = '\0';
            tree_insert('*',right(tree));
            tree_insert('*',left(tree));
            if(left(right(tree)) <=size){
                tree_insert('#',left(left(right(tree))));
                tree_insert('#',right(left(right(tree))));
                tree_insert('#',left(right(left(tree))));
                tree_insert('#',right(right(left(tree))));
            }
            index_in=strlen(copy1) - 1;
            makeTree(copy1,index_in,left(left(tree))); // вставляем скопируемые деревья
            index_in=strlen(copy1) - 1;
            makeTree(copy1,index_in,left(right(tree)));
            index_in=strlen(copy2) - 1;
            makeTree(copy2,index_in,right(left(tree)));

            delete [] copy1;
            delete [] copy2;
        }
        else if(tree_field((right(tree)))=='+'){
            check_opened_br = true;
            T *copy1 = new T[size];// копия левого поддерева корня
            T *copy2 = new T[size];// копия левого поддервева правого поддерева корня дерева
            size_t index_in = 0;


            tree_insert(tree_field(right(tree)),tree);
            copy_tree(left(tree),copy1,index_in); // копируем деревья
            copy1[index_in] = '\0';
            index_in = 0;
            copy_tree(left(right(tree)),copy2,index_in);
            copy2[index_in] = '\0';
            tree_insert('*',right(tree));
            tree_insert('*',left(tree));
            if(left(right(tree)) <=size){
                tree_insert('#',left(left(tree)));
                tree_insert('#',right(left(tree)));
                tree_insert('#',left(left(right(tree))));
                tree_insert('#',right(left(right(tree))));
            }
            index_in = strlen(copy1) -1;
            makeTree(copy1,index_in,left(left(tree))); // вставляем скопируемые деревья
            index_in = strlen(copy2) -1;
            makeTree(copy2,index_in,right(left(tree)));
            index_in = strlen(copy1) -1;
            makeTree(copy1,index_in,left(right(tree)));

            delete [] copy1;
            delete [] copy2;

        }
        else if(tree_field((left(tree)))=='+'){
            check_opened_br = true;
            T *copy1 = new T[size];// копия правого поддерева корня
            T *copy2 = new T[size];// копия правого поддервева левого поддерева корня дерева
            size_t index_in = 0;
            tree_insert(tree_field(left(tree)),tree);
            copy_tree(right(tree),copy1,index_in); // копируем деревья
            copy1[index_in] = '\0';
            index_in = 0;
            copy_tree(right(left(tree)),copy2,index_in);
            copy2[index_in] = '\0';
            tree_insert('*',right(tree));
            tree_insert('*',left(tree));
            if(left(right(tree)) <=size){
                tree_insert('#',left(right(tree)));
                tree_insert('#',right(right(tree)));
                tree_insert('#',left(right(left(tree))));
                tree_insert('#',right(right(left(tree))));
            }
            index_in = strlen(copy1) -1;
            makeTree(copy1,index_in,right(left(tree))); // вставляем скопируемые деревья
            index_in = strlen(copy1) -1;
            makeTree(copy1,index_in,right(right(tree)));
            index_in = strlen(copy2) -1;
            makeTree(copy2,index_in,left(right(tree)));
            delete [] copy1;
            delete [] copy2;

        }


    }
    open_brackets(left(tree),check_opened_br);
    open_brackets(right(tree),check_opened_br);

}

template <typename T> void tree <T>::copy_tree(size_t tree, char *&copy,size_t &index_in){
    if(empty(tree))
        return;

    copy_tree(left(tree),copy,index_in);
    copy_tree(right(tree),copy,index_in);
    copy[index_in]=tree_field(tree);
    index_in++;

}

template <typename T> void tree <T>::postfix(size_t tree){
    if(empty(tree))
        return;
    postfix(left(tree));
    postfix(right(tree));
    std::cout << tree_field(tree);
}

template <typename T> void tree <T>::prefix(size_t tree){
    if(empty(tree))
        return;
    std::cout << tree_field(tree);
    prefix(left(tree));
    prefix(right(tree));
}



template <typename T> void tree <T>::printF(size_t tree){

    if(empty(tree))
        return;

    if(size == 1){
        std::cout << tree_field(tree);
        return;
    }

    if(tree_field(tree) == '*'){
        std::cout << "(";
        if(isSign(tree_field(right(tree))) && isSign(tree_field(left(tree)))){
            printF(left(tree));
            std::cout << tree_field(tree);
            printF(right(tree));
        }
        else if(isSign(tree_field(right(tree)))){
            printF(left(tree));
            std::cout << tree_field(tree);
            printF(right(tree));
        }
        else if(isSign(tree_field(left(tree)))){
            printF(left(tree));
            std::cout << tree_field(tree);
            printF(right(tree));
        }
        else{
            printF(left(tree));
            std::cout << tree_field(tree);
            printF(right(tree));
        }
        std::cout << ")";
    }


    else if(isSign(tree_field(tree))){
        std::cout << "(";
        printF(left(tree));
        std::cout << tree_field(tree);
        printF(right(tree));
        std::cout << ")";
    }
    else
         std::cout << tree_field(tree);

}



template <typename T> void tree <T>::print(int &tabs,size_t tree){
 if (empty(tree))
     return;            //Если ветки не существует - выходим. Выводить нечего

 tabs++;             //Иначе увеличим счетчик рекурсивно вызванных процедур
                    //Который будет считать нам отступы для красивого вывода
 print(tabs,right(tree)); //Выведем ветку и ее подветки слева
 for (int i = 0; i<tabs; i++)
     std::cout << " ";       //Потом отступы

 std::cout << tree_field(tree) << std::endl; //Данные этой ветки
 print(tabs,left(tree));//И ветки, что справа
 tabs--; //После уменьшим кол-во отступов

}

template <typename T> tree <T>::~tree (){
    delete [] data;
}

template <typename T> size_t tree <T>::get_root(){
    return root;
}

template <typename T> void tree <T>::makeTree(char *&in,size_t &index_in, size_t tree){

    if( !empty(right(tree)) && !empty(left(tree)) )
        return;

    T field = in[index_in];
    index_in--;

    tree_insert(field,tree);

    if(!isSign(tree_field(tree)))
        return;
    makeTree(in,index_in,right(tree));
    makeTree(in,index_in,left(tree));

}

template <typename T> T tree <T>::tree_field(size_t father){
    return data[father];
}

template <typename T> size_t tree <T>::left(size_t father){
    return father*2 +1;
}

template <typename T> size_t tree <T>::right(size_t father){
    return father*2 +2;
}

template <typename T> bool tree <T>::empty(size_t pos){
    if(pos > size-1)
        return true;
    if(data[pos] == '#')
        return true;
    return false;
}

template <typename T> void tree <T>::resize_tree (){
    data[size]='\0';
    size_t last_size = size;
    T *copy = new T[size+1];
    strncpy(copy,data,size+1);
    delete [] data;
    size = size*2 + 1;
    data = new T [size+1];
    memset(data,'#',size+1);
    strncpy(data,copy,last_size);
    delete [] copy;
    data[size]='\0';

}

template <typename T> void tree <T>::tree_insert (T field, size_t pos){
    if(pos > size-1)
        resize_tree();

    data[pos] = field;

}



template <typename T> tree <T>::tree (){
    size = 1;
    data = new T[size+1];
    memset(data,'#',size+1);
    data[size] = '\0';
    root = 0;
}



#endif // TREE_H
