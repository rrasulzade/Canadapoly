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
#include <vector>

// #include "player.hpp"
// #include "building.hpp"

class Player;
class Slot;

class TextDisplay{
    char **theDisplay;
    std::vector<std::pair<int,int>> playerCurPosition;

public:
    TextDisplay();
    ~TextDisplay();
    void print();
    void updatePlayer(const Player* player, const std::pair<int, int> location);
    void notify(Player* );
    void notify(Slot*  b);
    void printAssets(Player*);

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif /* textDisplay_hpp */
