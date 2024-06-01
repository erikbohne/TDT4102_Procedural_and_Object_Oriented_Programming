#include "Foundation.h"


Foundation::Foundation(Point anchor)
    : Entity{anchor, Card::CARD_WIDTH + 2,
             Card::CARD_HEIGHT + 2} {
}

std::vector<Card> &Foundation::get_container()
{
    return cards;
}


const std::vector<Card> &Foundation::get_container() const
{
    return cards;
}

bool Foundation::can_push(Card card) const
{
    if ( cards.empty() ) {
        return card.get_rank() == CARD_A;
    } else {
        auto &topmost = cards.back();
        return topmost.get_suit() == card.get_suit()
            && card.get_rank() == topmost.get_rank() + 1;
    }
}
bool Foundation::push(Card card) {
    cards.push_back(card);
    return true;
}



