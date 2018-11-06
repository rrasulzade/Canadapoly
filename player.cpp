//
//  player.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "player.hpp"
#include "ownable.hpp"

#define START_BALANCE           50000


using namespace std;

int Player::playerID = 0;

Player::Player(const string name, const char piece, int position): name(name), piece(piece), id(playerID++), money(START_BALANCE), position(position) {}

Player::~Player(){}

int Player::getID() const{
    return this->id;
}

string Player::getName() const{
    return this->name;
}

char Player::getPiece() const{
    return this->piece;
}

int Player::getPosition() const{
    return this->position;
}

int Player::getBalance() const{
    return this->money;
}

int Player::getPropertyCount() const{
    return this->properties.size();
}

void Player::updateBalance(const int amount){
    this->money += amount;
}

void Player::setPosition(const int position){
    this->position = position;
}

void Player::attachProperty(Ownable* property){
    this->properties.push_back(property);
}

void Player::detachProperty(Ownable* property){
    int index = 0;
    for(auto it : properties){
        if(it == property) break;
        index++;
    }
    this->properties.erase(properties.begin() + index-1);
}

bool Player::hasMonopoly(const Ownable* property) const{
    int totalBlocks = countOwnedBlocks(property);
    // const string monopolyBlock = property->getMonopolyBlock();
    // int totalBlocks = property->getTotalBlocks();
    //
    // for(int i = 0; i < properties.size() && totalBlocks > 0; i++){
    //     if(properties[i]->getMonopolyBlock() == monopolyBlock){
    //         totalBlocks--;
    //     }
    // }

    if(totalBlocks == property->getTotalBlocks())
        return true;

    return false;
}

int Player::countOwnedBlocks(const Ownable* property) const{
    const string monopolyBlock = property->getMonopolyBlock();
    int totalBlocks = 0;
    for(int i = 0; i < properties.size(); i++){
        if(properties[i]->getMonopolyBlock() == monopolyBlock){
            totalBlocks++;
        }
    }
    return totalBlocks;
}
