#include "card.h"

Card::Card(int num, char suit)
    : num{num}, suit{suit}
{}
bool Card::operator==(const Card &other) {
    if ((suit == other.suit) && (num == other.num)) {
        return true;
    }
    else {
        return false;
    }
}

char Card::getSuit() const {
    return suit;
}

int Card::getNum() const {
    return num;
}

std::ostream& operator<<(std::ostream& output, const Card& card) {
    if (card.num >= 10){
        if (card.num == 10) {
            output << 'T';
        } 
        if (card.num == 11) {
            output << 'J';
        }
        if (card.num == 12) {
            output << 'Q';
        }
        if (card.num == 13) {
            output << 'K';
        }
    } else if (card.num == 1) {
        output << 'A';
    } 
    else {
        output << card.num;
    }
    output << card.suit;
    return output;
}

