#pragma once

#include "Entity.h"
#include "Card.h"
#include "CardDeck.h"

struct Tableau : Entity {
    Tableau() = default;
    Tableau(const Point &anchor);

    /// Returns a reference to the CardDeck instance managing
    /// the tableau's cards.
    CardDeck &get_held_stack();

    /// Returns a constant reference to the CardDeck instance managing
    /// the tableau's cards.
    const CardDeck &get_held_stack() const;

    /// Returns true if the card can be legally pushed onto the tableau.
    bool can_push(Card card) const;

    /// Called once every frame to keep requirements in order.
    virtual void update() override final;

private:
    CardDeck held_stack{};

};




