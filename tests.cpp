#include <string>
#include <cassert>

#include "MPautomatic.h"

void tests_zero(){
    MPautomatic test1("1111");
    test1.process();
    assert(test1.getCurrentState() == State::f);

    MPautomatic test2("xxxb11");
    test2.process();
    assert(test2.getCurrentState() == State::f);

    MPautomatic test3("11zaaa");
    test3.process();
    assert(test3.getCurrentState() == State::f);

}

void tests_mp(){
    MPautomatic test4("xxxbzaaa");
    test4.process();
    assert(test4.getCurrentState() == State::f);

    MPautomatic test5("xxxbzaaa");
    test5.process();
    assert(test5.getCurrentState() == State::f);

    MPautomatic test6("xxxbzzaaaaaa");
    test6.process();
    assert(test6.getCurrentState() == State::f);

    MPautomatic test7("xxxxxxbbzaaa");
    test7.process();
    assert(test7.getCurrentState() == State::f);

    MPautomatic test8("xxxxxxbbzzzaaaaaaaaa");
    test8.process();
    assert(test8.getCurrentState() == State::f);
}

void tests_err(){
    try{
        MPautomatic test9("xxyzaaa");
        test9.process();
        assert(false);
    }catch(const MPError& e){
        std::string errorMessage = e.what();
        std::cerr<<errorMessage<<std::endl;
        assert(std::string(e.what()).find("Ошибка: в позиции 3 неожидаемый символ y") != std::string::npos);
    }

    try{
        MPautomatic test10("xxbzaaa");
        test10.process();
        assert(false);
    }catch(const MPError& e){
        std::string errorMessage = e.what();
        std::cerr<<errorMessage<<std::endl;
        assert(std::string(e.what()).find("Ошибка: в позиции 3 неожидаемый символ b") != std::string::npos);
    }
}

int main(){
    std::cout << "Начало тестирования MPautomatic..." << std::endl;
    
    try{
        tests_zero();
        tests_mp();
        tests_err();

        std::cout<<"Тесты успешно пройдены"<<std::endl;
    } catch(...){
        std::cerr<<"Нарушен тест"<<std::endl;
        return 1;
    }

    
    return 0;
}