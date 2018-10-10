//
//  textDisplay.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "textDisplay.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX_ROW = 67;
#define MAX_COLUMN = 111;
#define MAX_PLAYER = 8;
const int member = 3;


TextDisplay::TextDisplay() {

    theDisplay = new char * [MAX_ROW];
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

    boardplayer = new char * [MAX_PLAYER];
    for (int i = 0; i < MAX_PLAYER; i++) {
        boardplayer[i] = new char [member];
        for (int j = 0; j < member; j++) {
            boardplayer[i][j] = 'f';
        }
    }
}


//  Overload operator<<
ostream &operator<<(ostream &out, const TextDisplay &td){
    for(int i=0; i < MAX_ROW; i++) {
        for(int j=0; j < MAX_COLUMN; j++) {
            out<<td.theDisplay[i][j];
        }
        out<<endl;
    }
    return out;
}