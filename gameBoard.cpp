//
//  gameBoard.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "gameBoard.hpp"


#define SLOTS_NUM  40

GameBoard:: GameBoard(): players(nullptr) {
    slots[0] = nullptr;
    slots[1] = nullptr;
    slots[2] = nullptr;
    slots[3] = nullptr;
    slots[4] = nullptr;
    slots[5] = nullptr;
    slots[6] = nullptr;
    slots[7] = nullptr;
    slots[8] = nullptr;
    slots[9] = nullptr;
    slots[10] = nullptr;
    slots[11] = nullptr;
    slots[12] = nullptr;
    slots[13] = nullptr;
    slots[14] = nullptr;
    slots[15] = nullptr;
    slots[16] = nullptr;
    slots[17] = nullptr;
    slots[18] = nullptr;
    slots[19] = nullptr;
    slots[20] = nullptr;
    slots[21] = nullptr;
    slots[22] = nullptr;
    slots[23] = nullptr;
    slots[24] = nullptr;
    slots[25] = nullptr;
    slots[26] = nullptr;
    slots[27] = nullptr;
    slots[28] = nullptr;
    slots[29] = nullptr;
    slots[30] = nullptr;
    slots[31] = nullptr;
    slots[32] = nullptr;
    slots[33] = nullptr;
    slots[34] = nullptr;
    slots[35] = nullptr;
    slots[36] = nullptr;
    slots[37] = nullptr;
    slots[38] = nullptr;
    slots[39] = nullptr;

}

GameBoard:: ~GameBoard(){
    for(int i = 0; i < SLOTS_NUM; i++){
        delete slots[i];
    }

    for(int i = 0; i < totalPlayers; i++){
        delete players[i];
    }
}
