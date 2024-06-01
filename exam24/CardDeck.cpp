#include "CardDeck.h"

extern bool can_push_to_tableau(const Card card, std::vector<Card> cards);

extern void update_card_stack_positions(const TDT4102::Point anchor, std::vector<Card> &container) ;

CardDeck::CardDeck(std::vector<Card> &stk) : stack{stk} {}

bool CardDeck::can_push(const Card card) {
    return can_push_to_tableau(card, stack);

}

bool CardDeck::empty() const {
    return stack.empty();
}

Card &CardDeck::back() {
    return stack.back();
}

void CardDeck::push(Card card) {
    if ( can_push(card) ) {
        push_unchecked(card);
    }
}

void CardDeck::push_unchecked(Card card) {
    stack.push_back(card);
}

std::vector<Card> CardDeck::pop_top_n(int n) {

    if ( n < 1 ) return {};
    // Conditionally handle empty stack

    if ( n > stack.size() ) n = stack.size();


    std::vector<Card> result{};

    for ( int i = 0; i < n; i++ )
    {
        result.emplace_back(stack.back());
        stack.pop_back();
    }

    return result;
}

void CardDeck::update()  {

    update_card_positions(get_position());

    // Potential assignment.
    if ( ! stack.empty() && stack.back().is_flipped() ) {
        stack.back().flip();
    }
}

void CardDeck::update_card_positions(const TDT4102::Point anchor) {
    update_card_stack_positions(anchor, stack);
}

std::vector<Card> &
CardDeck::get_container() {
    return stack;
}

const std::vector<Card> &
CardDeck::get_container() const {
    return stack;
}


void CardDeck::update_bounds() {
    // Base Height
    set_width(100);
}


