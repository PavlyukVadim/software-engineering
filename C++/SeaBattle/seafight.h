#ifndef SEAFIGHT_H
#define SEAFIGHT_H


class seaFight
{
    static int mSize;
    static int* shipsType;

    struct Deck{
        int x;
        int y;
        bool killed = false;
    };

    struct NeighboringDeck{
        int x;
        int y;
    };

    struct ShipInfo{
        int count_deck = 0;
        int count_n_deck = 0; // neighboring Decks
        int hit = 0;

        char type;
        Deck decks[4];
        NeighboringDeck n_decks[14];
    };

    struct LastSuccessHit{
        int x = -1;
        int y = -1;
    };

    public:
        seaFight();
        int index1 = 0; // order to create ships
        int index2 = 0;

        bool winning = false;
        int winner = 0;
        ShipInfo shipInfo1[10];
        ShipInfo shipInfo2[10];

        LastSuccessHit lastSuccessHit1;
        LastSuccessHit lastSuccessHit2;
        int wShooting = 1; // determines who should shoot

    void outputA();
    void createShips(int, int*);
    void orderVertical(int **_map, int *index_ship, seaFight::ShipInfo shipInfo[]);
    void orderHorizontal(int **_map, int *index_ship, seaFight::ShipInfo shipInfo[]);
    void orderDiagonal(int **_map, int *index_ship, seaFight::ShipInfo shipInfo[]);
    bool shooting(seaFight::LastSuccessHit &lastSuccessHit, int **_map);
    bool testWinning(int **_map);
    void checkKilling(int **_map, int i, int j);
    void writeStruct(seaFight::ShipInfo shipInfo[], bool decks, int index, int x, int y);
    void play();

    private: int **map1;
    private: int **map2;
};
#endif // SEAFIGHT_H
