#ifndef TIGER_CAGE_H
#define TIGER_CAGE_H

#include "string"
#include "habitat.h"

using namespace std;

class Tiger_cage : public Habitat{
public:
    Tiger_cage(string name, int price, int capacity)
    :Habitat(name, price, capacity){};
    virtual int estimateBuyPrice();
    virtual int estimateSellPrice();
    virtual int getCapacity();
};

#endif