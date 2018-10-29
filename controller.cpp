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
#include "player.hpp"
#include "slot.hpp"
#include "ownable.hpp"

#define MAX_PLAYER          8
#define MIN_PLAYER          2
#define START_POSITION      0

using namespace std;


Controller::Controller(GameBoard *board, TextDisplay *td): board(board), td(td){
     // this->board = new GameBoard;
     // this->td = new TextDisplay;
    curPlayerID = 0;
    ifstream in;
    in.open("pieces.txt");

    for(int i = 0; i < MAX_PLAYER; i++){
        char sym;
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

void Controller::initialize(){
    string in;
    cout << "Please, enter the number of players in range from 2 to 8:" << endl;
    while(1){
        getline(cin, in);
        stringstream ss(in);
        if( ss >> totalPlayers && (totalPlayers >=MIN_PLAYER && totalPlayers <= MAX_PLAYER)) {
            break;
        }
        cout << "Invalid number of players! Enter a valid number of players:" << endl;
    }

    board->initializePlayers(totalPlayers);
    int i = 0;
    while(i < totalPlayers){
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

        Player* player = board->addPlayer(i, name, symbol[0], START_POSITION);
        const pair<int, int> location = board->getLocationBySlotID(player->getPosition());
        td->updatePlayer(player, location);

        i++;
    }

    // print initial board
    cout << *td << endl;
}

void Controller::play(){


    while(1){

        Player* player = board->getPlayerByID(curPlayerID);

        string in;
        cout << "Enter" << endl;
        cout << "'next' to continue" << endl;
        cout << "'assets' to print total assets of the current player" << endl;

        getline(cin, in);
        if(in == "assets" || in == "a"){
            td->printAssets(player);
            continue;
        }
        else if(in == "next" || in == "n"){
            //roll dice and print results
            const int diceSum  = board->rollDice();
            cout << board->diceResults() << endl;

            //update board
            board->updatePlayer(curPlayerID, diceSum);
            int playerCurPosition = player->getPosition();
            const pair<int, int> location = board->getLocationBySlotID(playerCurPosition);
            td->updatePlayer(player, location);
            cout << *td << endl;

            if(board->isSlotFree(playerCurPosition)){
                cout << "This slot is free. Do you want to buy or put it on auction? buy/auction " << endl;
                getline(cin, in);
                if(in == "buy" || in == "b"){
                    if(board->tryBuy(curPlayerID, playerCurPosition)){
                        td->updateOwner(player);
                        cout << *td << endl;
                        cout << "You've just bought a new property!" << endl;
                    } else {
                        cout << "Unfortunately, you don't have enough money to buy this property." << endl;
                        cout << "If has any properties, mortgage then buy. PS: mortgage stats" << endl;
                        cout << "Other option is auction" << endl;
                    }
                }else if(in == "auction"){

                }else {
                    cout << "Invalid operation name. Enter 'buy' or 'auction' to proceed: " << endl;
                }
            } else if(board->isSlotOwned(playerCurPosition)){
                Ownable* property = dynamic_cast<Ownable*>(board->getPropertyByID(playerCurPosition));
                cout << "This property is owned by player " << (property->getOwner())->getPiece() << endl;

            } else {

            }
        }
        curPlayerID = curPlayerID == totalPlayers-1 ? 0 : curPlayerID+1;
    }
}
