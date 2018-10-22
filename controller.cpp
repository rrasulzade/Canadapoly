//
//  controller.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include <sstream>
#include <fstream>

#include "controller.hpp"
#include "gameBoard.hpp"
#include "textDisplay.hpp"

#define MAX_PLAYER          8
#define MIN_PLAYER          2
#define START_POSITION      0

using namespace std;


Controller::Controller(GameBoard *board, TextDisplay *td): board(board), td(td){
     // this->board = new GameBoard;
     // this->td = new TextDisplay;

    ifstream in;
    in.open("pieces.txt");

    for(int i = 0; i < MAX_PLAYER; i++){
        char sym, delim;
        string description;
        if(!(in >> sym)) { cout << "Invalid symbol. Please check pieces.txt file!"; }

        // get the rest of the line
        getline(in, description);
        symbols.insert(pair<char, string>(sym, description.substr(1)));
    }
}


Controller::~Controller(){
    delete board;
    delete td;
}


void Controller::initialize(){
    int playerCounter;
    string in;

    cout << "Please, enter the number of players in range from 2 to 8:" << endl;
    while(1){
        getline(cin, in);
        stringstream ss(in);
        if( ss >> playerCounter && (playerCounter >=MIN_PLAYER && playerCounter <= MAX_PLAYER)) {
            break;
        }
        cout << "Invalid number of players! Enter a valid number of players:" << endl;
    }

    board->initializePlayers(playerCounter);
    int i = 0;
    while(i < playerCounter){
        cout<<"------------------ PLAYER# " << i+1 << " ------------------"<< endl;
        cout<<"Please enter your NAME and the corresponding SYMBOL you want to use ";
        cout<<"to represent you."<<endl;
        printSymbols();
        cout<<"The format of the input should be 'NAME SYMBOL' followed by enter."<<endl;

        getline(cin, in);
        stringstream ss(in);

        string name = "", symbol = "";
        ss >> skipws >> name >> symbol;
        if(name.empty() || symbol.empty() || symbol.size() > 1 || !checkAndUpdateSymbols(symbol[0])){
            cout << "\n\tInvalid or missing input! Please, try to re-enter details.\n\n" << endl;
            continue;
        }

        board->addPlayer(i, name, symbol[0]);

        const pair <int, int> startLocation = board->getLocationByID(START_POSITION);
        td->addPlayer(i, symbol[0], startLocation);

        i++;
    }

    // print initial board
    cout << *td << endl;
}

void Controller::printSymbols(){
    for(auto& it : symbols){
        cout << it.first << " for " << it.second << endl;
    }
}

bool Controller::checkAndUpdateSymbols(const char &symbol){
    for(auto& it : symbols){
        if(it.first == symbol){
            symbols.erase(it.first);
            return true;
        }
    }
    return false;
}
