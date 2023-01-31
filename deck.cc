#include "deck.h"

Deck::Deck () {
    char suits[] = {'C','D','H','S'};
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    for (int j=0; j<13; j++) {
        for (int i=0; i<4; i++) {
            Card temp(nums[j], suits[i]);
            deck.push_back(temp);
        }       
    }
}

void Deck::shuffle() {

}

