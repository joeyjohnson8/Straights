#ifndef _CARD_
#define _CARD_
#include <vector>
#include <iostream>

struct Card {
	int num;
    char suit;
    Card( int num, char suit );
    public:
    bool operator==(const Card &);
    char getSuit() const;
    int getNum() const;
    friend std::ostream& operator<<(std::ostream& output, const Card& card);
};
#endif
