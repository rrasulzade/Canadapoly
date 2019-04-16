//
//  textDisplay.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "textDisplay.hpp"
#include "player.hpp"
#include "collectible.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>


#define MAX_ROW                 67
#define MAX_COLUMN              111
#define MAX_PLAYER              8
#define IMPROVEMENT_OFFSET      0               // 1st line of a slot to display improvements
#define OWNER_ROW_OFFSET        1               // 2nd line of a slot to display owner symbol
#define VISITOR_OFFSET          4               // 5th line of a slot to display player symbol
#define OWNER_NAME_OFFSET       7

using namespace std;

TextDisplay::TextDisplay() {

    theDisplay = new char* [MAX_ROW];
    for (int i = 0; i < MAX_ROW; i++) {
        theDisplay[i] = new char[MAX_COLUMN];
        for(int j = 0; j < MAX_COLUMN; j++){
            theDisplay[i][j] = ' ';
        }
    }

    ifstream in;
    in.open("board.txt");
    string a;

    for(int i = 0; i < MAX_ROW; i++){
        getline(in, a);
        for(int j = 0; j < MAX_COLUMN; j++){
             theDisplay[i][j] = a[j];
        }
    }

    // boardPlayer = new char * [MAX_PLAYER];
    // for (int i = 0; i < MAX_PLAYER; i++) {
    //     boardPlayer[i] = new char [member];
    //     for (int j = 0; j < member; j++) {
    //         boardPlayer[i][j] = 'f';
    //     }
    // }
}


TextDisplay::~TextDisplay(){}

void TextDisplay::printBanner(){
    ifstream in;
    in.open("banner.txt");
    string a;

    while(getline(in, a)){
        cout << a << endl;
    }
}

ostream &operator<<(ostream &out, const TextDisplay &td){
    for(int i = 0; i < MAX_ROW; i++) {
        for(int j = 0; j < MAX_COLUMN; j++) {
            out<<td.theDisplay[i][j];
        }
        out<<endl;
    }
    return out;
}

void TextDisplay::movePlayer(const Player* player, const pair<int, int> location){
    const int playerID = player->getID();
    const char symbol = player->getPiece();

    const int col = location.second + playerID;
    const int row = location.first + VISITOR_OFFSET;

    // cout << playerID << " " << col << " " << row << endl;
    // cout << playerCurPosition.size() << endl;

    if(playerCurPosition.size() <= playerID) {
        playerCurPosition.push_back(location);
    } else {
        const pair<int, int> currentLocation = playerCurPosition[playerID];
        int curCol = currentLocation.second + playerID;
        int curRow = currentLocation.first + VISITOR_OFFSET;

        // cout << playerID << " " << curCol << " " << curRow << endl;
        theDisplay[curRow][curCol] = ' ';
    }

    // update current position and display
    playerCurPosition[playerID] = location;
    theDisplay[row][col] = symbol;
}


void TextDisplay::addOwner(const Player* player){
    const char symbol = player->getPiece();
    const int playerID = player->getID();
    string owner = "owner: ";
    owner += symbol;

    const pair<int, int> currentLocation = playerCurPosition[playerID];
    const int col = currentLocation.second;
    const int row = currentLocation.first + OWNER_ROW_OFFSET;

    for(unsigned int i = 0; i < owner.size(); i++){
        theDisplay[row][col+i] = owner[i];
    }
}

void TextDisplay::updateOwner(const pair<int, int> &loc1, const pair<int, int> &loc2){
    const int col1 = loc1.second + OWNER_NAME_OFFSET;
    const int row1 = loc1.first + OWNER_ROW_OFFSET;

    const int col2 = loc2.second + OWNER_NAME_OFFSET;
    const int row2 = loc2.first + OWNER_ROW_OFFSET;

    char symbol = theDisplay[row1][col1];
    theDisplay[row1][col1] = theDisplay[row2][col2];
    theDisplay[row2][col2] = symbol;
}

void TextDisplay::updateOwner(const char& ownerSymbol, const pair<int, int> &loc){
    const int col = loc.second + OWNER_NAME_OFFSET;
    const int row = loc.first + OWNER_ROW_OFFSET;

    theDisplay[row][col] = ownerSymbol;
}


void TextDisplay::updateMortgage(const pair<int, int> location){
    const int col = location.second;
    const int row = location.first + IMPROVEMENT_OFFSET;
    string word = "MORTGAGED";
    for(unsigned int i = 0; i < word.size(); i++)
        if(theDisplay[row][col + i] == word[i]){
            theDisplay[row][col + i] = ' ';
        }else{
            theDisplay[row][col + i] = word[i];
        }
}

void TextDisplay::updateImprovement(const std::pair<int, int>& location, const int& levelOffset) const {
    const int col = location.second + levelOffset;
    const int row = location.first + IMPROVEMENT_OFFSET;
    if(theDisplay[row][col] == 'I')
        theDisplay[row][col] = ' ';
    else
        theDisplay[row][col] = 'I';
}

void TextDisplay::printAssets(const Player* p){
    const char symbol = p->getPiece();
    const int playerID = p->getID();
    const string name = p->getName();
    const int balance = p->getBalance();
    const int propertyCount = p->getPropertyCount();
    std::vector<Collectible* > properties = p->getProperties();

    cout << "Player " << playerID+1 << " assets:" << endl;
    cout << "Name: " << name << endl;
    cout << "Symbol: " << symbol << endl;
    cout << "Remaining balance: $" << balance << endl;
    cout << "Number of properties: " << propertyCount << endl;
    for(int i=0; i < properties.size(); i++){
        cout <<"\t" << i+1 << ". " << properties[i]->getName() << endl;
    }
}
