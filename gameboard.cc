#include "gameboard.h"
#include "player.h"
#include "card.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdlib.h> 

using namespace std;

Gameboard::Gameboard(unsigned seed) {
    this->seed = seed;
    player1.setPlayerNum(1);
    player2.setPlayerNum(2);
    player3.setPlayerNum(3);
    player4.setPlayerNum(4);
}


//assists in determining which player starts the game
int Gameboard::setTurn() {
    Card temp(7, 'S');
    for (int x = 0; x < 13; x++) {
        if (player1.getHand()[x].getNum() == 7 &&  player1.getHand()[x].getSuit() == 'S') {
            return 1;
        }
        else if (player2.getHand()[x].getNum() == 7 &&  player2.getHand()[x].getSuit() == 'S') {
            return 2;
        }
        else if (player3.getHand()[x].getNum() == 7 &&  player3.getHand()[x].getSuit() == 'S') {
            return 3;
        }
        else if (player4.getHand()[x].getNum() == 7 &&  player4.getHand()[x].getSuit() == 'S') {
            return 4;
        }
    }
}

//sets each players permissions
void Gameboard::setPerms() {
    cout << "Is player1 a human (h) or a computer (c)?" << endl;
    char val;
    cin >> val;
    if (val == 'c') {
        player1.setCPU(true);
    }
    cout << "Is player2 a human (h) or a computer (c)?" << endl;
    cin >> val;
    if (val == 'c') {
        player2.setCPU(true);
    }
    cout << "Is player3 a human (h) or a computer (c)?" << endl;
    cin >> val;
    if (val == 'c') {
        player3.setCPU(true);
    }
    cout << "Is player4 a human (h) or a computer (c)?" << endl;
    cin >> val;
    if (val == 'c') {
        player4.setCPU(true);
    }
}

//print for new round
void Gameboard::startPrint(int x) const{
    cout << "A new round begins. It’s Player" << x << "’s turn to play." << endl;
}

//fills the deck at the beginning of the program, in order
void Gameboard::fillDeck() {
    char suits[] = {'C','D','H','S'};
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 13; y++) {
            Card temp(nums[y], suits[x]);
            deck.push_back(temp);
        }       
    }
}

//prints the cards played so far in the game by suit
void Gameboard::printSuits() const {
    cout << "Clubs:";
    for (int x = 0; x < 13; x++) {
        for (size_t y = 0; y < board.size(); y++) {
            Card temp(x, 'C');
            if (temp == board[y]) {
                cout << " " << board[y].getNum();
            }
        }
    }
    cout << endl;
    cout << "Diamonds:";
    for (int x = 0; x < 13; x++) {
        for (size_t y = 0; y < board.size(); y++) {
            Card temp(x, 'D');
            if (temp == board[y]) {
                cout << " " << board[y].getNum();
            }
        }
    }
    cout << endl;
    cout << "Hearts:";
    for (int x = 0; x < 13; x++) {
        for (size_t y = 0; y < board.size(); y++) {
            Card temp(x, 'H');
            if (temp == board[y]) {
                cout << " " << board[y].getNum();
            }
        }
    }
    cout << endl;
    cout << "Spades:";
    for (int x = 0; x < 13; x++) {
        for (size_t y = 0; y < board.size(); y++) {
            Card temp(x, 'S');
            if (temp == board[y]) {
                cout << " " << board[y].getNum();
            }
        }
    }
    cout << endl;
}

//assists in printing a players hand
void Gameboard::printHand(Player player) const {
    cout << "Your hand:";
    for (size_t x = 0; x < player.getHand().size(); x++) {
        cout << " " << player.getCard(x);
    }
    cout << endl;
}

//prints a players available hands
void Gameboard::printPlays(Player player) const {
    cout << "Legal plays: ";
    vector<Card> list = player.getLegalPlays(board);
    for (size_t x = 0; x < list.size(); x++) {
        cout << list[x] <<  " ";
    }
    cout << endl;

}

//fills each players hand at the start of the game
void Gameboard::fillHands() {
    for (int x = 0; x < 52; x++) {
        if (x < 13) {
            player1.addCard(deck[x]);
        }
        else if (x < 26) {
            player2.addCard(deck[x]);
        }
        else if (x < 39) {
            player3.addCard(deck[x]);
        }
        else {
            player4.addCard(deck[x]);
        }
    }
}

