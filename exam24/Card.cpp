#include "Card.h"
#include "common.h"


// TASK: T1
bool Card::is_flipped() const  {
// BEGIN: T1
// Write your answer to assignment T1 here, between the //BEGIN: T1
// and // END: T1 comments. You should remove any code that is
// already there and replace it with your own.
    return flipped;
// END: T1
}


// TASK: T2
CardColor Card::get_color() const {
// BEGIN: T2
// Write your answer to assignment T2 here, between the //BEGIN: T2
// and // END: T2 comments. You should remove any code that is
// already there and replace it with your own.
    return (suit == Suit::CLUBS || suit == Suit::SPADES) ? CardColor::BLACK : CardColor::RED;
// END: T2
}



// TASK: T5
std::string Card::get_identifier() const {
// BEGIN: T5
    
    // Starter med å legge til tallverdien
    std::string identifier = std::to_string(rank + 1);

    // Vi må så finne passende streng til sort
    std::string type;
    if (suit == Suit::CLUBS) {
        type = "C";
    } else if (suit == Suit::SPADES) {
        type = "S";
    } else if (suit == Suit::HEARTS) {
        type = "H";
    } else if (suit == Suit::DIAMONDS) {
        type = "D";
    } else {
        throw std::runtime_error("Suit not found while creating identifier");
    }

    // Vi legger til strengverdien til sorten og returnerer
    return identifier + type;
// END: T5
}



// ========================================
// Do not touch anything below this point
// ========================================

Card::Card(int rank, Suit suit_) : rank{rank}, suit{suit_} {
    set_width(CARD_WIDTH);
    set_height(CARD_HEIGHT);
};


Card::Card(int rank, Suit suit_, Point pos) : Card(rank, suit_) {
    set_width(CARD_WIDTH);
    set_height(CARD_HEIGHT);
    set_position(pos);
};


int Card::get_rank() const {
    return rank;
}

Suit Card::get_suit() const {
    return suit;
}

void Card::set_flipped(bool flipped_)  {
    flipped = flipped_;
}

void Card::flip() {
    flipped = ! flipped;
}

int Card::CARD_WIDTH = 60;
int Card::CARD_HEIGHT = 89;



