#include "seafight.h"
#include <iostream>
#include <stdlib.h> // rand()
#include <ctime>

using namespace std;

int seaFight::mSize = 10;

static int ships[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
int* seaFight::shipsType = ships;

void seaFight::play(){
    if(this->wShooting == 1) {
        //cout << "The first player is shooting!" << endl;
        //cout << "2 ";
        if(this->shooting(this->lastSuccessHit1 , this->map2)) {
            this->winner = 1;
        }
        this->wShooting = 2;
    }
    else {
        //cout << "The second player is shooting!" << endl;
        //cout << "1 ";
        if(this->shooting(this->lastSuccessHit2 , this->map1)) {
            this->winner = 2;
        }
        this->wShooting = 1;
    }
}

seaFight::seaFight()
{
    this->map1 = new int *[this->mSize];
    for (int i = 0; i < this->mSize; i++) {
        this->map1[i] = new int [this->mSize];
    }

    for (int i = 0; i < this->mSize; i++) {
        for (int j = 0; j < this->mSize; j++) {
            map1[i][j] = 0;
        }
    }

    this->map2 = new int *[this->mSize];
    for (int i = 0; i < this->mSize; i++) {
        this->map2[i] = new int [this->mSize];
    }

    for (int i = 0; i < this->mSize; i++) {
        for (int j = 0; j < this->mSize; j++) {
            map2[i][j] = 0;
        }
    }
}

void seaFight::outputA()
{
     cout << " A1 :" << endl << endl;
     for (int i = 0; i < this->mSize; i++) {
        for (int j = 0; j < this->mSize; j++) {
            cout << this->map1[i][j] << "  ";
        }
        cout << endl << endl;
    }

    cout << " __________________________ " << endl << endl;

    cout << " A2 :" << endl << endl;
    for (int i = 0; i < this->mSize; i++) {
        for (int j = 0; j < this->mSize; j++) {
            cout << this->map2[i][j] << "  ";
        }
        cout << endl << endl;
    }
}

void seaFight::createShips(int n, int *index_ship)
{
    if (n == 1) {
        int order = rand() % 3 + 1;  //3 + 1; // define order ship : 1 - vert, 2 - horiz, 3 - diagon.
        switch (order) {
            case 1 : {this->orderVertical(this->map1, index_ship, this->shipInfo1);  break;}
            case 2 : {this->orderHorizontal(this->map1, index_ship, this->shipInfo1);  break;}
            case 3 : {this->orderDiagonal(this->map1, index_ship, this->shipInfo1);  break;}
        }
    }
    else if (n == 2) {
        int order = rand() % 3 + 1;  //3 + 1; // define order ship : 1 - vert, 2 - horiz, 3 - diagon.
        switch (order) {
            case 1 : {this->orderVertical(this->map2, index_ship, this->shipInfo2);  break;}
            case 2 : {this->orderHorizontal(this->map2, index_ship, this->shipInfo2);  break;}
            case 3 : {this->orderDiagonal(this->map2, index_ship, this->shipInfo2);  break;}
        }
    }
}

void seaFight::orderVertical(int **_map, int *index_ship, seaFight::ShipInfo shipInfo[]) {
    int count_decks = this->shipsType[*index_ship];
    int i, j; // indexes of lower left coordinate ship
    i = rand() % 10;
    j = rand() % 10;

    if (i - count_decks < -1) {
        //cout << "Going beyond the map" << endl;
        return;
    }

    for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
        if (_map[i - sh][j] != 0) {
            //cout << "There is a ship" << endl;
            return;
        }
    }
    // test - one cell between ships
    if (j != 0) {
        for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
            if (_map[i - sh][j - 1] != 0) {
                //cout << "There is a limit with ship" << endl;
                return;
            }
        }
    }

    if (j != 9) {
        for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
            if (_map[i - sh][j + 1] != 0) {
                //cout << "There is a limit with ship" << endl;
                return;
            }
        }
    }

    if (i - count_decks > -1) {
        if (_map[i - count_decks][j] != 0) {
            //cout << "There is a limit with ship" << endl;
            return;
        }
    }

    if (i != 9) {
        if (_map[i + 1][j] != 0) {
            //cout << "There is a limit with ship" << endl;
            return;
        }
    }

    shipInfo[*index_ship].type = 'v';

    for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
        _map[i - sh][j] = 1;
        _map[i - sh][j - 1] = 8;
        _map[i - sh][j + 1] = 8;

        this->writeStruct(shipInfo, true, *index_ship, j, i - sh);
    }

    if (i != 9) {
        _map[i + 1][j] = 8;
        this->writeStruct(shipInfo, false, *index_ship, j, i + 1);
    }
    if (i - count_decks > -1) {
        _map[i - count_decks][j] = 8;
        this->writeStruct(shipInfo, false, *index_ship, j, i - count_decks);
    }

    *index_ship += 1;
}

