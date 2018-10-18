#include "header.h"
#include <cstring>


void input(int argc, char* argv[],char * &in){
    int len;
    if(argc > 1){ // выполгится, если данные переданы как аргументы строки
        len = argc-1;
        in = new char[len];
		int i;
        for(i = 0; i + 1 < argc; i++){ // копируем данные из argv в in
            if(i==len-1){
                in[len-1] = '\0';
                resize(in,len);
            }

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
            if(i==len-1){
                in[len-1] = '\0';
                resize(in,len);
            }
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
	int old_poz = 0;
    char ch;
    int i = 0;
    bool check = true;

    while(1){
        if(i == strlen(in)){
            if(!Mystack.empty()){
             while(Mystack.size_s() > 1)// очищаем стек пока в нем не останется один элемент
                std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;

             if(!Cl_bracket(Mystack.top()) && !isName(Mystack.top()) && !isdigit(in[i-1])){// если на верине стека лежит не закрывающая скобка
                 std::cout << "In the end must be bracket" << std::endl;
                 pos.push_back(i-old_poz);								     // и не имя то формула некорректна
                 check = false;
                }
            }
            std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;
            Mystack.print();
            break;
        }
		if(isdigit(ch))
            while(isdigit(in[i])){
                old_poz++;
				i++;
			}

		if(i == strlen(in))
            continue;
        ch = in[i];
        std::cout << "Counted: " <<  ch << " i: " << i << std::endl;
        Mystack.print();
        i++;

        if(!isSign(ch) && !isName(ch) && !O_bracket(ch) && !Cl_bracket(ch)){
            std::cout << "~~~~Incorrect symbol: " << ch << " ~~~~" << std::endl;
            pos.push_back(i-old_poz); // формула неккоректна записаваем положение символа
            check = false;
        }

        if(isName(ch)){// если считано имя
            if(Cl_bracket(Mystack.top())){// если на вершине стека лежит закрывающая скобка
                std::cout << "~~~~Incorrect symbol: " << ch << " ~~~~" << std::endl;
                pos.push_back(i-old_poz); // формула неккоректна записаваем положение символа
                check = false;
                if(!Mystack.empty())
                    std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;
            }
            if(isSign(Mystack.top()))// если на вершине стека лежит знак попаем элемент из вершины стека
                if(!Mystack.empty())
                    std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;

            Mystack.push(ch); //кладем считанный элемент в стек
            std::cout << "Push to Stack: " << ch << std::endl;

        }
        if(isSign(ch)){// если считан знак
            if(isSign(Mystack.top())){// и на вершине стека лежит открывающая скобка
                std::cout << "~~~~Incorrect symbol: " << ch << " ~~~~" << std::endl;
                pos.push_back(i-old_poz);// формула неккоректна записаваем положение символа
                check = false;

            }
			else if(O_bracket(Mystack.top())){
				std::cout << "~~~~Incorrect symbol: " << ch << " ~~~~" << std::endl;
                pos.push_back(i-old_poz);// формула неккоректна записаваем положение символа
                check = false;
				Mystack.push(ch);//кладем считанный элемент в стек
                std::cout << "Push to Stack: " << ch << std::endl;
			}
            else{
                if(!Mystack.empty())// попаем элемент из вершины стека
                    std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;

                Mystack.push(ch);//кладем считанный элемент в стек
                std::cout << "Push to Stack: " << ch << std::endl;
            }

        }
        if(O_bracket(ch)){//если считана открывающая скобка
            if(Cl_bracket(Mystack.top()) || isName(Mystack.top())){//если на вершине стека лежит закрывающая скобка
                std::cout << "~~~~Incorrect symbol: " << ch << " ~~~~" << std::endl;
                pos.push_back(i-old_poz);// формула неккоректна записаваем положение символа
                check = false;
                if(!Mystack.empty()) // попоаем элемент с вершины стека
                    std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;
            }
            if(!O_bracket(Mystack.top()))// если на вершине стека
                if(!Mystack.empty())
                    std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;

            Mystack.push(ch);// кладем элемент в стек
            std::cout << "Push to Stack: " << ch << std::endl;
        }

        if(Cl_bracket(ch)){//если считана закрывающая скобка
            if(O_bracket(Mystack.top())){//если на вершине стека лежит открывающая скобка
                check = false;

                pos.push_back(i-old_poz);// формула неккоректна записаваем положение символа
                if((ch == ')' && Mystack.top() =='(') ||
                   (ch == '}' && Mystack.top() =='{') ||
                   (ch == ']' && Mystack.top() =='['))
                    std::cout << "~~~~Incorrect symbol: " << ch << " ~~~~" << std::endl;
            }
            else{
                if(!Mystack.empty())// попаем элемень из стека
                    std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;
            }
            if((ch == ')' && Mystack.top() !='(') || // если открывающей скобке не соответсвует нужная скобка на вершине стека
               (ch == '}' && Mystack.top() !='{') ||
               (ch == ']' && Mystack.top() !='[')){
                std::cout << "~~~~Incorrect symbol: " << ch << " ~~~~" << std::endl;
                check = false;
                pos.push_back(i-old_poz);// формула неккоректна записаваем положение символа
            }
            if(!Mystack.empty())// попаем элемент из стека
                std::cout << "Pop from Stack: " << Mystack.pop() << std::endl;
            Mystack.push(ch);// кладем считанный элемент в стек
            std::cout << "Push to Stack: " << ch << std::endl;

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

