//
//  gameBoard.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef gameBoard_hpp
#define gameBoard_hpp

#include <iostream>


class Player;
class Slot;

class GameBoard{
    int totalPlayers;
    Player **players;
    Slot *slots[40];

public:
    GameBoard();
    ~GameBoard();

    void init();

};

#endif /* gameBoard_hpp */
