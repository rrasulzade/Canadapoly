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
#include "academic.hpp"

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

    bool rolled = false , debtPaid = true;
    while(1){

        Player* player = board->getPlayerByID(curPlayerID);

        string in;
        if(debtPaid){
            cout << "\n+ + + + Enter one of the following commands to proceed + + + + + + + + + + + +" << endl;
            cout << "+ 'assets'\t\t\t\t to print total assets of the current player" << endl;
            cout << "+ 'mortgage <property name>'\t\t to mortgage a property" << endl;
            cout << "+ 'unmortgage <property name>'\t\t to unmortgage a property" << endl;
            cout << "+ 'trade <name> <give> <receive>'\t to offer a trade" << endl;
            cout << "+ 'improve <property> buy/sell'\t\t to buy/sell an improvement" << endl;
            if(!rolled)
                cout << "+ 'roll'\t\t\t\t to roll dice" << endl;
            else
                cout << "+ 'next'\t\t\t\t to give control to the next player" << endl;
            cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n" << endl;
        }

        // read user inputs
        getline(cin, in);
        stringstream ss(in);
        ss >> in;

        if(in == "assets" || in == "a"){
            td->printAssets(player);
            continue;
        }
        else if(in == "mortgage" || in == "m"){
            string property;
            ss >> property;
            // !(ss >> property) ||
            if(!mortgage(player, property)){
                cout << "Use 'mortgage <property name>' format to mortgage a property." << endl;
                continue;
            }
            cout << *td << endl;
        }
        else if(in == "unmortgage" || in == "um"){
            string property;
            ss >> property;
            // !(ss >> property) ||
            if(!unmortgage(player, property)){
                cout << "Use 'unmortgage <property name>' format to unmortgage a property." << endl;
                continue;
            }
            cout << *td << endl;
        }
        else if(in == "trade" || in == "t"){
            if(!trade(player, ss.str())){
                cout << "Use 'trade <name> <give> <receive>' to offer a trade." << endl;
                continue;
            }
            cout << *td << endl;
        }
        else if(in == "improve" || in == "im"){
            if(!improve(player, ss.str())){
                cout << "Use 'improve <property> buy/sell' to offer a trade." << endl;
                continue;
            }
            cout << *td << endl;
        }
        else if((in == "roll" || in == "r") && !rolled){
            int d1 , d2;
            ss >> d1 >> d2;
            board->setDice(d1, d2);
            const int diceSum  = d1+d2; //board->rollDice();

            //update board
            board->updatePlayer(curPlayerID, diceSum);
            int playerCurPosition = player->getPosition();
            const pair<int, int> location = board->getLocationBySlotID(playerCurPosition);
            td->updatePlayer(player, location);

            cout << *td << endl;
            cout << board->diceResults() << endl;

            if(board->isSlotFree(playerCurPosition)){
                cout << "This slot is free. Do you want to buy or put it on auction? buy/auction " << endl;
                while(getline(cin, in)){
                    if(in == "buy" || in == "b"){
                        if(board->tryBuy(curPlayerID, playerCurPosition)){
                            td->addOwner(player);
                            cout << *td << endl;
                            cout << "You've just bought a new property!" << endl;
                        } else {
                            cout << "Unfortunately, you don't have enough money to buy this property." << endl;
                            cout << "If has any properties, mortgage then buy. PS: mortgage stats" << endl;
                            cout << "Other option is auction" << endl;
                        }
                        break;
                    }else if(in == "auction"){
                        break;
                    }else {
                        cout << "Invalid operation name. Enter 'buy' or 'auction' to proceed: " << endl;
                    }
                }
            } else if(board->isSlotOwned(playerCurPosition)){
                Ownable* property = dynamic_cast<Ownable*>(board->getSlotByID(playerCurPosition));
                if(property->getOwner() != player){
                    debtPaid = payDebt(property, player);
                }
            } else {

            }

            if(!board->isPair()){
                rolled = true;
            }
        }
        else if((in == "next" || in == "n") && rolled){
            curPlayerID = curPlayerID == totalPlayers-1 ? 0 : curPlayerID+1;
            rolled = false;
        }
    }
}

