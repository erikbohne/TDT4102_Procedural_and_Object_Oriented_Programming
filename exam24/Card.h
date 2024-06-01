#pragma once
#include "Entity.h"



constexpr int CARD_A = 0;
constexpr int CARD_2  = 1;
constexpr int CARD_3  = 2;
constexpr int CARD_4  = 3;
constexpr int CARD_5  = 4;
constexpr int CARD_6  = 5;
constexpr int CARD_7  = 6;
constexpr int CARD_8  = 7;
constexpr int CARD_9  = 8;
constexpr int CARD_10 = 9;
constexpr int CARD_J  = 10;
constexpr int CARD_Q  = 11;
constexpr int CARD_K  = 12;

enum class CardColor {
    BLACK,
    RED
};

enum class Suit {
    SPADES,
    CLUBS,
    HEARTS,
    DIAMONDS
};

struct Card : public Entity {

    static int CARD_WIDTH;
    static int CARD_HEIGHT;

    Card() = default;

    /// Construct a regular playing card
    explicit Card(int rank, Suit type);

    /// Construct a playing card with a position.
    explicit Card(int rank, Suit type, Point pos);

    /// Get the current value of the Card.
    /// See `CARD_A` through `CARD_K`
    int get_rank() const;

    /// Get the suit enum of the current card.
    Suit get_suit() const;

    /// Returns true if the card is flipped
    bool is_flipped() const;

    /// Explicitly sets the flipped state of the card.
    void set_flipped(bool flipped_);

    /// Toggles the flip state of the card.
    void flip();

    /// Gets the color of the Card.
    /// CardColor::BLACK when clubs or spades.
    /// CardColor::RED when hearts or diamonds.
    CardColor get_color() const;

    // Get the cartd's identifier
    std::string get_identifier() const;

private:
    int rank{CARD_A};
    Suit suit{Suit::CLUBS};
    bool flipped = false;
};



