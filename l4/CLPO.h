#ifndef L4_CLPO_H
#define L4_CLPO_H

#include "CommPO.h"
#include "LicPO.h"


class CLPO: CommPO, LicPO {
public:
    void print();
    void randomize();
};


#endif //L4_CLPO_H