bool Controller::mortgage(Player* p, const std::string& propertyName){
    Ownable* property = dynamic_cast<Ownable*>(board->getSlotByName(propertyName));
    if(property == nullptr){
        cout << "Invalid input. " << propertyName << " is not a building" << endl;
        return false;
    }
    if(property->getOwner() != p){
        cout<<"Invalid input. " << propertyName << " does not belong to you."<<endl;
        return false;
    }

    property->mortgage();
    td->updateMortgage(property->getLocation());
    return true;
}

bool Controller::unmortgage(Player* p, const std::string& propertyName){
    Ownable* property = dynamic_cast<Ownable*>(board->getSlotByName(propertyName));
    int cost = property->getCost()/2 * 1.10;

    if(property == nullptr){
        cout << "Invalid input. " << propertyName << " is not a building" << endl;
        return false;
    }
    if(property->getOwner() != p){
        cout<<"Invalid input. " << propertyName << " does not belong to you."<<endl;
        return false;
    }
    if(p->getBalance() < cost){
        cout<<"Insufficient balance. " << propertyName << " costs " << cost << " to unmortgage."<<endl;
        return false;
    }

    property->unmortgage();
    td->updateMortgage(property->getLocation());
    return true;
}

// TOD add to utility
bool isNumber(const string& s){
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

bool Controller::trade(Player* p, const string& in){
    string name;
    string give;
    string receive;
    int money;
    bool status = false;
    stringstream ss(in);
    ss >> name;

    if(!(ss>>name)||!(ss>>give)||!(ss>>receive)){     // check for valid input startd here
        cout<<"Invalid input"<<endl;
        return status;
    }

    Player *p2 = board->getPlayerByName(name);
    if(!p2){
        cout<<"Trade is rejected. "<<name<<" is not a valid player."<<endl;
        return status;
    }

    if(p->getName() == name){
        cout<<"Trade is rejected. You can't trade with yourself."<<endl;
        return status;
    }

    if(isNumber(give)) {            // trade money in return of a property
        if(isNumber(receive)) {
            cout << "Trade is rejected. Cannot trade money in return of money." << endl;
            return status;
        }

        Ownable *property = dynamic_cast<Ownable*>(board->getSlotByName(receive));
        money = stoi(give);
        if(p->getBalance() < money) {
            cout << "Trade is rejected. Insufficient balance for trading." << endl;
        }
        else if(!property){
            cout << "Trade is rejected. "<< receive << " is not a valid property name." << endl;
        }
        else if(property->getOwner() != p2){
            cout <<"Trade is rejected. " << receive << " is not owned by " << name << "." << endl;
        }
        else {
            finishTrade(p, p2, money, property);
            status = true;
        }
    }
    else if(isNumber(receive)) {   // trade a property in return of money
        Ownable *property = dynamic_cast<Ownable*>(board->getSlotByName(give));
        money = stoi(receive);

        if(p2->getBalance() < money) {
            cout << "Trade is rejected. Insufficient balance for trading." << endl;
        }
        else if(!property){
            cout << "Trade is rejected. "<< give << " is not a valid property name." << endl;
        }
        else if(property->getOwner() != p){
            cout << "Trade is rejected. " ""<< give << " is not owned by " << p->getName() << "." << endl;
        }
        else {
            finishTrade(p2, p, -1*money, property);
            status = true;
        }

    } else {                             // trade a property in return of a property
        Ownable *propertyGive = dynamic_cast<Ownable*>(board->getSlotByName(give));
        Ownable *propertyReceive = dynamic_cast<Ownable*>(board->getSlotByName(receive));

        if(!propertyGive){
            cout << "Trade is rejected. " << give << " is not a valid property name." << endl;
        }
        else if(!propertyReceive){
            cout << "Trade is rejected. "<< receive << " is not a valid property name." << endl;
        }
        else if(propertyGive->getOwner() != p){
            cout << "Trade is rejected. "<< give << " is not owned by " << p->getName() << "." << endl;
        }
        else if(propertyReceive->getOwner() != p2){
            cout << "Trade is rejected. "<< receive << " is not owned by " << name << "." << endl;
        }
        else {
            finishTrade(p, p2, propertyGive, propertyReceive);
            status = true;
        }
    }

    return status;
}


void Controller::finishTrade(Player* p1, Player* p2, Ownable *give, Ownable *receive){
    cout << "A message for " << p2->getName() << ": " << endl;
    cout << p1->getName() << " offers you " <<give->getName()<< " for "<<receive->getName()<<"."<<endl;
    cout << "Do you accept this offer? (y/n)"<<endl;
    string in;
    if(getline(cin, in) && (in == "y" || in == "Y")){
        p1->detachProperty(give);
        p2->detachProperty(receive);
        p1->attachProperty(receive);
        p2->attachProperty(give);
        give->setOwner(p2);
        receive->setOwner(p1);
        td->updateOwner(give->getLocation(), receive->getLocation());
        cout << "Trade is completed successfully!" << endl;
    }
}


void Controller::finishTrade(Player* p1, Player* p2, int money, Ownable *property){
    cout << "A message for ";
    if (money < 0){
        money *= -1;
        cout << p1->getName() << ": " << endl;
        cout << p2->getName() << " offers you " <<property->getName()<< " for "<< money<<"."<<endl;
    }
    else{
        cout << p2->getName() << ": " << endl;
        cout << p1->getName() << " offers you " <<money<< " for "<<property->getName()<<"."<<endl;
    }
    cout << "Do you accept this offer? (y/n)"<<endl;
    string in;
    if(getline(cin, in) && (in == "y" || in == "Y")){
        p1->updateBalance(-1*money);
        p2->detachProperty(property);
        p1->attachProperty(property);
        p2->updateBalance(money);
        property->setOwner(p1);
        td->updateOwner(p1->getPiece(), property->getLocation());
        cout << "Trade is completed successfully!" << endl;
    }
}

bool Controller::improve(Player* p, const string& in){
    string propertyName, action;
    stringstream ss(in);
    ss >> propertyName;

    if(!(ss>>propertyName) || !(ss>>action)){
        cout << "Invalid input. " << endl;
        return false;
    }

    Academic* property = dynamic_cast<Academic*>(board->getSlotByName(propertyName));
    if(!property){
        cout << propertyName << " is not a valid property name. " << endl;
        return false;
    }

    if(property->getOwner() != p){
        cout << "You are not allowed to build on others properties."<<endl;
        return false;
    }

    if(!p->hasMonopoly(property)){
        cout << "You must own a monopoly before improving." << endl;
        return false;
    }

    int cost = property->getUpgradeCost();
    if(cost == 0){
        cout << propertyName << " cannot be improved. " << endl;
        return false;
    }
    if(cost > p->getBalance()){
        cout << "Insufficient balance. " << endl;
        return false;
    }

    int upgradeLevel = property->getUpgradeLevel();

    if(action == "buy" ){
        if(upgradeLevel == 5){
            cout << "You've already bought all improvements." << endl;
            return false;
        }
        upgradeLevel++;
        td->updateImprovement(property->getLocation(), upgradeLevel);
        cost *= -1;
    }
    else if(action == "sell" && upgradeLevel > 0){
        if(upgradeLevel == 0){
            cout << "You've already sold all improvements." << endl;
            return false;
        }
        td->updateImprovement(property->getLocation(), upgradeLevel);
        upgradeLevel--;
        cost /= 2;
    }
    else {
        cout << action << " is not a valid improvement action." << endl;
        return false;
    }

    property->setUpgradeLevel(upgradeLevel);
    p->updateBalance(cost);


    return true;
}


bool Controller::payDebt(Ownable* property, Player* p){
    int debt = property->getRentalCost(p);
    string ownerName = property->getOwner()->getName();
    if(debt == 4 || debt == 10){
        cout << "You landed on a gym." << endl;
        int sum = board->rollDice();
        cout << board->diceResults() << endl;
        debt *= sum;
        cout << "You paid $" << debt << " gym memebership fee to " << ownerName << endl;
    } else {
        cout << "You paid $" << debt << " rental fee to " << ownerName << endl;
    }

    if(debt > p->getBalance()){
        cout << "Insufficient balance. " << endl;
        return false;
    }
    else {
        p->updateBalance(-1*debt);
        property->getOwner()->updateBalance(debt);
    }

    return true;
}
