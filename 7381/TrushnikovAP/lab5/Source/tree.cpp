#include "tree.h"
#include "header.h"
Tree::Tree(){
    this->root = nullptr;
}


Tree::~Tree(){
    delete get_root();
}


Tree_Node::~Tree_Node(){
    delete left;
    delete right;
}


Tree_Node*& Tree::get_root(){
    return this->root;
}

Tree_Node*& Tree_Node::get_left(){
    return left;
}

Tree_Node*& Tree_Node::get_right(){
    return right;
}

Tree_Node::Tree_Node(size_t left,size_t right){
    this->INDEX_left = left;
    this->INDEX_right = right;
    this->left = nullptr;
    this->right = nullptr;

}

size_t Tree_Node::get_INDEX_left(){
    return this->INDEX_left;
}

size_t Tree_Node::get_INDEX_right(){
    return this->INDEX_right;
}

void Tree::compression(Tree_Node *  &father,int bit,Info * &info,size_t l,size_t r, size_t info_size){
    size_t mid=l;
    double sum1;
    double sum2;
    size_t last[2];

    if(father == nullptr){ // создаю новый элемнт дерева
        father = new Tree_Node (l,r);
        std::cout << "Insert: ";
        for(size_t j = l; j < r; j++){
            if(info[j].symbol == ' ')
                std::cout << "space";
            else
                std::cout << info[j].symbol;
        }
        std::cout << std::endl;
    }

    if(bit!=3 || (bit==3 && info_size == 1)){ // сохраняю шифры для символов
        for(size_t j = 0; j < info_size;j++){
            for(size_t i = father->get_INDEX_left(); i < father->get_INDEX_right();i++){
                if(info[j].symbol == info[i].symbol){
                    if(bit == 0 || bit == 3){  // если текущий бит 0 или 3 то добавляю 0 к шифру символа
                        info[j].cipher[info[j].cipher_index] = '0';
                        info[j].cipher_index +=1;
                        if(info[j].symbol == ' ')
                            std::cout << "Added a 0 to the cipher of 'space'" << std::endl;
                        else
                            std::cout << "Added a 0 to the cipher of '" << info[j].symbol << "'" << std::endl;
                    }
                    else{       // если текущий бит 1 то добавляю 1 к шифру символа
                        info[j].cipher[info[j].cipher_index] = '1';
                        info[j].cipher_index +=1;
                        if(info[j].symbol == ' ')
                            std::cout << "Added a 1 to the cipher of 'space'" << std::endl;
                        else
                            std::cout << "Added a 1 to the cipher of '" << info[j].symbol << "'" << std::endl;
                    }
                }
            }
        }
    }



    if(r-l == 1)
        return;
    last[0] = l;
    last[1] = mid+1;

    if((r-l)-2!=0)
        while(mid!=r){ // делю символы на две группы по примерно одинаковым суммам частот
            mid++;
            sum1=0.0;
            sum2=0.0;
            for(size_t j= l; j < mid;j++)
                sum1+=info[j].freq;

            for(size_t j = mid; j < r;j++)
                sum2+=info[j].freq;

            if(fabs(sum1-sum2) < 0.000001) // если суммы частот равны, то сохраняю расположение символов
                break;


            if((sum2 - sum1) < 0.000001){ // если сумм частот из 2 группы больше суммы из первой
                l = last[0];              // то сохраняю предыдущее расположение символов
                mid = last[1];
                break;
            }

            last[0] = l;
            last[1] = mid;
        }
    else
        mid++;

        std::cout << "Go left. ";
        compression(father->get_left(),0,info,l,mid,info_size);
        std::cout << "Go right. ";
        compression(father->get_right(),1,info,mid,r,info_size);

}


void Tree ::print(int &tabs,Tree_Node *&father,Info * &info){
 if (father == nullptr)
     return;            //Если ветки не существует - выходим. Выводить нечего

 tabs++;             //Иначе увеличим счетчик рекурсивно вызванных процедур
                    //Который будет считать нам отступы для красивого вывода
 print(tabs,father->get_right(),info); //Выведем ветку и ее подветки слева
 for (int i = 0; i<tabs; i++)
     std::cout << "       ";       //Потом отступы

 std::string str = "";

 for(size_t j = father->get_INDEX_left(); j < father->get_INDEX_right(); j++){
     if(info[j].symbol == ' ')
         str = str + "space";
     else
         str.insert(str.size(), 1, info[j].symbol);
 }

 std::cout << str << std::endl; //Данные этой ветки
 print(tabs,father->get_left(),info);//И ветки, что справа
 tabs--; //После уменьшим кол-во отступов

}
