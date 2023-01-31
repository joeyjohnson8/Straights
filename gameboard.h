#ifndef _GAMEBOARD_
#define _GAMEBOARD_
#include "player.h"
#include "card.h"
#include "deck.h"
#include <vector>

class Gameboard {
    private:
    std::vector<Card> board;
    std::vector<Card> deck;
    Player player1;
    Player player2;
    Player player3;
    Player player4;
    unsigned seed;
    void startPrint(int) const;
    void turn1();
    void turn2();
    void turn3();
    void turn4();
    void printSuits() const;
    void printHand(Player) const; 
    void printPlays(Player) const;
    void fillHands();
    void fillDeck();
    void printDeck() const;
    void Gameplay();
    void shuffle();
    void printWinner();
    void endRound();
    int setTurn();
    void setPerms();
    void turn(Player);
    public:
    Gameboard (unsigned);
    void play();
};
#endif
