//
//  textDisplay.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef textDisplay_hpp
#define textDisplay_hpp


#include <iostream>
#include <sstream>
// #include "player.hpp"
// #include "building.hpp"


class TextDisplay{
    char **theDisplay;
    char **boardplayer;

public:
    TextDisplay();
    ~TextDisplay();
    void print();
    void addPlayer(Player * );
    void notify(Player* );
    void notify(Building*  b);
    void printAssets(Player*);

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif /* textDisplay_hpp */
