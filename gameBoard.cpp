#include "gameBoard.hpp"
#include "dice.hpp"
#include "player.hpp"
#include "slot.hpp"
#include "vicinity.hpp"
#include "service.hpp"
#include "railroad.hpp"
#include "redCross.hpp"
#include "chance.hpp"

#define SLOTS_NUM					40
#define INCOME						200
extern const int INCOME_TAX		=   300;
extern const int SALES_TAX		=   150;


using namespace std;

GameBoard::GameBoard(): players(nullptr) {
    dice = new Dice();
    slots[0] = new Slot("Collect Income", make_pair(61, 101));
    slots[1] = new Vicinity("REGINA", make_pair(61, 91), 40, 2, "SC", 50, 0, {2,10,30,90,160,250});
    slots[2] = new RedCross("RedCross1", make_pair(61, 81));
    slots[3] = new Vicinity("SASKATOON", make_pair(61, 71), 60, 2, "SC", 50, 0, {4,20,60,180,320,450});
    slots[4] = new Slot("Income Tax", make_pair(61, 61));
    slots[5] = new Railroad("Canadian Pacific Railroad", make_pair(61, 51), 100, 4);
    slots[6] = new Vicinity("ATHABASCA", make_pair(61, 41), 100, 3, "AB", 50, 0, {6,30,90,270,400,550});
    slots[7] = new Chance("Chance1", make_pair(61, 31));
    slots[8] = new Vicinity("EDMONTON", make_pair(61, 21), 100, 3, "AB", 50, 0, {6,30,90,270,400,550});
    slots[9] = new Vicinity("CALGARY", make_pair(61, 11), 120, 3, "AB", 50, 0, {8,40,100,300,450,600});
    slots[10] = new Slot("DC Tims line", make_pair(61, 1));
    slots[11] = new Vicinity("LONDON", make_pair(55, 1), 140, 3, "ON1", 100, 0, {10,50,150,450,625,750});
    slots[12] = new Service("Internet Service", make_pair(49, 1), 150, 2);
    slots[13] = new Vicinity("GUELPH", make_pair(43, 1), 140, 3, "ON1", 100, 0, {10,50,150,450,625,750});
    slots[14] = new Vicinity("HAMILTON", make_pair(37, 1), 160, 3, "ON1", 100, 0, {12,60,180,500,700,900});
    slots[15] = new Railroad("Hudson Bay Railroad", make_pair(31, 1), 100, 4);
    slots[16] = new Vicinity("WATERLOO", make_pair(25, 1), 180, 3, "ON2", 100, 0, {14,70,200,550,750,950});
    slots[17] = new RedCross("RedCross2", make_pair(19, 1));;
    slots[18] = new Vicinity("OTTAWA", make_pair(13, 1), 180, 3, "ON2", 100, 0, {14,70,200,550,750,950});
    slots[19] = new Vicinity("TORONTO", make_pair(7, 1), 200, 3, "ON2", 100, 0, {16,80,220,600,800,1000});
    slots[20] = new Slot("Goose Nesting", make_pair(1, 1));;
    slots[21] = new Vicinity("KELOWNA", make_pair(1, 11), 220, 3, "BC", 150, 0, {18,90,250,700,875,1050});
    slots[22] = new Chance("Chance2", make_pair(1, 21));
    slots[23] = new Vicinity("VICTORIA", make_pair(1, 31), 220, 3, "BC", 150, 0, {18,90,250,700,875,1050});
    slots[24] = new Vicinity("VANCOUVER", make_pair(1, 41), 240, 3, "BC", 150, 0, {20,100,300,750,925,1100});
    slots[25] = new Railroad("Via Rail", make_pair(1, 51), 100, 4);
    slots[26] = new Vicinity("GATINEAU", make_pair(1, 61), 260, 3, "QC", 150, 0, {22,110,330,800,975,1150});
    slots[27] = new Vicinity("QUEBEC", make_pair(1, 71), 260, 3, "QC", 150, 0, {22,110,330,800,975,1150});
    slots[28] = new Service("Phone Service", make_pair(1, 81), 150, 2);
    slots[29] = new Vicinity("MONTREAL", make_pair(1, 91), 280, 3, "QC", 150, 0, {24,120,360,850,1025,1200});
    slots[30] = new Slot("Go to Tims", make_pair(1, 101));
    slots[31] = new Vicinity("ROCKIES", make_pair(7, 101), 300, 3, "Attr1", 200, 0, {26,130,390,900,1100,1275});
    slots[32] = new Vicinity("NIAGARA", make_pair(13, 101), 300, 3, "Attr1", 200, 0, {26,130,390,900,1100,1275});
    slots[33] = new RedCross("RedCross3", make_pair(19, 101));
    slots[34] = new Vicinity("CNTOWER", make_pair(25, 101), 320, 3, "Attr1", 200, 0, {28, 150, 450, 1000, 1200, 1400});
    slots[35] = new Railroad("Ottawa Valley Railroad", make_pair(31, 101), 100, 4);
    slots[36] = new Chance("Chance3", make_pair(37, 101));
    slots[37] = new Vicinity("BANFF", make_pair(43, 101), 350, 2, "Attr2", 200, 0, {35,175,500,1100,1300,1500});
    slots[38] = new Slot("Sales Tax Fee", make_pair(49, 101));
    slots[39] = new Vicinity("ALGONQUIN", make_pair(55, 101), 400, 2, "Attr2", 200, 0, {50,200,600,1400,1700,2000});

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
    return slots[slotID]->getStatus() == Collectible::FREE;
}

bool GameBoard::isSlotOwned(const int& slotID){
    return slots[slotID]->getStatus() == Collectible::OWNED;
}

bool GameBoard::isSlotMortgaged(const int& slotID){
    return slots[slotID]->getStatus() == Collectible::MORTGAGED;
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

void GameBoard::movePlayer(int& curPlayerID, const int& diceSum){
    // move player and update locationID
    Player* curPlayer = this->players[curPlayerID];
    const int nextPosition = (curPlayer->getPosition() + diceSum) % SLOTS_NUM;
    curPlayer->setPosition(nextPosition);
}

bool GameBoard::tryBuy(const int& playerID, const int& slotID){
    Player* curPlayer = players[playerID];
	Collectible* property = dynamic_cast<Collectible*> (slots[slotID]);
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

bool GameBoard::tryPayCoopFee(int playerID){
    Player* p = players[playerID];
    cout << "You landed on Coop Fee slot and must pay $" << COOP_FEE  << " fee."<< endl;
    if(p->getBalance() < COOP_FEE){
        return false;
    }
    p->updateBalance(-1*COOP_FEE);
    cout << "You paid the fee and can continue game. " << endl;
    return true;
}


bool GameBoard::tryPayTuitionFee(int playerID){
    Player* p = players[playerID];
    cout << "You landed on Tuition slot and must pay $" << TUITION_FEE << " fee."<< endl;
    if(p->getBalance() < TUITION_FEE){
        return false;
    }
    p->updateBalance(-1*TUITION_FEE);
    cout << "You paid the fee and can continue game. " << endl;
    return true;
}

void GameBoard::collectOSAP(int playerID){
    Player* p = players[playerID];
    p->updateBalance(OSAP_FEE);
}