//prints full deck
void Gameboard::printDeck() const {
    for (size_t x = 1; x <= deck.size(); x++) {
        cout << deck[x - 1] << " ";
        if (x % 13 == 0) {
            cout << endl;
        }
    }
}

//assists in all neccesary round ending features
void Gameboard::endRound() {
    cout << "Player1's discards:";
    for (size_t x = 0; x < player1.getDiscards().size(); x++) {
        cout << " " << player1.getDiscards()[x];
    }
    cout << endl;
    int score1 = player1.roundScore();
    int newscore1 = score1 + player1.getScore();
    cout << "Player1's Score: " << player1.getScore() << " + " << score1 << " = " << newscore1 << endl;
    player1.setScore(newscore1);
    player1.resetDiscards();

    cout << "Player2's discards:";
    for (size_t x = 0; x < player2.getDiscards().size(); x++) {
        cout << " " << player2.getDiscards()[x];
    }
    cout << endl;
    int score2 = player2.roundScore();
    int newscore2 = score2 + player2.getScore();
    cout << "Player2's Score: " << player2.getScore() << " + " << score2 << " = " << newscore2 << endl;
    player2.setScore(newscore2);
    player2.resetDiscards();

    cout << "Player3's discards:";
    for (size_t x = 0; x < player3.getDiscards().size(); x++) {
        cout << " " << player3.getDiscards()[x];
    }
    cout << endl;
    int score3 = player3.roundScore();
    int newscore3 = score3 + player3.getScore();
    cout << "Player3's Score: "<< player3.getScore() << " + " << score3 << " = " << newscore3 << endl;
    player3.setScore(newscore3);
    player3.resetDiscards();

    cout << "Player4's discards:";
    for (size_t x = 0; x < player4.getDiscards().size(); x++) {
        cout << " " << player4.getDiscards()[x];
    }
    cout << endl;
    int score4 = player4.roundScore();
    int newscore4 = score4 + player4.getScore();
    cout << "Player4's Score: " << player4.getScore() << " + " << score4 << " = " << newscore4 << endl;
    player4.setScore(newscore4);
    player4.resetDiscards();
    
    board.clear();
}

//prints winner at end of game
void Gameboard::printWinner() {
    int low = player1.getScore();
    if (player2.getScore() < low) {
        low = player2.getScore();
    }
    if (player3.getScore() < low) {
        low = player3.getScore();
    }
    if (player4.getScore() < low) {
        low = player4.getScore();
    }
    if (player1.getScore() == low) {
        cout << "Player1 wins!" << endl;
    }
    if (player2.getScore() == low) {
        cout << "Player2 wins!" << endl;
    }
    if (player3.getScore() == low) {
        cout << "Player3 wins!" << endl;
    }
    if (player4.getScore() == low) {
        cout << "Player4 wins!" << endl;
    }
}

//assists in creating card from input on player's turns
Card buildCard(char num, char suit) {
    int number;
    if (num == 'A') {
        number = 1;
    }
    else if (num == 'T') {
        number = 10;
    }
    else if (num == 'J') {
        number = 11;
    }
    else if (num == 'Q') {
        number = 12;
    }
    else if (num == 'K') {
        number = 13;
    }
    else {
        number = num - '0';
    }
    Card temp(number, suit);
    return temp;
 }

