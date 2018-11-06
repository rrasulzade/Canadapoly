//
//  gameBoard.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "gameBoard.hpp"
#include "dice.hpp"
#include "player.hpp"
#include "slot.hpp"
#include "academic.hpp"
#include "gym.hpp"
#include "residence.hpp"
#include "slc.hpp"
#include "needleshall.hpp"


#define SLOTS_NUM  40




using namespace std;

GameBoard::GameBoard(): players(nullptr) {
    dice = new Dice();
    slots[0] = new Slot("Collect OSAP", make_pair(61, 101));
    slots[1] = new Academic("AL", make_pair(61, 91), Academic::FREE, 40, 2, "Arts1", 50, 0, {2,10,30,90,160,250});
    slots[2] = new SLC("SLC1", make_pair(61, 81));
    slots[3] = new Academic("ML", make_pair(61, 71), Academic::FREE, 60, 2, "Arts1", 50, 0, {4,20,60,180,320,450});
    slots[4] = new Slot("Tuition", make_pair(61, 61));
    slots[5] = new Residence("MKV", make_pair(61, 51), Residence::FREE, 100, 4);
    slots[6] = new Academic("ECH", make_pair(61, 41), Academic::FREE, 100, 3, "Arts2", 50, 0, {6,30,90,270,400,550});
    slots[7] = new Needleshall("Needles1", make_pair(61, 31));
    slots[8] = new Academic("PAS", make_pair(61, 21), Academic::FREE, 100, 3, "Arts2", 50, 0, {6,30,90,270,400,550});
    slots[9] = new Academic("HH", make_pair(61, 11), Academic::FREE, 120, 3, "Arts2", 50, 0, {8,40,100,300,450,600});
    slots[10] = new Slot("DC Tims line", make_pair(61, 1));
    slots[11] = new Academic("RCH", make_pair(55, 1), Academic::FREE, 140, 3, "Eng", 100, 0, {10,50,150,450,625,750});
    slots[12] = new Gym("PAC", make_pair(49, 1), Gym::FREE, 150, 2);
    slots[13] = new Academic("DWE", make_pair(43, 1), Academic::FREE, 140, 3, "Eng", 100, 0, {10,50,150,450,625,750});
    slots[14] = new Academic("CPH", make_pair(37, 1), Academic::FREE, 160, 3, "Eng", 100, 0, {12,60,180,500,700,900});
    slots[15] = new Residence("UWP", make_pair(31, 1), Residence::FREE, 100, 4);
    slots[16] = new Academic("LHI", make_pair(25, 1), Academic::FREE, 180, 3, "Health", 100, 0, {14,70,200,550,750,950});
    slots[17] = new SLC("SLC2", make_pair(19, 1));;
    slots[18] = new Academic("BMH", make_pair(13, 1), Academic::FREE, 180, 3, "Health", 100, 0, {14,70,200,550,750,950});
    slots[19] = new Academic("OPT", make_pair(7, 1), Academic::FREE, 200, 3, "Health", 100, 0, {16,80,220,600,800,1000});
    slots[20] = new Slot("Goose Nesting", make_pair(1, 1));;
    slots[21] = new Academic("EV1", make_pair(1, 11), Academic::FREE, 220, 3, "Env", 150, 0, {18,90,250,700,875,1050});
    slots[22] = new Needleshall("Needless2", make_pair(1, 21));
    slots[23] = new Academic("EV2", make_pair(1, 31), Academic::FREE, 220, 3, "Env", 150, 0, {18,90,250,700,875,1050});
    slots[24] = new Academic("EV3", make_pair(1, 41), Academic::FREE, 240, 3, "Env", 150, 0, {20,100,300,750,925,1100});
    slots[25] = new Residence("V1", make_pair(1, 51), Residence::FREE, 100, 4);
    slots[26] = new Academic("PHYS", make_pair(1, 61), Academic::FREE, 260, 3, "Sci1", 150, 0, {22,110,330,800,975,1150});
    slots[27] = new Academic("B1", make_pair(1, 71), Academic::FREE, 260, 3, "Sci1", 150, 0, {22,110,330,800,975,1150});
    slots[28] = new Gym("CIF", make_pair(1, 81), Gym::FREE, 150, 2);
    slots[29] = new Academic("B2", make_pair(1, 91), Academic::FREE, 280, 3, "Sci1", 150, 0, {24,120,360,850,1025,1200});
    slots[30] = new Slot("Go to Tims", make_pair(1, 101));
    slots[31] = new Academic("EIT", make_pair(7, 101), Academic::FREE, 300, 3, "Sci2", 200, 0, {26,130,390,900,1100,1275});
    slots[32] = new Academic("ESC", make_pair(13, 101), Academic::FREE, 300, 3, "Sci2", 200, 0, {26,130,390,900,1100,1275});
    slots[33] = new SLC("SLC3", make_pair(19, 101));
    slots[34] = new Academic("C2", make_pair(25, 101), Academic::FREE, 320, 3, "Sci2", 200, 0, {28, 150, 450, 1000, 1200, 1400});
    slots[35] = new Residence("REV", make_pair(31, 101), Residence::FREE, 100, 4);
    slots[36] = new Needleshall("Needless3", make_pair(37, 101));
    slots[37] = new Academic("MC", make_pair(43, 101), Academic::FREE, 350, 2, "Math", 200, 0, {35,175,500,1100,1300,1500});
    slots[38] = new Slot("Coop Fee", make_pair(49, 101));
    slots[39] = new Academic("DC", make_pair(55, 101), Academic::FREE, 400, 2, "Math", 200, 0, {50,200,600,1400,1700,2000});

}

