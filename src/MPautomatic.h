#ifndef MP_AUTOMATIC_
#define MP_AUTOMATIC_

#include <string>
#include <vector>
#include <iostream>
#include <exception>

class MPError : public std::exception{
private:
    std::string errorMessage;
public:
    explicit MPError(const std::string& message): errorMessage(message){}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

};

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

    State getCurrentState() const {
        return current;
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
                        }else if(ch=='e' && buff[0]=='Y'){
                            current=f;
                            buff.erase(buff.begin());
                        }else{
                            input.pop_back();
                            throw MPError(input+" Ошибка: в позиции "+std::to_string(i+1)+" неожидаемый символ " +std::string(1, ch));
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
                        }else if(ch=='e' && buff[0]=='Y'){
                            current=f;
                            buff.erase(buff.begin());
                        }else{
                            input.pop_back();
                            throw MPError(input+" Ошибка: в позиции "+std::to_string(i+1)+" неожидаемый символ " +std::string(1, ch));
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
                            input.pop_back();
                            throw MPError(input+" Ошибка: в позиции "+std::to_string(i+1)+" неожидаемый символ " +std::string(1, ch));
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
                        }else{
                            input.pop_back();
                            throw MPError(input+" Ошибка: в позиции "+std::to_string(i+1)+" неожидаемый символ " +std::string(1, ch));
                        }
                        break;
            case q4:    if(ch=='b' && buff[0]=='B'){
                            current=q3;
                            buff.erase(buff.begin());
                        }else if(ch=='z' && buff[0]=='Y'){
                            current=q1;
                            buff.insert(buff.begin(), 'Z');
                        }else if(ch=='e' && buff[0]=='Y'){
                            current=f;
                            buff.erase(buff.begin());
                        }else{
                            input.pop_back();
                            throw MPError(input+" Ошибка: в позиции "+std::to_string(i+1)+" неожидаемый символ " +std::string(1, ch));
                        }
                        break;
            case f:     if (ch!='e' && buff[0]!='Y'){
                            input.pop_back();
                            throw MPError(input + " Ошибка: в позиции "+std::to_string(i+1)+" неожидаемый символ " +std::string(1, ch));
                        }
                        return;
            default:
                throw MPError("Неизвестное состояние");
            }
        }

        if (current==f){
            input.pop_back();
            std::cout<< input<<" цепочка успешно обработана"<<std::endl;
        }else{
            throw MPError("Ошибка конечного состояния: "+ std::string(2,current));
        }
    }

    ~MPautomatic(){
        buff.clear();
    }

};

#endif
