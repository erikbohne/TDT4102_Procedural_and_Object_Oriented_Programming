#pragma once
#include "std_lib_facilities.h"


// Task 1
enum class Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
};

enum class Rank {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
};

string suitToString(Suit suit);
string rankToString(Rank rank);


// Task 2
class Card {
private:
    Suit s;
    Rank r;

public:
    Card(Suit suit, Rank rank) : s{suit}, r{rank} {}

    Suit getSuit() const {
        return s;
    }

    Rank getRank() const {
        return r;
    }

  string toString() const {
        string suitStr = suitToString(s);
        string rankStr = rankToString(r);
        return rankStr + " of " + suitStr;
    }
};


// Task 3
class CardDeck {
private:
    std::vector<Card> cards;

    void swap(int index1, int index2);

public:
    CardDeck();

    void print() const;
    void shuffle();
    Card drawCard();
};