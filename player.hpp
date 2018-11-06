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
    const int id;
    int money;
    int position;
    std::vector<Ownable* > properties;

    static int playerID;

public:
    Player(const std::string name, const char piece, int position);
    ~Player();

    bool hasMonopoly(const Ownable* property) const;
    int countOwnedBlocks(const Ownable* property) const;

    // ACCESSORS
    int getPosition() const;
    std::string getName() const;
    int getID() const;
    char getPiece() const;
    int getBalance() const;
    int getPropertyCount() const;

    void setPosition(const int position);
    void updateBalance(const int amount);
    void attachProperty(Ownable* property);
    void detachProperty(Ownable* property);
};

#endif /* player_hpp */
