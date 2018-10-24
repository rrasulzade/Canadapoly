//
//  dice.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-23.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

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
};

#endif /* dice_hpp */
