#include <iostream>
#include <vector>
#include <string>
#include "MPautomatic.h"



int main(){

    std::string input;
    std::cin>>input;
    
    MPautomatic mp(input);
    mp.process();

    return 0;
}
