#include "mytools.h"
#include <string>

std::string  mytools::get_random_string(int size){
    static const char alphanum[] =
            "0123456789"
            "!@#$%^&*"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    int stringLength = sizeof(alphanum) - 1;
    std::string Str;
    for(unsigned int i = 0; i < size; ++i){
        Str += alphanum[rand() % stringLength];
    }
    return Str;
};