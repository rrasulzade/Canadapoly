#ifndef dice_hpp
#define dice_hpp

#include <iostream>
#include <string>


class Dice {
    int die1;
    int die2;

public:
    Dice(int die1=0, int die2=0);
    bool isPair();
    int getSum();
    void roll();
    std::string getResults();

    void setDice(int d1, int d2);
};

#endif /* dice_hpp */
