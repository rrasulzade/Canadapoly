#include <sstream>
#include <fstream>


#include "controller.hpp"
#include "gameBoard.hpp"
#include "textDisplay.hpp"
#include "player.hpp"
#include "slot.hpp"
#include "collectible.hpp"
#include "vicinity.hpp"

#define MAX_PLAYER              8
#define MIN_PLAYER              2
#define MAX_DOUBLES             3
#define START_LOCATION          0
#define INCOME_TAX_LOCATION     4
#define TIMS_LOCATION           10
#define SALES_TAX_LOCATOION     38
#define TIMS_LINE_FEE           50

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
    // print banner
    td->printBanner();

    // set up game
    while(1){
        cout << "Please enter number of players (2-8):" << endl;
        getline(cin, in);
        stringstream ss(in);
        if( ss >> totalPlayers && (totalPlayers >= MIN_PLAYER && totalPlayers <= MAX_PLAYER)) {
            break;
        }
        cout << "Invalid number of players!" << endl;
    }

    board->initializePlayers(totalPlayers);
    int i = 0;
    while(i < totalPlayers){
        cout << "\n";
        cout<<"------------------ PLAYER " << i+1 << " ------------------"<< endl;
        cout<<"Please enter your NAME and choose your SYMBOL from the following list:"<<endl;
        printSymbols();
        cout<<"Note: input format is 'NAME SYMBOL'"<<endl;

        getline(cin, in);
        stringstream ss(in);

        string name = "", symbol = "";
        ss >> skipws >> name >> symbol;
        if(name.empty() || symbol.empty() || symbol.size() > 1 || !checkAndUpdateSymbols(symbol[0])){
            cout << "\nInvalid or missing input! Please, try to re-enter details.\n\n" << endl;
            continue;
        }

        Player* player = board->addPlayer(i, name, symbol[0], START_LOCATION);
        const pair<int, int> location = board->getLocationBySlotID(player->getPosition());
        td->movePlayer(player, location);

        i++;
    }

    // print initial board
    cout << *td << endl;
}

