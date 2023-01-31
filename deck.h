#ifndef _DECK_
#define _DECK_
#include "card.h"
#include <vector>
class Deck {
    protected:
    std::vector<Card> deck;
    public:
    Deck ();
    void shuffle();
};
#endif
