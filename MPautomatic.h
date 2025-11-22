#ifndef MP_AUTOMATIC_
#define MP_AUTOMATIC_

#include <string>
#include <vector>
#include <iostream>

enum State{
    q0, q1, q2, q3, q4, f
};

class MPautomatic{
private:
    std::string input;
    std::vector<char> buff;
    State current;
public:
    MPautomatic(const std::string& IN):input(IN), buff({'Y'}),current(q0){
        input.append("e");
    }

    
    
    void process(){
        char ch;

       

        for(size_t i=0;i<input.size();++i){
            ch=input[i];
            
            switch (current)
            {
            case q0:    if(ch=='x' && buff[0]=='Y'){
                            current=q1;
                            buff.insert(buff.begin(), 'X');
                        }else if(ch=='z' && buff[0]=='Y'){
                            current=q1;
                            buff.insert(buff.begin(), 'Z');
                        }else if(ch=='1' && buff[0]=='Y'){
                            current=q1;
                            buff.insert(buff.begin(), 'C');
                        }else if(ch=='e' && buff[0]=='Y'){
                            current=f;
                            buff.erase(buff.begin());
                        }else{
                            std::cout<<"Ошибка: в позиции "<<i+1<<" неожидаемый символ " << ch;
                            return;
                        }
                        break;
            case q1:    
                        if(ch=='x' && buff[0]=='X'){
                            current=q2;
                            buff.erase(buff.begin());
                        }else if(ch=='z' && buff[0]=='Z'){
                            current=q1;
                            buff.insert(buff.begin(), 'Z');
                        }else if(ch=='a' && buff[0]=='Z'){
                            current=q2;
                            buff.insert(buff.begin(), 'A');
                        }else if(ch=='1' && buff[0]=='C'){
                            current=q0;
                            buff.erase(buff.begin());
                        }else if(ch=='e' && buff[0]=='Y'){
                            current=f;
                            buff.erase(buff.begin());
                        }else{
                            std::cout<<"Ошибка: в позиции "<<i+1<<" неожидаемый символ " << ch;
                            return;
                        }
                        break;
            case q2:    if(ch=='x' && buff[0]=='Y'){
                            current=q3;
                            buff.insert(buff.begin(), 'B');
                        }else if(ch=='x' && buff[0]=='B'){
                            current=q3;
                            buff.insert(buff.begin(), 'B');
                        }else if(ch=='a' && buff[0]=='A'){
                            current=q3;
                            buff.erase(buff.begin());
                        }else{
                            std::cout<<"Ошибка: в позиции "<<i+1<<" неожидаемый символ " << ch;
                            return;
                        }
                        break;
            case q3:    if(ch=='x' && buff[0]=='B'){
                            current=q1;
                            buff.insert(buff.begin(), 'X');
                        }else if(ch=='b' && buff[0]=='B'){
                            current=q4;
                            buff.erase(buff.begin());
                        }else if(ch=='z' && buff[0]=='Y'){
                            current=q1;
                            buff.insert(buff.begin(), 'Z');
                        }else if(ch=='a' && buff[0]=='Z'){
                            current=q1;
                            buff.erase(buff.begin());
                        }else if(ch=='1' && buff[0]=='Y'){
                            current=q1;
                            buff.insert(buff.begin(), 'C');
                        }else if(ch=='e' && buff[0]=='Y'){
                            current=f;
                            buff.erase(buff.begin());
                        }else{
                            std::cout<<"Ошибка: в позиции "<<i+1<<" неожидаемый символ " << ch;
                            return;
                        }
                        break;
            case q4:  if(ch=='b' && buff[0]=='B'){
                            current=q3;
                            buff.erase(buff.begin());
                        }else if(ch=='z' && buff[0]=='Y'){
                            current=q1;
                            buff.insert(buff.begin(), 'Z');
                        }else if(ch=='1' && buff[0]=='Y'){
                            current=q1;
                            buff.insert(buff.begin(), 'C');
                        }else{
                            std::cout<<"Ошибка: в позиции "<<i+1<<" неожидаемый символ " << ch;
                            return;
                        }
                        break;
            case f:     if (ch=='e' && buff[0]=='Y'){
                            std::cout<< "True";
                        }else{
                            std::cout<<"Ошибка: в позиции "<<i+1<<" неожидаемый символ " << ch;
                        }
                        return;
            default:
                std::cerr <<"ERROR"<<std::endl;
                return;
            }
        }

        if (current==f){
            std::cout<< "цепочка принадлежит языку";
        }else{
            std::cout<<"ошибка состояния"<<current;
        }
    }

    ~MPautomatic(){
        buff.clear();
    }

};

#endif