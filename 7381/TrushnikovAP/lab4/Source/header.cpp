#include "header.h"

MyException::MyException(std::string str){
    this->str_what=str;
}

std::string MyException::get_what(){
    return str_what;
}

void infix_to_postfix(char*&in, char*&postfix){
    Array_stack stack;
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
                    ch = stack.pop();       //если важность токена на вершине стека больше чем важность считанного токе
                    postfix[j] = ch;        // то достаем его из стека
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

inline void check_input(int oper_count , int sign_count){
    if((oper_count!=sign_count+1 || oper_count == 0 || sign_count == 0)){
        if(oper_count == 0 && sign_count == 0)
            throw MyException("Empty");
        else if(oper_count == sign_count)
            throw MyException("Too few operands");
        else if(oper_count > 2*sign_count)
            throw MyException("Too few signs");
        else if(oper_count < 2*sign_count)
            throw MyException("Too few operands");
    }
}


void input(int argc, char* argv[],char * &in, int &first_len){
    Array_stack brackets;
    int oper_count = 0;
    int sign_count = 0;

    if(argc > 1){ // выполгится, если данные переданы как аргументы строки
        first_len = argc-1;
        int i;
        char ch;
        in = new char [first_len];


        for(i = 0; i+1 < argc; i++){ // копируем данные из argv в in
            ch = argv[i+1][0];

            if(ch == '('){
                brackets.push('(');
            }
            else if(ch == ')'){
                if(brackets.empty()){
                    in[i] = '\0';
                    throw MyException("Incorrect brace placement");
                }
                if(brackets.top() == '(')
                     brackets.pop();
            }

            if(isalnum(ch))
                oper_count++;

            if(ch == '*' || ch == '+' || ch == '-')
                sign_count++;


            if(i==first_len-1){
                in[first_len-1] = '\0';
                resize(in,first_len);
            }
            in[i] = ch;
        }
        in[i] = '\0';
        if(!brackets.empty())
            throw MyException("Incorrect brace placement");
        if(oper_count==1 && sign_count==0)
            return;
        check_input(oper_count,sign_count);
    }

    else{

        int i =0;
        first_len = INPUT_SIZE;
        in = new char [first_len];
        char ch;

        while(1){


            if(i==first_len-1){
                in[first_len-1] = '\0';
                resize(in,first_len);
            }

            std::cin >> ch;
            if(!check(ch))
                throw MyException("Incorrect symbol");

            if(ch == '('){
                brackets.push('(');
            }
            else if(ch == ')'){
                if(brackets.empty()){
                    in[i] = '\0';
                    throw MyException("Incorrect brace placement");
                }
                if(brackets.top() == '(')
                     brackets.pop();
            }
            if(isalnum(ch))
                oper_count++;

            if(ch == '*' || ch == '+' || ch == '-')
                sign_count++;



            in[i] = ch;
            i++;
            if(std::cin.peek() == '\n'){
                if(!brackets.empty()){
                    in[i] = '\0';
                    throw MyException("Incorrect brace placement");
                }
                break;
            }

        }
        in[i] = '\0';
        if(oper_count==1 && sign_count==0)
            return;
        check_input(oper_count,sign_count);
    }



}

void resize(char * &str, int &len){
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