void Controller::play(){

    bool rolled = false , debtPaid = true;
    Player* player = board->getPlayerByID(curPlayerID);

    while(1){
        string in;
        stringstream ss;
        bool inTims = player->isInTims();
        if(debtPaid){
            cout << "- - - - Player " << player->getPiece() << "'s turn - - - -" << endl;
            cout << "\n+ + + + Enter one of the following commands to proceed + + + + + + + + + + + +" << endl;
            cout << "+ 'assets'\t\t\t\t to print your total assets" << endl;
            cout << "+ 'mortgage <property name>'\t\t to mortgage a property" << endl;
            cout << "+ 'unmortgage <property name>'\t\t to unmortgage a property" << endl;
            cout << "+ 'trade <name> <give> <receive>'\t to offer a trade" << endl;
            cout << "+ 'improve <property> buy/sell'\t\t to buy/sell an improvement" << endl;
            if(inTims) cout << "+ 'pay' \t\t\t\t to pay $50 fee to leave Tims line" << endl;
            if(!rolled)
                cout << "+ 'roll'\t\t\t\t to roll dice" << endl;
            else
                cout << "+ 'next'\t\t\t\t to give control to the next player" << endl;
            cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + \n" << endl;

            // read user inputs
            getline(cin, in);
            ss.str(in);
            ss >> in;
        } else {
            cout << "All debts must be paid!" << endl;
        }


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
                cout << "Use 'improve <property> buy/sell' to buy/sell an improvement." << endl;
                continue;
            }
            cout << *td << endl;
        }
        else if(in == "pay"){
            if(!payTimsLineFee(player)){
                cout << "PLAYER LEFT TO BANKRUPTCY" << endl;
            }
        }
        else if((in == "roll" || in == "r") && !rolled){
            int d1 , d2;
            stringstream message;
            ss >> d1 >> d2;
            board->setDice(d1, d2);
            int diceSum  = d1+d2; //board->rollDice();

            if(!board->isPair()){
                rolled = true;
                if(inTims){
                    player->decreaseDoublesCounter();
                    if(player->getDoublesCounter() == 0) {
                        cout << "This was your last chance to try to roll doubles but no success. " << endl;
                        cout << "You must pay to leave Tims line now. " << endl;
                        if(!payTimsLineFee(player)){
                            cout << "PLAYER LEFT TO BANKRUPTCY" << endl;
                        }
                    }
                } else {
                    player->setDoublesCounter(0);
                }
            }else{
                if(inTims){
                    player->setTims(false);
                    player->setDoublesCounter(0);
                    rolled = true;
                }else{
                    player->increaseDoublesCounter();
                }
            }

            if(player->getDoublesCounter() == MAX_DOUBLES){
                message << "Tims coffee time. You rolled 3 doubles in a row." << endl;
                player->setTims(true);
                player->setPosition(TIMS_LOCATION);
                diceSum = 0;
            } else {
                board->movePlayer(curPlayerID, diceSum);
            }

            int playerCurPosition = player->getPosition();
            const pair<int, int> location = board->getLocationBySlotID(playerCurPosition);
            td->movePlayer(player, location);

            cout << *td << endl;
            cout << board->diceResults() << endl;
            if (!message.str().empty() ) cout << message.str() << endl;


            if(player->isInTims()){
                endTurn(&player);
                continue;
            }

            if(playerCurPosition - diceSum < 0 ){
                board->collectIncome(curPlayerID);
            }

            if((playerCurPosition == SALES_TAX_LOCATOION &&
                !(board->tryPayTax(curPlayerID, SALES_TAX)) &&
                !handleLowBalance(player, SALES_TAX, true)) ||
                (playerCurPosition == INCOME_TAX_LOCATION &&
                !(board->tryPayTax(curPlayerID, INCOME_TAX)) &&
                !handleLowBalance(player, INCOME_TAX, true)))
            {
                cout << "PLAYER LEFT TO BANKRUPTCY" << endl;

            }
            else if(board->isSlotFree(playerCurPosition)){
                cout << "This slot is available. Do you want to buy or auction? buy/auction " << endl;
                // print slot details - NAME PRICE -
                string slotDetails = board->getCollectibleBuyInfo(playerCurPosition);
                cout << slotDetails << endl;

                while(1){
                    in.clear();
                    if(in.empty()) getline(cin, in);
                    if(in == "buy" || in == "b"){
                        if(board->tryBuy(curPlayerID, playerCurPosition)){
                            td->addOwner(player);
                            cout << *td << endl;
                            cout << "Congrats! You've just bought a new property." << endl;
                            break;
                        } else {
							Collectible* property = dynamic_cast<Collectible*>(board->getSlotByID(playerCurPosition));
                            if(!handleLowBalance(player, property->getCost())) {
                                in = "auction";
                            } else {
                                in = "buy";
                            }
                        }
                    }
                    else if(in == "auction" || in == "a"){
                        //auction(curPlayerID, playerCurPosition);
                        break;
                    }
                    else {
                        cout << "Invalid operation name. Please enter 'buy' or 'auction' to proceed: " << endl;
                    }
                }
            } else if(board->isSlotOwned(playerCurPosition)){
				Collectible* property = dynamic_cast<Collectible*>(board->getSlotByID(playerCurPosition));
                if(property->getOwner() != player){
                    debtPaid = payDebt(property, player);
                }
            }
        }
        else if((in == "next" || in == "n") && rolled){
            endTurn(&player);
            rolled = false;
        }
        else {
            cout << "\n Invalid command! \n" << endl;
        }
    }
}

bool Controller::payTimsLineFee(Player* p){
    if(p->getBalance() < TIMS_LINE_FEE && !handleLowBalance(p, TIMS_LINE_FEE, true)){
        return false;
    }

    p->updateBalance(-1*TIMS_LINE_FEE);
    p->setTims(false);
    p->setDoublesCounter(0);
    return true;
}

