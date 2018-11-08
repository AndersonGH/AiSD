#include "header.h"
#define FROM_FILE

MyException::MyException(std::string str){
    this->str_what=str;
}

std::string MyException::get_what(){
    return str_what;
}


int struct_cmp_by_freq(const void *a, const void *b){
    Info *ia = (Info *)a;
    Info *ib = (Info *)b;
    return  (ia->freq < ib->freq) - (ib->freq < ia->freq) ;
}




void input(int argc, char* argv[],Info *&info,size_t &info_size,std::string &text){
    std::string str;
    int count = 0;
    char ch;
    bool have;
    //std::string copy;

    #ifdef FROM_FILE // если текст надо считать с файла
        std::ifstream fin;
        if(argc == 2)
            fin.open(argv[1], std::ios::in);
        else{
           std::string file_name;
           std::cout << "input filename" << std::endl;
               std::cin >> file_name;
           fin.open(file_name, std::ios::in);
        }
        if(!fin)
            throw MyException("Error opening file");

        getline(fin,text);
    #else
    std::cout << "Enter the text: " << std::endl; // если текст передается через консоль ввода
    getline(std::cin,text,'\n');
    #endif
    std::cout << "Read text: " << text << std::endl;

    for(size_t j = 0; j < text.size();j++){
        ch = text[j];
        have = false;
        for(size_t i =0 ;i <str.size();i++){ // сохраняем отдельно символы в единисном экземпляре
            if(ch == str[i])
                have = true;
        }
        if(!have)
            str.insert(str.size(), 1, ch);
    }

    double length = (double)text.size();
    info_size = str.size();
    info = new Info[info_size];

    for(size_t j = 0;j < str.size(); j++){
        info[j].cipher_index = 0;
        info[j].symbol = str[j];
        count = 0;
        for(size_t i = 0;i<text.size();i++) // считаем и записываем частоту встречаемости каждого символа
            if(str[j] == text[i])
                count++;
        if(count  > 0)
            info[j].freq = count/length;
    }

    qsort(info, info_size, sizeof(struct Info), struct_cmp_by_freq); // сортируем по невозрастанию частот



}
