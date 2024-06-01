#pragma once

#include "Entity.h"
#include "Card.h"

struct CardDeck : Entity {

    CardDeck() = default;
    CardDeck(std::vector<Card> &stk);

    /// Returns true if the card can be legally pushed onto the stack.
    bool can_push(const Card card);

    /// Returns true if the underlying storage container is empty.
    bool empty() const;

    /// Returns the number of elements in the underlying storage container.
    std::size_t size() const {
        return stack.size();
    }

    /// Returns a reference to the last element in the underlying storage container.
    Card &back();

    /// Conditionally pushes a card onto the stack. See `can_push`
    void push(Card card);

    /// Unconditionally pushes a card onto the stack.
    void push_unchecked(Card card);

    /// Returns a vector of upto `n` cards that are simultaneously removed
    /// from this instance.
    std::vector<Card> pop_top_n(int n);

    virtual void update() override;

    void update_card_positions(const Point anchor);

    /// Get the underlying container.
    std::vector<Card> &get_container();

    /// Get the underlying container.
    const std::vector<Card> &get_container() const;

private:

    std::vector<Card> stack{};

    void update_bounds();
};



