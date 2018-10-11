#include "lisp.h"
#include "header.h"
 Lisp_Node::~Lisp_Node(){ //деструктор очистки иерархического списка
    if(this->bottom)
        delete bottom;
     if(this->right)
        delete right;
}
 Lisp::Lisp(){
    this->root = NULL;
}
 Lisp::~Lisp(){
}
 bool Lisp::create_lisp(int len,char ** &in,class Lisp &lisp){
    int i = len-1;
    int level = 0;
    std::stack <class Lisp_Node *> fathers;
    class Lisp_Node * father;
    while(1){
        char ch=' ';
        if(len == 1 && i == -1)
            break;
        if(i <= 0 && len > 1)
            break;
        while(i>0){
            ch = in[i][0];
                if(in[i][1] != '\0')
                    ch = in[i][1];
            i--;
            break;
        }
        if(len == 1){
            ch = in[i][0];
                if(in[i][1] != '\0')
                    ch = in[i][1];
            i--;
        }

        if(len == 1){
            class Lisp_Node * node = new Lisp_Node;
            node->atom(node);
            lisp.root = node;
            level++;
            father = node;
            if(isdigit(ch)){ // если считано число вставляем его
                int num = atoi(in[i+1]);
                std::cout << "Insert atom num: " << num << std::endl;
                lisp.insert_atom_num(father,num);
            }
            else if(isSign(ch)){ // если считан знак встваляем
                std::cout << "Insert atom sign " << ch << std::endl;
                lisp.insert_atom_sign(father,ch);
            }
            continue;
        }

        else if(i==len-2 ){
            class Lisp_Node * node = new Lisp_Node;
            node->atom(node);
            lisp.root = node;
            level++;
            fathers.push(node);
            if(len > 2)// выполнится если в ариф выражении компонетов больше одного
                continue;
            else
                father = fathers.top();

         }
         else
            father = fathers.top();


        if(in[i][0] =='(' && ch == ')'){ // проверяем явлестя ли данный компонет Nill
            i--;
            std::cout << "Insert Nill" << std::endl;
            lisp.insert_nill(father);
        }

        else if(ch==')' || ch == '('){ // если это откр или заркр скобка создаем либо pair и атом либо просто атом
            lisp.create_temp(ch,fathers,level,father);
        }
        else if(isdigit(ch)){ // если считано число вставляем его
            int num = atoi(in[i+1]);
            std::cout << "Insert atom num: " << num << std::endl;
            lisp.insert_atom_num(father,num);
        }
        else if(isSign(ch)){ // если считан знак встваляем
            std::cout << "Insert atom sign " << ch << std::endl;
            lisp.insert_atom_sign(father,ch);
        }
    }
     return true;
}
 void Lisp::insert_nill(class Lisp_Node *father){ // метод вставки Nill
     if(father->isEmptyAtom(father)) // если на вершине стека лежит пустой атом вставляем туда Nill
        father->Nill(father);
    else{
        while(father->right!=NULL) // идем вправо пока не встретим элемент правый указатель которого пустой
            father=father->right;
         class Lisp_Node *node = new Lisp_Node;
        node->Nill(node);
        father->right=node;
    }
}
 void Lisp::insert_atom_sign(class Lisp_Node *father,char sign){ // метод вставки атома знака
     if(father->isEmptyAtom(father)) // если на вершине стека лежит пустой атом вставляем туда атом знака
        father->atom_sign(father,sign);
    else{
        while(father->right!=NULL) // идем вправо пока не встретим элемент правый указатель которого пустой
            father=father->right;
         class Lisp_Node *node = new Lisp_Node;
        node->atom_sign(node,sign);
        father->right=node;
    }
 }
