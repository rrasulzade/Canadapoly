//
//  player.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "player.hpp"

#define START_BALANCE 1500
#define START_POSITION 0


using namespace std;

int Player::playerID = 0;

Player::Player(const string name, const char piece): name(name), piece(piece), id(playerID++), money(START_BALANCE), position(START_POSITION) {}
