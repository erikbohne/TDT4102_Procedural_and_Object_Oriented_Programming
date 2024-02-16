#pragma once
#include "std_lib_facilities.h"

enum class Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
};

enum class Rank {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
};

string suitToString(Suit suit);
string rankToString(Rank rank);