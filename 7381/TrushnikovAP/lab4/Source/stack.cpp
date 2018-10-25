#include "stack.h"

Underflow::Underflow(std::string str){
    this->str_what=str;
};


Array_stack::~Array_stack(){
    delete [] data;
}

Array_stack::Array_stack(){
    size_t len = INIT_SIZE;
    data = new char [len];
    memset( data,'0', len );
    size = len;
    ontop = 0;

}

void Array_stack::resize(){
    data[size-1]='\0';
    char * copy = new char[size];
    strncpy(copy,data,size);
    delete [] data;
    size*=2;
    data = new char [size];
    strncpy(data,copy,size/2);
    delete [] copy;
}

void Array_stack::push(char ch){
    if(this->ontop + 2 == this->size)
        resize();
    ontop++;
    data[ontop] = ch;


}

bool Array_stack::empty(){
    return ontop == 0;
}

char Array_stack::pop(){
    if(this->ontop == 0)
        throw Underflow("\nStack Underflow!");
    char ch = data[ontop];
    ontop--;

    return ch;
}
char Array_stack::top(){
    if(this->ontop == 0)
        throw Underflow("Stack Underflow!");

    return data[ontop];
}
