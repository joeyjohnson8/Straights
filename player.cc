#include "player.h"
#include "card.h"
#include "deck.h"
#include <vector>
using namespace std;

Player::Player(int playerNum)
    : playerNum{playerNum}, score{0}, isCPU{false}
{}

Player::Player()
    : playerNum{0}, score{0}, isCPU{false}
{}


std::vector<Card> Player::getLegalPlays(std::vector<Card> valid) const {
    std::vector<Card> plays;
    for (size_t x = 0; x < hand.size(); x++) {
        if (hand[x].getSuit() == 'S' && hand[x].getNum() == 7) {
            plays.emplace_back(7, 'S');
            return plays;
        }
    }

    for (size_t x = 0; x < hand.size(); x++) {
        if (hand[x].getNum() == 7) {
            plays.emplace_back(hand[x]);
        }
        else {
            for (size_t y = 0; y < valid.size(); y++) {
                if (hand[x].getSuit() == valid[y].getSuit()) {
                    if (hand[x].getNum() == valid[y].getNum() + 1 || hand[x].getNum() == valid[y].getNum() - 1) {
                        plays.emplace_back(hand[x]);
                    }
                }
            }
        }
    }
    return plays;
}

Card Player::getCard(int x) const {
    return hand[x];
}

void Player::setCPU(bool val) {
    isCPU = val;
}

bool Player::getCPU() const {
    return isCPU;
}

int Player::getScore() {
    return score;
}

std::vector<Card> Player::getHand() const {
    return hand;
}

void Player::discard(Card card) {
    discards.emplace_back(card);
    for (size_t x = 0; x < hand.size(); x++) {
        if (card == hand[x]) {
            hand.erase(hand.begin() + x);
            break;
        }
    }
} 
    
void Player::playCard(Card card) {
    for (size_t x = 0; x < hand.size(); x++) {
        if (card == hand[x]) {
            hand.erase(hand.begin() + x);
            break;
        }
    }
} 

int Player::getNum() const {
    return playerNum;
}

int Player::roundScore() {
    int count = 0;
    for (size_t x = 0; x < discards.size(); x++) {
        count+= discards[x].getNum();
    }
    return count;
}

void Player::setScore(int x) {
    score = x;
}

void Player::setPlayerNum(int x) {
    playerNum = x;
}

void Player::addCard(Card card) {
    hand.emplace_back(card);
}

std::vector<Card> Player::getDiscards() const {
    return discards;
}

void Player::resetDiscards() {
    discards.clear();
}

void Player::makePlay(Card choice, std::vector<Card> pile) {
    if (isCPU == true) {
        std::vector<Card> plays = getLegalPlays(pile);
        //if there is a legal play
        if (plays.size() != 0) {
            playCard(plays[0]);
        }
        //no legal plays
        else {
            discard(hand[0]);
        }
    }
    else {
        std::vector<Card> plays = getLegalPlays(pile);
        for (size_t x = 0; x < plays.size(); x++) {
            if (choice == plays[x]) {
                playCard(choice);
            }
            else {
            }
        }
    }
}
