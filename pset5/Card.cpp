#include "Card.h"

string suitToString(Suit suit) {
    switch (suit) {
        case Suit::CLUBS: return "Clubs";
        case Suit::DIAMONDS: return "Diamonds";
        case Suit::HEARTS: return "Hearts";
        case Suit::SPADES: return "Spades";
        default: return "Unknown Suit";
    }
}

string rankToString(Rank rank) {
    switch (rank) {
        case Rank::TWO: return "Two";
        case Rank::THREE: return "Three";
        case Rank::FOUR: return "Four";
        case Rank::FIVE: return "Five";
        case Rank::SIX: return "Six";
        case Rank::SEVEN: return "Seven";
        case Rank::EIGHT: return "Eight";
        case Rank::NINE: return "Nine";
        case Rank::TEN: return "Ten";
        case Rank::JACK: return "Jack";
        case Rank::QUEEN: return "Queen";
        case Rank::KING: return "King";
        case Rank::ACE: return "Ace";
        default: return "Unknown Rank";
    }
}

CardDeck::CardDeck() {
    for (int suit = static_cast<int>(Suit::CLUBS); suit <= static_cast<int>(Suit::SPADES); ++suit) {
        for (int rank = static_cast<int>(Rank::TWO); rank <= static_cast<int>(Rank::ACE); ++rank) {
            cards.emplace_back(static_cast<Suit>(suit), static_cast<Rank>(rank));
        }
    }
}

void CardDeck::swap(int index1, int index2) {
    std::swap(cards[index1], cards[index2]);
}

void CardDeck::print() const {
    for (const auto& card : cards) {
        cout << card.toString() << endl;
    }
}

void CardDeck::shuffle() {
    auto rng = std::default_random_engine {};
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card CardDeck::drawCard() {
    if (cards.empty()) {
        throw std::out_of_range("Cannot draw from an empty deck.");
    }

    Card drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}