#ifndef L4_PO_H
#define L4_PO_H

#include <string>

class PO {
    std::string name;
    std::string type;
    int number_of_disks;
    int volume;

public:
    virtual void randomize();
    double Run();
    virtual void print();
    PO();
    ~PO();
};

#endif //L4_PO_H
