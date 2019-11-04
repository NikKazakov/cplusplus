#ifndef L4_LICPO_H
#define L4_LICPO_H
#include "PO.h"


class LicPO: virtual public PO {
public:
    std::string license;
    void print();
    void randomize();
    LicPO();
};


#endif //BIN_LICPO_H