//turn function for player1
void Gameboard::turn1() {
    if (player1.getCPU() == false) {
        cout << "Cards on the table:" << endl;
        printSuits();
        printHand(player1);
        printPlays(player1);
        string temp;
        getline(cin, temp);
        stringstream ss1{temp};
        string temp2;
        ss1 >> temp2;
        if (temp2 == "play") {
            char suittemp;
            char numtemp;
            ss1 >> numtemp;
            ss1 >> suittemp;
            Card tempcard = buildCard(numtemp, suittemp);
            int size1 = player1.getHand().size();
            player1.makePlay(tempcard, board);
            int size2 = player1.getHand().size();
            if (size1 == size2) {
                cout << "This is not a legal play." << endl;
                turn1();
            }
            else {
                cout << "Player" << player1.getNum() <<" plays " << tempcard.getNum() << tempcard.getSuit() << "." << endl;
                board.push_back(tempcard);
            }
        }
        else if (temp2 == "discard") {
            char suittemp;
            char numtemp;
            ss1 >> numtemp;
            ss1 >> suittemp;
            if (player1.getLegalPlays(board).size() != 0) {
                cout << "You have a legal play. You may not discard." << endl;
                turn1();
            }
            else {
                Card tempcard = buildCard(numtemp, suittemp);
                player1.discard(tempcard);
            }
        }
        else if (temp2 == "deck") {
                printDeck();
                turn1();
        }
        else if (temp2 == "quit") {
           exit(0);
        }
        else if (temp2 == "ragequit") {
            cout << "Player" << player1.getNum() <<  " ragequits. A computer will now take over." << endl;
            player1.setCPU(true);
            turn1();
        }
        else {
            turn1();
        }
    }
    else {
        std::vector<Card> plays = player1.getLegalPlays(board);
        if (plays.size() == 0) {
            Card first = player1.getCard(0);
            player1.discard(first);
            cout << "Player" << player1.getNum() <<" discards " << first << endl;
        }
        else {
            Card first = plays[0];
            player1.makePlay(first, board);
            board.emplace_back(first);
            cout << "Player" << player1.getNum() << " plays " << first << endl;
        }
    }

}

//turn function for player2
void Gameboard::turn2() {
    if (player2.getCPU() == false) {
        cout << "Cards on the table:" << endl;
        printSuits();
        printHand(player2);
        printPlays(player2);
        string temp;
        getline(cin, temp);
        stringstream ss1{temp};
        string temp2;
        ss1 >> temp2;
        if (temp2 == "play") {
            char suittemp;
            char numtemp;
            ss1 >> numtemp;
            ss1 >> suittemp;
            Card tempcard = buildCard(numtemp, suittemp);
            int size1 = player2.getHand().size();
            player2.makePlay(tempcard, board);
            int size2 = player2.getHand().size();
            if (size1 == size2) {
                cout << "This is not a legal play." << endl;
                turn2();
            }
            else {
                cout << "Player" << player2.getNum() <<" plays " << tempcard.getNum() << tempcard.getSuit() << "." << endl;
                board.push_back(tempcard);
            }
        }
        else if (temp2 == "discard") {
            char suittemp;
            char numtemp;
            ss1 >> numtemp;
            ss1 >> suittemp;
            if (player2.getLegalPlays(board).size() != 0) {
                cout << "You have a legal play. You may not discard." << endl;
                turn2();
            }
            else {
                Card tempcard = buildCard(numtemp, suittemp);
                player2.discard(tempcard);
            }
        }
        else if (temp2 == "deck") {
                printDeck();
                turn2();
        }
        else if (temp2 == "quit") {
           exit(0); 
        }
        else if (temp2 == "ragequit") {
            cout << "Player" << player2.getNum() <<  " ragequits. A computer will now take over." << endl;
            player2.setCPU(true);
            turn2();
        }
        else {
            turn2();
        }
    }
    else {
        std::vector<Card> plays = player2.getLegalPlays(board);
        if (plays.size() == 0) {
            Card first = player2.getCard(0);
            player2.discard(first);
            cout << "Player" << player2.getNum() <<" discards " << first << endl;
        }
        else {
            Card first = plays[0];
            player2.makePlay(first, board);
            cout << "Player" << player2.getNum() << " plays " << first << endl;
            board.emplace_back(first);
        }
    }

}

