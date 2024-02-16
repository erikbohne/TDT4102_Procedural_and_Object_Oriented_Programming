#include "Blackjack.h"

bool Blackjack::isAce(const Card& card) {
    return card.getRank() == Rank::ACE;
}

int Blackjack::getCardValue(const Card& card) {
    if (isAce(card)) {
        return 11;
    } else if (card.getRank() >= Rank::JACK) {
        return 10;
    } else {
        return static_cast<int>(card.getRank()) + 2;
    }
}

int Blackjack::getHandScore(const std::vector<Card>& hand) {
    int score = 0;
    int aceCount = 0;

    for (const Card& card : hand) {
        score += getCardValue(card);
        if (isAce(card)) {
            aceCount++;
        }
    }

    while (score > 21 && aceCount > 0) {
        score -= 10;
        aceCount--;
    }

    return score;
}

void Blackjack::drawPlayerCard() {
    Card card = deck.drawCard();
    playerHand.push_back(card);
    playerHandSum = getHandScore(playerHand);
}

void Blackjack::drawDealerCard() {
    Card card = deck.drawCard();
    dealerHand.push_back(card);
    dealerHandSum = getHandScore(dealerHand);
}

void Blackjack::playGame() {
    deck.shuffle();
    drawPlayerCard(); drawPlayerCard();
    drawDealerCard(); drawDealerCard();

    // Spillerens tur
    while (playerHandSum < 21 && askPlayerDrawCard()) {
        drawPlayerCard();
        cout << "Your hand sum: " << playerHandSum << endl;
    }

    // Dealerens tur
    while (dealerHandSum < 17) {
        drawDealerCard();
    }

    // Bestemmer vinneren
    if (playerHandSum > 21) {
        cout << "Dealer wins by default, player busted!" << endl;
    } else if (dealerHandSum > 21 || playerHandSum > dealerHandSum) {
        cout << "Player wins!" << endl;
    } else if (playerHandSum < dealerHandSum) {
        cout << "Dealer wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }
}

bool Blackjack::askPlayerDrawCard() {
    cout << "Your hand: " << endl;
    for (const Card& card : playerHand) {
        cout << card.toString() << endl;
    }
    cout << "Your hand sum: " << playerHandSum << endl;

    cout << "Do you want to draw a card? (y/n) ";
    char answer;
    cin >> answer;
    return answer == 'y';
}