GameBoard::~GameBoard(){
    for(int i = 0; i < SLOTS_NUM; i++){
        delete slots[i];
    }

    for(int i = 0; i < totalPlayers; i++){
        delete players[i];
    }
}


void GameBoard::initializePlayers(const int playerNum){
    this->totalPlayers = playerNum;
    this->players = new Player*[this->totalPlayers];
    for(int i=0; i < this->totalPlayers; i++){
        players[i] = nullptr;
    }
}

Player* GameBoard::addPlayer(const int id, const std::string name, const char symbol, const int slotID){
    this->players[id] = new Player(name, symbol, slotID);
    return this->players[id];
}


pair<int,int> GameBoard::getLocationBySlotID(const int slotID){
    return slots[slotID]->getLocation();
}

Slot* GameBoard::getSlotByID(const int& slotID){
    return slots[slotID];
}

Slot* GameBoard::getSlotByName(const string& slotName){
    for(int i = 0; i < SLOTS_NUM; i++){
        if(slots[i]->getName() == slotName){
            return slots[i];
        }
    }
    return  nullptr;
}

int GameBoard::rollDice(){
    dice->roll();
    return dice->getSum();
}

string GameBoard::diceResults(){
    return dice->getResults();
}

bool GameBoard::isPair(){
    return dice->isPair();
}


bool GameBoard::isSlotFree(const int& slotID){
    return slots[slotID]->getStatus() == Ownable::FREE;
}

bool GameBoard::isSlotOwned(const int& slotID){
    return slots[slotID]->getStatus() == Ownable::OWNED;
}

bool GameBoard::isSlotMortgaged(const int& slotID){
    return slots[slotID]->getStatus() == Ownable::MORTGAGED;
}

Player* GameBoard::getPlayerByID(const int& playerID){
    return players[playerID];
}

void GameBoard::setDice(int d1, int d2){
    dice->setDice(d1, d2);
}

Player* GameBoard::getPlayerByName(const string& name){
    for(int i = 0; i < totalPlayers; i++){
        if(players[i]->getName() == name){
            return players[i];
        }
    }
    return  nullptr;
}

void GameBoard::updatePlayer(int& curPlayerID, const int& diceSum){
    // move player and update locationID
    Player* curPlayer = this->players[curPlayerID];
    const int nextPosition = (curPlayer->getPosition() + diceSum) % SLOTS_NUM;
    curPlayer->setPosition(nextPosition);
}

bool GameBoard::tryBuy(const int& playerID, const int& slotID){
    Player* curPlayer = players[playerID];
    Ownable* property = dynamic_cast<Ownable*> (slots[slotID]);
    int cost = property->getCost();
    // not enough money to buy
    if(curPlayer->getBalance() < cost){
        return false;
    }

    property->setOwner(curPlayer);
    curPlayer->attachProperty(property);
    curPlayer->updateBalance(-1*cost);

    return true;
}
