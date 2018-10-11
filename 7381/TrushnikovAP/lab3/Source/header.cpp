#include "header.h"
#include <cstring>


void input(int argc, char* argv[],char * &in){
    int len;
    if(argc > 1){ // выполгится, если данные переданы как аргументы строки
        len = argc-1;
        in = new char[len];
		int i;
        for(i = 0; i + 1 < argc; i++){ // копируем данные из argv в in
            if(i==len)
                resize(in,len);			
            in[i] = argv[i+1][0];
        }
		in[i]= '\0';				
    }
    else{ // выполнится, если данные не переданы как аргументы строки
        len = 2;
        in = new char[len];
        int i =0;
        char ch;
        while(1){
            if(i == len)
                resize(in,len);
            if(std::cin.peek() == '\n') // считываем пока не встретим символ конца строки
                break;

            std::cin >> ch;
            in[i] = ch;
            i++;
        }
        in[i] ='\0';
    }

}

void resize(char * &str, int &len){
    char * copy = new char [len];
    strcpy(copy,str); // сохраняем данные перед выдлением памяти для in
    delete []str;
    str= nullptr;
    len*=2;
    str = new char [len]; // перевыделяем память для строки входных данных 
    strcpy(str,copy);
    delete []copy;
    copy = nullptr;
}

bool checkform(std::vector<int> &pos, char * &in){
    mystack Mystack;
    char ch;
    int i = 0;
    bool check = true;

    while(1){
        if(i == strlen(in)){
            if(Mystack.empty()){
                while(Mystack.size_s() > 1)// если в стеке больше одного символа очищаем его пока не осстанется один
                    Mystack.pop();
                if(!Cl_bracket(Mystack.top()) && !isName(Mystack.top())){// если на верине стека лежит не закрывающая скобка
                    pos.push_back(i);								     // и не имя то формула некорректна
                    check = false;
                }
            }
            break;
        }
        ch = in[i];
        i++;

        if(O_bracket(Mystack.top())) // если на вершине стека лежит открывающая скобка
            if(Cl_bracket(ch) || isSign(ch)){// а считанный символ закрывающая скобка
                check = false;
                pos.push_back(i);			// то формула некорректна записываем номер некорректной позиции
            }
        if(isSign(ch))// если считан знак
            if(O_bracket(Mystack.top())){// если на вершине стека лежит откр скобка
                pos.push_back(i);			// то формула некорректна записываем номер некорректной позиции
                check = false;
            }

        if(isSign(Mystack.top()) ){// если на вершине стека лежит знак
            if(Cl_bracket(ch) || isSign(ch)){// и считанный символ незакрывающая скобка и знак
                pos.push_back(i);			// то формула некорректна записываем номер некорректной позиции
                check = false;

            }
            Mystack.pop();
        }



        if(isName(Mystack.top())){// если на вершине стека лежит имя
            if(!Cl_bracket(ch) && !isSign(ch)){// и считанный символ не незакрывающая скобка и не знак
                check = false;					// то формула некорректна записываем номер некорректной позиции
                pos.push_back(i);
            }

            if(isSign(ch)){ // если считан знак и на вершине стека не лежит закрывающая скобка и не лежит имя
                if(Mystack.empty()){
                    if(!Cl_bracket(Mystack.top()) && !isName(Mystack.top())){
                        check = false;		// то формула некорректна записываем номер некорректной позиции
                        pos.push_back(i);
                        Mystack.pop();
                    }
                }
                Mystack.pop();
                Mystack.push(ch);
            }
            else if(O_bracket(ch)){// если считана открывающая скобка
                check = false;
                pos.push_back(i);// то формула некорректна записываем номер некорректной позиции
                Mystack.pop();
            }
            else
                Mystack.pop();
        }
        if(Cl_bracket(Mystack.top())){ // если на вершине стека лежит закрывающая скобка
            if(!Cl_bracket(ch) && !isSign(ch)){// и считанный символ не незакрывающая скобка и не знак
                check = false;					// то формула некорректна записываем номер некорректной позиции
                pos.push_back(i);
                Mystack.pop();
            }
            Mystack.pop();
        }

        if(isName(ch))
            Mystack.push(ch);

        if(O_bracket(ch))
            Mystack.push(ch);

        if(Cl_bracket(ch)){ // если считана закрывающая скобка и на вершине стека не лежит соотв закрыв скобка
           if((ch == ')' && Mystack.top() !='(') ||
            (ch == '}' && Mystack.top() !='{') ||
            (ch == ']' && Mystack.top() !='[')){
                check = false;// то формула некорректна записываем номер некорректной позиции

                pos.push_back(i);
                Mystack.pop();
            }
           Mystack.pop();
           Mystack.push(ch);
        }


    }
    return check;
}


bool isSign(char ch){
    if(ch == '+' || ch == '-')
        return true;
    return false;
}
bool isName(char ch){
    if(ch == 'x' || ch == 'y' || ch == 'z')
        return true;
    return false;
}

bool O_bracket(char ch){
    if(ch == '(' || ch == '{' || ch == '[')
        return true;
    return false;
}
bool Cl_bracket(char ch){
    if(ch == ')' || ch == '}' || ch == ']')
        return true;
    return false;
}