void Lisp::insert_atom_num(class Lisp_Node *father,int num){// метод вставки атома числа
     if(father->isEmptyAtom(father)) // если на вершине стека лежит пустой атом вставляем туда атом числа
        father->atom_num(father,num);
     else{
        while(father->right!=NULL) // идем вправо пока не встретим элемент правый указатель которого пустой
            father=father->right;
         class Lisp_Node *node = new Lisp_Node;
        node->atom_num(node,num);
        father->right=node;
     }
}
 void Lisp::create_temp(char ch,std::stack <class Lisp_Node *> &fathers,int &level,class Lisp_Node *father){// метод создания pair и пустого атом
    if(ch == ')'){								//либо пустого атома
        level++;
        class Lisp_Node *node = new Lisp_Node; // создаем пустой элемент
        fathers.push(node);
         if(level - 1 !=0){ // если степень вложенности больше одного делаем созданный элемент pair
            std::cout << "Insert pair" << std::endl;
            node->pair(node);
        }
        if(father->is_Nill(father))
            while (father->is_Nill(father)) {
                if(father->right == NULL)
                    break;
                father = father->right;
            }
         paste_node(father,node);
         if(level - 1 > 0){ // если степень вложенности больше одного создаем новый пустой атом
            std::cout << "Insert empty atom" << std::endl;
            class Lisp_Node *node_b = new Lisp_Node;
            node_b->atom(node_b);
            fathers.push(node_b);
            node->bottom=node_b;
        }
     }
    else{
        if(level - 1 !=0){// если считана закрывабщая скобка удаляем из стека лишние адресы
            int j = level -1;
            while(j>0){
                fathers.pop();
                j--;
            }
        }
        level--;
    }
}
 void Lisp_Node::pair(Lisp_Node *s){// метод делует элемент списка pair
    s->s.Nill = false;
    s->s.tag = false;
    s->s.empty = false;
    s->right=NULL;
    s->bottom=NULL;
}
 void Lisp_Node::atom_num(Lisp_Node *s,int num){ // метод делует элемент списка атомом числа
    s->s.Nill = false;
    s->s.tag = true;
    s->s.empty=false;
    s->s.sign_check=false;
    s->s.num=num;
    s->right=NULL;
    s->bottom=NULL;
}
 void Lisp_Node::Nill(Lisp_Node *s){// метод делует элемент списка Nill
    s->s.Nill = true;
    s->s.tag = false;
    s->right = NULL;
    s->bottom = NULL;
}
 void Lisp_Node::atom(Lisp_Node *s){// метод делует элемент списка пустым атомом
    s->s.Nill = false;
    s->s.empty=true;
    s->s.tag = true;
    s->right=NULL;
    s->bottom=NULL;
}
 void Lisp_Node::atom_sign(Lisp_Node *s,char ch){// метод делует элемент списка атомом знака
    s->s.Nill = false;
    s->s.tag = true;
    s->s.empty=false;
    s->s.sign_check=true;
    s->s.sign=ch;
    s->right=NULL;
    s->bottom=NULL;
}
 bool Lisp_Node::isAtom_num(Lisp_Node *s){// метод делает элемент списка атомом числа
    if(is_Nill(s) || is_pair(s))
        return false;
    if(!s->s.sign_check)
        return true;
    return false;
 }
bool Lisp_Node::isEmptyAtom(Lisp_Node *s){// вернет true если s пустой атом
    if(is_Nill(s) || is_pair(s))
        return false;
     return s->s.empty;
}
 bool Lisp_Node::isAtom_sign(Lisp_Node *s){// вернет true если s атом знака
    if(is_Nill(s) || is_pair(s))
        return false;
    if(s->s.sign_check)
        return true;
    return false;
}
 bool Lisp_Node::is_Nill(Lisp_Node *s){// вернет true если s Nill
    return s->s.Nill;
}
bool Lisp_Node::is_pair(Lisp_Node *s){// вернет true если s pair
    if(is_Nill(s))
        return false;
    return !s->s.tag;
}
 bool Lisp_Node::isAtom (Lisp_Node *s){// вернет true если s атом
    if(is_Nill(s) || is_pair(s))
        return false;
    return true;
}
