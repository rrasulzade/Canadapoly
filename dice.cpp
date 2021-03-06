#include "dice.hpp"
#include <sstream>
#include <ctime>

using namespace std;

Dice::Dice(int die1, int die2): die1(die1), die2(die2){}

bool Dice::isPair(){
    return die1 == die2;
}

int Dice::getSum(){
    return die1 + die2;
}

void Dice::roll(){
    srand(time(nullptr));
    die1 = 1 + rand() % 6;
    die2 = 1 + rand() % 6;
}

string Dice::getResults(){
    stringstream ss;
    ss << "You rolled " << die1 << " and " << die2 << endl;
    ss << "Sum is " << getSum() << endl;

    return ss.str();
}

void Dice::setDice(int d1, int d2){
    die1 = d1;
    die2 = d2;
}