void seaFight::orderHorizontal(int **_map, int *index_ship, seaFight::ShipInfo shipInfo[]) {
    int count_decks = this->shipsType[*index_ship];
    int i, j; // indexes of lower left coordinate ship
    i = rand() % 10;
    j = rand() % 10;

    if (j + count_decks > 10) {
        //cout << "Going beyond the map" << endl;
        return;
    }

    for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
        if (_map[i][j + sh] != 0) {
            //cout << "There is a ship" << endl;
            return;
        }
    }

    // test - one cell between ships
    if (i != 0) {
        for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
            if (_map[i - 1][j + sh] != 0) {
                //cout << "There is a limit with ship" << endl;
                return;
            }
        }
    }

    if (i != 9) {
        for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
            if (_map[i + 1][j + sh] != 0) {
                //cout << "There is a limit with ship" << endl;
                return;
            }
        }
    }

    if (j + count_decks <= 10) {
        if (_map[i][j + count_decks] != 0) {
            //cout << "There is a limit with ship" << endl;
            return;
        }
    }

    if (j != 0) {
        if (_map[i][j + 1] != 0) {
            //cout << "There is a limit with ship" << endl;
            return;
        }
    }

    shipInfo[*index_ship].type = 'h';

    for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
        _map[i][j + sh] = 1;
        this->writeStruct(shipInfo, true, *index_ship, j + sh, i);
        if (i > 0) {
            _map[i - 1][j + sh] = 8;
            this->writeStruct(shipInfo, false, *index_ship, j + sh, i - 1);
        }
        if (i < 9) {
            _map[i + 1][j + sh] = 8;
            this->writeStruct(shipInfo, false, *index_ship, j + sh, i + 1);
        }
    }

    if (j != 0) {
        _map[i][j - 1] = 8;
        this->writeStruct(shipInfo, false, *index_ship, j - 1, i);
    }
    if (j + count_decks <= 10) {
        _map[i][j + count_decks] = 8;
        this->writeStruct(shipInfo, false, *index_ship, j + count_decks, i);
    }

    *index_ship += 1;
}

void seaFight::orderDiagonal(int **_map, int *index_ship, seaFight::ShipInfo shipInfo[]) {
    int count_decks = this->shipsType[*index_ship];
    int i, j; // indexes of lower left coordinate ship
    i = rand() % 10;
    j = rand() % 10;

    if (i - count_decks < -1 || j + count_decks > 10) {
        //cout << "Going beyond the map" << endl;
        return;
    }

    for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
        if (_map[i - sh][j + sh] != 0) {
            //cout << "There is a ship" << endl;
            return;
        }
    }

    // test - one cell between ships
    if (j != 0) {
        for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
            if (_map[i - sh][j + sh - 1] != 0) {
                //cout << "There is a limit with ship" << endl;
                return;
            }
        }
    }

    if (j + count_decks != 9) {
        for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
            if (_map[i - sh][j + sh + 1] != 0) {
                //cout << "There is a limit with ship" << endl;
                return;
            }
        }
    }

    if (i - count_decks > -1) {
        if (_map[i - count_decks][j + count_decks] != 0) {
            //cout << "There is a limit with ship" << endl;
            return;
        }
    }

    if (i != 9) {
        if (_map[i + 1][j] != 0) {
            //cout << "There is a limit with ship" << endl;
            return;
        }
    }

    shipInfo[*index_ship].type = 'd';

    for (int sh = 0; sh < count_decks; sh++) { //sh - shift relatively j
        _map[i - sh][j + sh] = 1;

        this->writeStruct(shipInfo, true, *index_ship, j + sh, i - sh);

        _map[i - sh][j + sh - 1] = 8;
        _map[i - sh][j + sh + 1] = 8;

        this->writeStruct(shipInfo, false, *index_ship, j + sh - 1, i - sh);
        this->writeStruct(shipInfo, false, *index_ship, j + sh + 1, i - sh);
    }

    if (i != 9) {
        _map[i + 1][j] = 8;
        this->writeStruct(shipInfo, false, *index_ship, j, i + 1);
    }
    if (i - count_decks > -1) {
        _map[i - count_decks][j + count_decks] = 8;
        this->writeStruct(shipInfo, false, *index_ship, j + count_decks, i - count_decks);
    }

    *index_ship += 1;
}

