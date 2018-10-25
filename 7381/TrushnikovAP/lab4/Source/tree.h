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
    size_t get_root();
    void tree_insert(T field, size_t pos);
    void resize();
    T tree_field(size_t pos);
    bool empty(size_t pos);
    void makeTree(char *&in,size_t &index_in, size_t tree);
    void print(int &tabs,size_t tree);
    size_t left(size_t father);
    size_t right(size_t father);
    ~tree();


};



template <typename T> void tree <T>::print(int &tabs,size_t tree){
 if (empty(tree))
     return;            //Если ветки не существует - выходим. Выводить нечего

 tabs++;             //Иначе увеличим счетчик рекурсивно вызванных процедур
                    //Который будет считать нам отступы для красивого вывода

 print(tabs,left(tree)); //Выведем ветку и ее подветки слева

 for (int i = 0; i<tabs; i++)
     std::cout << " ";       //Потом отступы

 std::cout << tree_field(tree) << std::endl; //Данные этой ветки


 print(tabs,right(tree));//И ветки, что справа

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

    if(empty(tree))
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

template <typename T> void tree <T>::resize (){

    size_t last_size = size;
    T *copy = new T[size+1];
    strncpy(copy,data,size+1);
    delete [] data;
    size = size*2 + 1;
    data = new T [size+1];
    memset(data,'#',size+1);
    data[size]='\0';
    strncpy(data,copy,last_size);


}

template <typename T> void tree <T>::tree_insert (T field, size_t pos){
    if(pos > size-1)
        resize();

    data[pos] = field;

}



template <typename T> tree <T>::tree (){
    size = 3;
    data = new T[size+1];
    memset(data,'#',size+1);
    data[size] = '\0';
    root = 0;
}

#endif // TREE_H
