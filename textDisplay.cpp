//
//  textDisplay.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "textDisplay.hpp"
#include "player.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>


#define MAX_ROW             67
#define MAX_COLUMN          111
#define MAX_PLAYER          8
#define IMPROVEMENT_OFFSET  0               // 1st line of a slot to display improvements
#define OWNER_OFFSET        1               // 2nd line of a slot to display owner symbol
#define VISITOR_OFFSET      4               // 5th line of a slot to display player symbol


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


ostream &operator<<(ostream &out, const TextDisplay &td){
    for(int i = 0; i < MAX_ROW; i++) {
        for(int j = 0; j < MAX_COLUMN; j++) {
            out<<td.theDisplay[i][j];
        }
        out<<endl;
    }
    return out;
}

void TextDisplay::updatePlayer(const Player* player, const pair<int, int> location){
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