void seaFight::writeStruct(seaFight::ShipInfo shipInfo[], bool decks, int index, int x, int y){
    int n_deck;
    if (decks) {
        n_deck = shipInfo[index].count_deck;
        shipInfo[index].decks[n_deck].x = x;
        shipInfo[index].decks[n_deck].y = y;
        shipInfo[index].count_deck++;
    }
    else {
        n_deck = shipInfo[index].count_n_deck;
        shipInfo[index].n_decks[n_deck].x = x;
        shipInfo[index].n_decks[n_deck].y = y;
        shipInfo[index].count_n_deck++;
    }
}



bool seaFight::shooting(seaFight::LastSuccessHit &lastSuccessHit, int **_map){
    int i, j;
    do {
        if (lastSuccessHit.x > 0 && lastSuccessHit.y > 0) {
            int sh_x = rand() % 3 - 1;
            int sh_y = rand() % 3 - 1;
            i = lastSuccessHit.y + sh_y;
            j = lastSuccessHit.x + sh_x;
            //cout << "||" << i << " " << j << endl;
            if (i >= 0 && i <= 9 && j >= 0 && j <= 9) {
                if (_map[i][j] != 2 && _map[i][j] != 3) {
                    break;
                }
            }
            lastSuccessHit.x = -1;
            lastSuccessHit.y = -1;
        }
        else {
            i = rand() % 10;
            j = rand() % 10;
            if (_map[i][j] != 2 && _map[i][j] != 3) {
                break;
            }
        }
    }
    while (1);

    if (_map[i][j] == 1) {
        _map[i][j] = 3; // means simply hit the target
        lastSuccessHit.x = j;
        lastSuccessHit.y = i;
        checkKilling(_map, i, j);
        if (this->wShooting == 1) {
            this->wShooting = 2;
        }
        else {
            this->wShooting = 1;
        }
    }
    else {
        _map[i][j] = 2; // means simply hit
        lastSuccessHit.x = -1;
        lastSuccessHit.y = -1;
    }

    if(this->testWinning(_map)) {
        return true;
    }
    return false;
}

void seaFight::checkKilling(int **_map, int y, int x){

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < this->shipInfo1[i].count_deck; j++) {
            if (this->shipInfo1[i].decks[j].x == x && this->shipInfo1[i].decks[j].y == y) {
                this->shipInfo1[i].hit++;

                if (this->shipInfo1[i].hit == this->shipInfo1[i].count_deck ) {
                    for (int o = 0; o < this->shipInfo1[i].count_n_deck; o++) {
                        _map[this->shipInfo1[i].n_decks[o].y][this->shipInfo1[i].n_decks[o].x] = 2;
                    }
                }
                break;
            }
        }
    }
};

bool seaFight::testWinning(int **_map) {
    int counter = 0;
    for (int i = 0; i < this->mSize; i++) {
        for (int j = 0; j < this->mSize; j++) {
            if (_map[i][j] == 3) {
                counter++;
            }
        }
    }
    //cout << " " << counter << endl;
    if (counter == 20) {
        this->winning = true;
        return true;
    }
    return false;
}
