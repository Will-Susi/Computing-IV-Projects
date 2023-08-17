#include <iostream>
#include <string>

#include "FibLFSR.hpp"

FibLFSR::FibLFSR(string seed){
    _register = seed;
}

string FibLFSR::getRegister() const {
    return _register;
}

int FibLFSR::step(){
    int resultBit = _register[5] ^ ( _register[3] ^ ( _register[2] ^ _register[0]));

    _register = _register.substr(1, 16);
    _register.append(to_string(resultBit));

    return resultBit;
}

int FibLFSR::generate(int k){
    int result = 0;
    for (int i = 0; i < k; i++){
        result = (result * 2) + step();
    }

    return result;
}

ostream& operator<<(ostream& outStream, const FibLFSR& lfsr){
    outStream << lfsr.getRegister();
    return outStream;
}