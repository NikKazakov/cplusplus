#include "LicPO.h"
#include "mytools.h"
#include <iostream>
#include <ctime>

LicPO::LicPO():PO() {
    license = mytools::get_random_string(16);
}

void LicPO::randomize(){
    srand((unsigned) time(nullptr));
    PO::randomize();
    license = mytools::get_random_string(16);
}

void LicPO::print() {
    PO::print();
    std::cout << "License: " << license << std::endl;
}
