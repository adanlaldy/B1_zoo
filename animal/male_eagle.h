#include "string"
#include "animal.h"

using namespace std;

class Male_eagle : public Animal{

public:
    Male_eagle(string name, int age_month)
    :Animal(name, age_month){};
    virtual int estimateBuyPrice();
    virtual int getAge();
};