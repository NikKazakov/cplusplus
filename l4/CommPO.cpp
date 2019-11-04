#include "CommPO.h"
#include <iostream>
#include <ctime>

CommPO::CommPO():PO() {
    cost = 13;
}

void CommPO::randomize(){
    srand((unsigned) time(nullptr));
    PO::randomize();
    cost = rand() % 69 + 1;
}

void CommPO::print() {
    PO::print();
    std::cout << cost << " $$" << std::endl;
}