//turn function for player3
void Gameboard::turn3() {
    if (player3.getCPU() == false) {
        cout << "Cards on the table:" << endl;
        printSuits();
        printHand(player3);
        printPlays(player3);
        string temp;
        getline(cin, temp);
        stringstream ss1{temp};
        string temp2;
        ss1 >> temp2;
        if (temp2 == "play") {
            char suittemp;
            char numtemp;
            ss1 >> numtemp;
            ss1 >> suittemp;
            Card tempcard = buildCard(numtemp, suittemp);
            cout << tempcard.getNum() << endl;
            int size1 = player3.getHand().size();
            player3.makePlay(tempcard, board);
            int size2 = player3.getHand().size();
            if (size1 == size2) {
                cout << "This is not a legal play." << endl;
                turn3();
            }
            else {
                cout << "Player" << player3.getNum() <<" plays " << tempcard.getNum() << tempcard.getSuit() << "." << endl;
                board.push_back(tempcard);
            }
        }
        else if (temp2 == "discard") {
            char suittemp;
            char numtemp;
            ss1 >> numtemp;
            ss1 >> suittemp;
            if (player3.getLegalPlays(board).size() != 0) {
                cout << "You have a legal play. You may not discard." << endl;
                turn3();
            }
            else {
                Card tempcard = buildCard(numtemp, suittemp);
                player3.discard(tempcard);
            }
        }
        else if (temp2 == "deck") {
                printDeck();
                turn3();
        }
        else if (temp2 == "quit") {
           exit(0);
        }
        else if (temp2 == "ragequit") {
            cout << "Player" << player3.getNum() <<  " ragequits. A computer will now take over." << endl;
            player3.setCPU(true);
            turn3();
        }
        else {
            turn3();
        }
    }
    else {
        std::vector<Card> plays = player3.getLegalPlays(board);
        if (plays.size() == 0) {
            Card first = player3.getCard(0);
            player3.discard(first);
            cout << "Player" << player3.getNum() << " discards " << first << endl;
        }
        else {
            Card first = plays[0];
            player3.makePlay(first, board);
            cout << "Player" << player3.getNum() << " plays " << first << endl;
            board.emplace_back(first);
        }
    }

}

//turn function for player4
void Gameboard::turn4() {
    if (player4.getCPU() == false) {
        cout << "Cards on the table:" << endl;
        printSuits();
        printHand(player4);
        printPlays(player4);
        string temp;
        getline(cin, temp);
        stringstream ss1{temp};
        string temp2;
        ss1 >> temp2;
        if (temp2 == "play") {
            char suittemp;
            char numtemp;
            ss1 >> numtemp;
            ss1 >> suittemp;
            Card tempcard = buildCard(numtemp, suittemp);
            int size1 = player4.getHand().size();
            player4.makePlay(tempcard, board);
            int size2 = player4.getHand().size();
            if (size1 == size2) {
                cout << "This is not a legal play." << endl;
                turn4();
            }
            else {
                cout << "Player" << player4.getNum() <<" plays " << tempcard.getNum() << tempcard.getSuit() << "." << endl;
                board.push_back(tempcard);
            }
        }
        else if (temp2 == "discard") {
            char suittemp;
            char numtemp;
            ss1 >> numtemp;
            ss1 >> suittemp;
            if (player4.getLegalPlays(board).size() != 0) {
                cout << "You have a legal play. You may not discard." << endl;
                turn4();
            }
            else {
                Card tempcard = buildCard(numtemp, suittemp);
                player4.discard(tempcard);
            }
        }
        else if (temp2 == "deck") {
                printDeck();
                turn4();
        }
        else if (temp2 == "quit") {
           exit(0);
        }
        else if (temp2 == "ragequit") {
            cout << "Player" << player4.getNum() <<  " ragequits. A computer will now take over." << endl;
            player4.setCPU(true);
            turn4();
        }
        else {
            turn4();
        }
    }
    else {
        std::vector<Card> plays = player4.getLegalPlays(board);
        if (plays.size() == 0) {
            Card first = player4.getCard(0);
            player4.discard(first);
            cout << "Player" << player4.getNum() <<" discards " << first << endl;
        }
        else {
            Card first = plays[0];
            player4.makePlay(first, board);
            cout << "Player" << player4.getNum() << " plays " << first << endl;
            board.emplace_back(first);
        }
    }

}

//shuffles the deck with the seed field
void Gameboard::shuffle(){
    std::default_random_engine rng{seed};
    std::shuffle( deck.begin(), deck.end(), rng );
}

//runs the gameplay
void Gameboard::play() {
    fillDeck();
    shuffle();
    setPerms();
    string clear;
    getline(cin, clear);
    while (player1.getScore() < 80 && player2.getScore() < 80 && player3.getScore() < 80 && player4.getScore() < 80) {
        fillHands();
        int firstplayer = setTurn();
        startPrint(firstplayer);
        int counter = 52 + firstplayer;
        for (int x = firstplayer; x < counter; x++) {
            if (x % 4 == 1) {
                turn1();
            }
            else if (x % 4 == 2) {
                turn2();
            }
            else if (x % 4 == 3) {
                turn3();
            }
            else {
                turn4();
            }
        }
    endRound();
    shuffle();
    }
    printWinner();
}
