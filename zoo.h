#include <string>
#include "animal.h"

using namespace std;

class Zoo{
    string m_name;
public:
    Zoo(string name):m_name(name){};
    void buyAnimal(Animal* animal);
    void sellAnimal(Animal* animal);
};