void Controller::endTurn(Player** p){
    curPlayerID = curPlayerID == totalPlayers-1 ? 0 : curPlayerID+1;
    *p = board->getPlayerByID(curPlayerID);
}

bool Controller::handleLowBalance(Player* player, int moneyNeeded, bool forced){
    cout<<"Insufficient balance. " << endl;
    while(1){
        int remaining = moneyNeeded - player->getBalance();

        if(remaining <= 0) {
            cout << "You have collected sufficient amount of money to proceed. " << endl;
            return true;;
        } else {
            cout << "You have to collect $" << remaining << " to complete the operation. " << endl;
        }

        cout << "\n+ + + + Enter one of the following commands to proceed + + + + + + + + + + + +" << endl;
        cout << "+ 'assets'\t\t\t\t to print your total assets" << endl;
        cout << "+ 'bankrupt'\t\t\t\t to declare bankruptcy" << endl;
        cout << "+ 'mortgage <property name>'\t\t to mortgage a property" << endl;
        cout << "+ 'trade <name> <give> <receive>'\t to offer a trade" << endl;
        cout << "+ 'improve <property> sell'\t\t to sell an improvement" << endl;
        if(!forced)
            cout << "+ 'cancel'\t\t\t\t to cancel operation" << endl;
        cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n" << endl;

        string in;
        getline(cin, in);
        stringstream ss(in);
        ss >> in;

        if(in == "assets" || in == "a"){
            td->printAssets(player);
        }
        else if(in == "mortgage" || in == "m"){
            string property;
            ss >> property;
            if(!mortgage(player, property)){
                cout << "Use 'mortgage <property name>' format to mortgage a property." << endl;
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
            string propertyName, action;
            if(!(ss>>propertyName) || !(ss>>action) || action != "sell"){
                cout << "Invalid input. " << endl;
                cout << "Use 'improve <property> sell' to sell an improvement." << endl;
            }
            else if(!improve(player, ss.str())){
                cout << "Use 'improve <property> sell' to sell an improvement." << endl;
                continue;
            }
            cout << *td << endl;
        }
        else if(in == "bankrupt" || in == "b"){
            break;
        }
        else if((in == "cancel" || in == "c") && !forced){
            //cout << "Operation is cancelled! \n" << endl;
            break;
        }

    }

    return false;
}



bool Controller::mortgage(Player* p, const std::string& propertyName){
	Collectible* property = dynamic_cast<Collectible*>(board->getSlotByName(propertyName));
    if(property == nullptr){
        cout << "Invalid input. " << propertyName << " is not a valid propety to mortgage." << endl;
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
	Collectible* property = dynamic_cast<Collectible*>(board->getSlotByName(propertyName));
    int cost = property->getCost()/2 * 1.10;

    if(property == nullptr){
        cout << "Invalid input. " << propertyName << " is not a valid propety to unmortgage." << endl;
        return false;
    }
    if(property->getOwner() != p){
        cout<<"Invalid input. " << propertyName << " does not belong to you."<<endl;
        return false;
    }
    if(p->getBalance() < cost && !handleLowBalance(p, cost)) {
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

		Collectible *property = dynamic_cast<Collectible*>(board->getSlotByName(receive));
        money = stoi(give);
        if(!property){
            cout << "Trade is rejected. "<< receive << " is not a valid property for trading." << endl;
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
		Collectible *property = dynamic_cast<Collectible*>(board->getSlotByName(give));
        money = stoi(receive);

        if(!property){
            cout << "Trade is rejected. "<< give << " is not a valid property for trading." << endl;
        }
        else if(property->getOwner() != p){
            cout << "Trade is rejected. " ""<< give << " is not owned by " << p->getName() << "." << endl;
        }
        else {
            finishTrade(p2, p, -1*money, property);
            status = true;
        }

    } else {                             // trade a property in return of a property
		Collectible *propertyGive = dynamic_cast<Collectible*>(board->getSlotByName(give));
		Collectible *propertyReceive = dynamic_cast<Collectible*>(board->getSlotByName(receive));

        if(!propertyGive){
            cout << "Trade is rejected. " << give << " is not a valid property for trading." << endl;
        }
        else if(!propertyReceive){
            cout << "Trade is rejected. "<< receive << " is not a valid property for trading." << endl;
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


void Controller::finishTrade(Player* p1, Player* p2, Collectible *give, Collectible *receive){
    cout << "A message for " << p2->getName() << ": " << endl;
    cout << p1->getName() << " offers you " <<give->getName()<< " for "<<receive->getName()<<"."<<endl;

    while(1){
        cout << "Do you accept this offer? (y/n)"<<endl;
        cout << "Note: You can check your balance by typing 'assets'."<<endl;
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
            break;
        }
        else if(in == "assets" || in == "a")
            td->printAssets(p2);
    }
}


void Controller::finishTrade(Player* p1, Player* p2, int money, Collectible *property){
    if (money < 0){
        money *= -1;
        cout << "A message for " << p1->getName() << ": " << endl;
        cout << p2->getName() << " offers you " <<property->getName()<< " for "<< money<<"."<<endl;
    }
    else{
        if(p1->getBalance() < money && !handleLowBalance(p1, money)){
                cout << "Trade is rejected." << endl;
                return;
        }
        cout << "A message for " << p2->getName() << ": " << endl;
        cout << p1->getName() << " offers you " <<money<< " for "<<property->getName()<<"."<<endl;
    }

    while(1){
        cout << "Do you accept this offer? (y/n)"<<endl;
        cout << "Note: You can check your balance by typing 'assets'."<<endl;
        string in;
        if(getline(cin, in) && (in == "y" || in == "Y")){
            p1->updateBalance(-1*money);
            p2->detachProperty(property);
            p1->attachProperty(property);
            p2->updateBalance(money);
            property->setOwner(p1);
            td->updateOwner(p1->getPiece(), property->getLocation());
            cout << "Trade is completed successfully!" << endl;
            break;
        }
        else if(in == "assets" || in == "a")
            td->printAssets(p2);
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

    Vicinity* property = dynamic_cast<Vicinity*>(board->getSlotByName(propertyName));
    if(!property){
        cout << propertyName << " is not a valid property for an improvement. " << endl;
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

    int upgradeLevel = property->getUpgradeLevel();

    if(action == "buy" ){
        if(cost > p->getBalance() && !handleLowBalance(p, cost)){
                cout << "Improvement is rejected." << endl;
                return false;
        }
        if(upgradeLevel == 5){
            cout << "No improvements to buy." << endl;
            return false;
        }
        upgradeLevel++;
        td->updateImprovement(property->getLocation(), upgradeLevel);
        cost *= -1;
    }
    else if(action == "sell" && upgradeLevel >= 0){
        if(upgradeLevel == 0){
            cout << "No improvements to sell." << endl;
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
    property->setAsset(cost);
    p->updateBalance(cost);


    return true;
}


bool Controller::payDebt(Collectible* property, Player* p){
    int debt = property->getRentalCost(p);
    string ownerName = property->getOwner()->getName();
    if(debt == 4 || debt == 10){
        cout << "You landed on a gym." << endl;
        int sum = board->rollDice();
        cout << board->diceResults() << endl;
        debt *= sum;
    }

    if(debt > p->getBalance() && !handleLowBalance(p, debt, true)) {
            return false;
    }

    p->updateBalance(-1*debt);
    property->getOwner()->updateBalance(debt);

    cout << "You paid $" << debt << " rental fee to " << ownerName << endl;
    return true;
}


bool Controller::auction(int playerID, int propertyID){
    Collectible* property = dynamic_cast<Collectible*>(board->getSlotByID(propertyID));
    cout << "Auction of " << property->getName() << " begins!" << endl;
    vector<int> participants;
    // for(int i=0; i < totalPlayers; i++){
    //     participants.push_back()
    // }

    return false;
}
