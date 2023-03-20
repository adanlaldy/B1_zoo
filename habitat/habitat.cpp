#include "habitat.h"
#include "iostream"
#include <stdlib.h>
#include "tiger.h"
#include "chicken.h"
#include "eagle.h"
#include "cmath"

int Habitat::getCapacity() {
    return m_capacity;
}

string Habitat::getAnimal() {
    return m_animal;
}

void Habitat::addAnimal(Animal *animal) {
    animals.push_back(animal);
}

int Habitat::estimateFood() {
    int kilos = 0;
    for (int i = 0; i < animals.size(); i++) {
        if(dynamic_cast<Tiger*>(animals[i])!= nullptr){
            if (animals[i]->isMale()) {
                kilos += 12;
            } else if (!animals[i]->isMale() && animals[i]->isPregnant()) {
                kilos += 20;
            } else {
                kilos += 10;
            }
        } else if (dynamic_cast<Eagle*>(animals[i])!= nullptr){
            if (animals[i]->isMale()) {
                kilos += 0.25;
            } else if (!animals[i]->isMale() && animals[i]->isPregnant()) {
                kilos += 0.6;
            } else {
                kilos += 0.3;
            }
        } else {
            if (animals[i]->isMale()) {
                kilos += 0.15;
            } else if (!animals[i]->isMale() && animals[i]->isPregnant()) {
                kilos += 0.36;
            } else {
                kilos += 0.18;
            }
        }

    }
    return kilos;
}


void Habitat::addDay() {
    for (int i = 0; i < animals.size(); i++) {
        animals[i]->addDays();
    }
}

void Habitat::giveFood() {
    for (int i = 0; i < animals.size(); i++) {
        animals[i]->eat();
    }
}

void Habitat::checkCouple() {
    bool gotValideFemale = false;
    int valideFemaleIndex;
    bool gotValideMale = false;
    for (int i = 0; i < animals.size(); i++) {
        if (!animals[i]->isMale() && animals[i]->isMature() && !animals[i]->isHungry() && !animals[i]->isSick() && !animals[i]->isPregnant() && !animals[i]->getWaitNextPregnant()) {
            gotValideFemale = true;
            valideFemaleIndex = i;
        } else if ((dynamic_cast<Tiger*> (animals[i]) != nullptr && animals[i]->getlastTimePregnant() == 90) || (dynamic_cast<Eagle*> (animals[i])!= nullptr && animals[i]->getlastTimePregnant()==45)  || (dynamic_cast<Chicken*> (animals[i])!= nullptr && animals[i]->getlastTimePregnant()==42)) {
            gotValideFemale = true;
            valideFemaleIndex = i;
        }
        if (animals[i]->isMale() && animals[i]->isMature() && !animals[i]->isHungry() && !animals[i]->isSick()) {
            gotValideMale = true;
        }
    }
    if (gotValideFemale && gotValideMale) {
        cout << "startgestation" << animals[valideFemaleIndex]->getName() << endl;
        animals[valideFemaleIndex]->startGestation();
    }
}

void Habitat::checkHungryTiger() {
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->isHungrySince() > 4) {
            cout << "dead hungyyy" << endl;
            animals[i]->killAnimal();
            animals.erase(animals.begin() + i);
        } else if (animals[i]->isHungrySince() > 2) {
            if (!animals[i]->isMale()) {
                animals[i]->setHungry();
                animals[i]->setPregenant(false);
            } else {
                animals[i]->setHungry();
            }
        }
    }
}

void Habitat::isMatureTiger() {
    for (int i = 0; i < animals.size(); i++) {
        if (!animals[i]->isMature()) {
            if (animals[i]->isMale() && animals[i]->getAge() >= 48) { // remettre 72
                animals[i]->setMaturity(true);
            }
            if (!animals[i]->isMale() && animals[i]->getAge() >= 48) {
                animals[i]->setMaturity(true);
            }
        }
        if (animals[i]->isMale() && animals[i]->getAge() == 168) {
            animals[i]->setMaturity(false);
        }
        if (!animals[i]->isMale() && animals[i]->getAge() == 168) {
            animals[i]->setMaturity(false);
        }
    }
}

void Habitat::checkGestation() {
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->isPregnant() && animals[i]->pregnantSince() == 90) {
            animals[i]->birth();
            cout << "?" << endl;
            addTigrous();
        }
    }
}

void Habitat::addTigrous() {
    for (int i = 0; i < 3; i++) {
        int dead = rand() % 3 + 1;
        if (dead != 3) {
            bool male;
            string name;
            if (dead == 1) {
                cout << "Choose name for the male baby tiger :" << endl;
                cin >> name;
                male = true;
            } else {
                cout << "Choose name for the female baby tiger :" << endl;
                cin >> name;
                male = false;
            }
            Tiger *tigrou = new Tiger(male, name, 0);
            tigrou->setMaturity(false);
            addAnimal(tigrou);
        }
    }
}

void Habitat::checkTigerAge() {
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getAge() == 168) {
            animals[i]->killAnimal();
            animals.erase(animals.begin() + i);
        }
    }
}

void Habitat::checkSickTiger() {
    double proba_annuelle = 0.3; // probabilité annuelle de tomber malade
    double proba_quotidienne = 1 - pow(1 - proba_annuelle, 1.0 / 365.0); // probabilité quotidienne de tomber malade
    for (int i = 0; i < animals.size(); i++) {
        double probabilite = static_cast<double>(rand()) / RAND_MAX;
        if (probabilite < proba_quotidienne) {
            cout << "tomber malade" << endl;
            if (animals[i]->isSick()) {
                cout << "dead sikeuh" << endl;
                animals[i]->killAnimal();
                animals.erase(animals.begin() + i);
            }
            animals[i]->setSick(true);
        }
        if (animals[i]->getSickSince() == 15) {
            animals[i]->setSick(false);
        }
    }
}




