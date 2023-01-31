#ifndef _PLAYER_
#define _PLAYER_
#include <vector>
#include "card.h"
#include "deck.h"

class Player {
    protected:
    int playerNum;
    int score;
    bool isCPU;
    std::vector<Card> hand; 
    std::vector<Card> discards; 
    public:
    Player ( int playerNum );
    Player();
    void makePlay(Card, std::vector<Card>);
    void playCard(Card);
    std::vector<Card> getLegalPlays(std::vector<Card>) const;
    void discard(Card);
    int roundScore();
    void addCard(Card);
    Card getCard(int) const;
    int getNum() const;
    void setCPU(bool);
    bool getCPU() const;
    void setPlayerNum(int);
    int getScore();
    void setScore(int);
    void resetDiscards();
    std::vector<Card> getDiscards() const;
    std::vector<Card> getHand() const;
};

#endif
