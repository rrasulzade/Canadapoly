//
//  dice.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-23.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

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
