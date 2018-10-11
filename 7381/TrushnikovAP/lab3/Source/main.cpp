#include "header.h"
#include <cstring>

int main(int argc, char* argv[]){
    std::vector<int> pos;
    char *in;


    input(argc,argv,in);// вызов функции считывания входящей строки

    if(checkform(pos,in))
        std::cout<< "Correct" << std::endl;//вывод сообщения в консоль, если формула корректна
    else{
        std::cout<< "Incorrect: " ; //вывод сообщения в консоль, если формула некорректна
        std::vector<int> :: iterator it;
        sort(pos.begin(), pos.end()); // сортирум вектор
        it = unique(pos.begin(), pos.end()); // удаляем повторяющиеся элементы
        pos.resize(it - pos.begin());

        for(int  i = 0; i < pos.size(); i++)//вывод сообщения в консоль с номерами ошибочных позиций
            std::cout << pos[i] << " ";

    }
	std::cout << std::endl;
	delete []in;
    return 0;
}
