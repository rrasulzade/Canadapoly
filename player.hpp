//
//  player.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <string>
#include <vector>

// #include "ownable.hpp"

class Ownable;

class Player {
    const std::string name;
    const char piece;
    int id;
    int money;
    int position;
    std::vector<Ownable* > buildings;

    static int playerID;

public:
    Player(const std::string name, const char piece);
    ~Player();

    bool hasMonopoly();
    void buy();
    void auction();
    void mortgage();
    void unmortgage();
    void trade();
    void bankrupt();
    void improve();

};

#endif /* player_hpp */
