#pragma once

#include "std_lib_facilities.h"
#include "Card.h"

class Blackjack {
private:
    CardDeck deck;
    vector<Card> playerHand;
    vector<Card> dealerHand;
    int playerHandSum = 0;
    int dealerHandSum = 0;

    bool isAce(const Card& card);
    int getCardValue(const Card& card);
    int getHandScore(const vector<Card>& hand);
    bool askPlayerDrawCard();
    void drawPlayerCard();
    void drawDealerCard();

public:
    void playGame();
};