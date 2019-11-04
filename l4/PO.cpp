#include <iostream>
#include <ctime>
#include "PO.h"

void PO::randomize() {
    std::string names[15] = {"SamplePO", "VeryEasy", "WhoIsIt", "HelloWorld", "IsThisMatrix", "LittleTrain", "Gravel", "Bee", "Nonsence", "Stap", "OhHeyThere", "OhHiMark", "Help", "ImGovard", "ISubmit"};
    std::string types[7] = {"TextEditor", "Calculator", "TableEditor", "Player", "WebApplication", "idk", "SomethingSomething"};
    srand((unsigned) time(nullptr));
    name = names[rand() % (sizeof(names)/ sizeof(*names))];
    type = types[rand() % (sizeof(types)/ sizeof(*types))];
    number_of_disks = rand() % 13 + 1;
    volume = rand() % 32000000;
}

double PO::Run() {return 13.37;}

void PO::print() {
    std::cout << "Name: " << name << std::endl
              << "Type: " << type << std::endl
              << "Disks used: " << number_of_disks << std::endl
              << "Volume: " << volume << " bytes" << std::endl;
}

PO::PO(){
    name = "SamplePO";
    type = "TextEditor";
    number_of_disks = 4;
    volume = 16;
}

PO::~PO() = default;
