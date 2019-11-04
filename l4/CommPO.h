#ifndef L4_COMMPO_H
#define L4_COMMPO_H

#include "PO.h"


class CommPO: virtual public PO{
public:
    int cost;
    void print() override;
    void randomize() override;
    CommPO();
};


#endif //L4_COMMPO_H
