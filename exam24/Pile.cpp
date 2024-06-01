#include "Pile.h"


void Pile::rotate() {

    if ( cards.empty() ) return;

    cards.push_front(current_);

    current_ = cards.back();
    cards.pop_back();
}

void Pile::delete_and_rotate() {
    if ( cards.empty() ) return;

    current_ = std::move(cards.back());
    cards.pop_back();
}



Pile::Pile(std::vector<Card> &&deck)
{

    while ( deck.size() ) {
        cards.emplace_front(deck.back());
        deck.pop_back();
    }

    current_ = cards.back();
    cards.pop_back();

    deck.clear();
}

Card const &Pile::current() const {
    return current_;
}

const std::deque<Card> &Pile::get_container() const {
    return cards;
}

bool Pile::empty() const {
    return cards.empty();
}

Pile pile;


