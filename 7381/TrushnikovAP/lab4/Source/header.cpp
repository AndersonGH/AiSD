#include "header.h"

MyException::MyException(std::string str){
    this->str_what=str;
}

std::string MyException::get_what(){
    return str_what;
}

void infix_to_postfix(char*&in, char*&postfix){
    Array_stack stack;
    postfix = new char[strlen(in)+1];
    memset(postfix,'\0',strlen(in)+1);

    char ch,token;
    int i;
    size_t j=0;    //i-index of infix,j-index of postfix

    for(i=0;in[i]!='\0';i++){
        token = in[i];

        if(isalnum(token)){
            postfix[j] = token;
            j++;

        }
        else if(token == '(')
            stack.push(token);
        else if(token == ')'){
            try{
                while(1){
                    ch=stack.pop();
                    if(ch == '(')
                        break;
                    postfix[j] = ch;
                    j++;
                    if(stack.empty())
                        break;
                }
            }catch(Underflow e){

            }
        }
        else {
            try{
                while((precedence(token) <= precedence(stack.top())) && !stack.empty() ){
                    ch = stack.pop();
                    postfix[j] = ch;
                    j++;
                }
            }catch(Underflow e){

            }

            stack.push(token);
        }


    }

    while(!stack.empty()){
        ch=stack.pop();
        postfix[j] = ch;
        j++;
    }
    postfix[j]='\0';
}


void input(int argc, char* argv[],char ** &in, int &first_len, int &second_len){
    Array_stack brackets;

    if(argc > 1){ // выполгится, если данные переданы как аргументы строки
        first_len = argc-1;
        second_len = FIRST_INPUT_SIZE;
        int i,j=0,k = 0;
        char ch;
        in = new char *[first_len];

        for(int j =0; j < first_len; j++)
            in[j] = nullptr;

        for(i = 0, k = 0; k + 1 < argc; i++,k++){ // копируем данные из argv в in
            ch = argv[k+1][0];

            if(ch == '('){
                brackets.push('(');
            }
            else if(ch == ')'){
                if(brackets.empty()){
                    throw MyException("Incorrect brace placement");
                }
                if(brackets.top() == '(')
                     brackets.pop();
            }


            if(ch == '|'){
                j++;
                continue;
            }
            if(in[j] == nullptr){
                i=0;
                second_len = FIRST_INPUT_SIZE;
                in[j] = new char [second_len];
                memset(in[j],'\0',second_len);
            }
            if(i==second_len-1){
                in[j][second_len-1] = '\0';
                resize1(in[j],second_len);
            }
            in[j][i] = ch;
        }
        if(!brackets.empty())
            throw MyException("Incorrect brace placement");
    }

    else{
        int i =0, j = 0;
        first_len = FIRST_INPUT_SIZE;
        in = new char* [first_len];
        char ch;

        for(int j =0; j < first_len; j++)
            in[j] = nullptr;


        while(1){
            if(in[j] == nullptr){
                second_len = SECOND_INPUT_SIZE;
                in[j] = new char [second_len];
                memset(in[j],'\0',second_len);
            }

            if(i==second_len-1){
                in[j][second_len-1] = '\0';
                resize1(in[j],second_len);
            }

            std::cin >> std::noskipws >> ch;
            if(!check(ch))
                throw MyException("Incorrect symbol");

            if(ch == '('){
                brackets.push('(');
            }
            else if(ch == ')'){
                if(brackets.empty()){
                    throw MyException("Incorrect brace placement");
                }
                if(brackets.top() == '(')
                     brackets.pop();
            }



            if(ch == ' '){
                in[j][i] = '\0';
                j++;
                if(j == first_len){
                    in[j-1][second_len-1] = '\0';
                    resize2(first_len,in);
                }
                i = 0;
                continue;
            }
            if(ch == '\n'){
                if(!brackets.empty())
                    throw MyException("Incorrect brace placement");
                break;
            }
            in[j][i] = ch;
            i++;
        }
        in[j][i] = '\0';
    }


}

void resize1(char * &str, int &len){
    char * copy = new char [len];
    strcpy(copy,str); // сохраняем данные перед выдлением памяти для in
    delete []str;
    str= nullptr;
    len*=2;
    str = new char [len];
    memset(str,'\0',len);// перевыделяем память для строки входных данных
    strcpy(str,copy);
    delete []copy;
}


void resize2(int &len,char ** &in){// функция увеличения размера двумерного массива
   int l_copy = len;
    char **copy = new char* [l_copy];
    for(int i = 0;i<len;i++){
       copy[i] = new char [strlen(in[i])+1];
       strcpy(copy[i],in[i]);
   }
    for(int i = 0;i<len;i++){
        delete [] in[i];
   }
   delete  [] in;
   len=len*2;
   in = new char* [len];
   for(int i = 0;i<l_copy;i++){
       in[i] = new char [strlen(copy[i])+1];
       strcpy(in[i],copy[i]);
   }
   for(int i = len/2; i < len; i++)
       in[i] = nullptr;
   for(int i =0;i<l_copy;i++){
       delete [] copy[i];
   }
   delete  [] copy;
}
int precedence(char ch){
    if(ch=='(')
        return 0;
    if(ch=='+'||ch=='-')
        return 1;
    if(ch =='*')
        return 2;

    return 3;
}

bool isSign(char ch){
    if(ch=='+' || ch == '-' ||  ch == '*')
        return true;
    else
        return false;
}

bool check (char ch){
    if(ch == '*' || ch == '-' || ch == '+' || (ch >= 97 && ch <= 122) || ch == '(' || ch == ')'
            || ch == ' ' || ch == '\n' || isdigit(ch))
        return true;
    return false;

}

