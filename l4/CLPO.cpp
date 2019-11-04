#include "CLPO.h"
#include "mytools.h"
#include <iostream>
#include <ctime>

void CLPO::print() {
    PO::print();
    std::cout << "License: " << license << std::endl
              << cost << " $$" << std::endl;
}

void CLPO::randomize() {
    srand((unsigned) time(nullptr));
    PO::randomize();
    license = mytools::get_random_string(16);
    cost = rand() % 69 + 1;
}
