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