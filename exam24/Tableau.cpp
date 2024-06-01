#include "Tableau.h"
#include "Tasks.h"

extern void stack_set_flip(std::vector<Card> &stack);

Tableau::Tableau(const Point &anchor)
    : Entity{anchor, Card::CARD_WIDTH + 2,
             Card::CARD_HEIGHT + 2} {
                 held_stack.set_position(anchor);
             }

CardDeck &Tableau::get_held_stack() { return held_stack; }

const CardDeck &Tableau::get_held_stack() const { return held_stack; }

void Tableau::update() {
  held_stack.update_card_positions(get_position());

  if ( held_stack.size() == 0 ) set_height(Card::CARD_HEIGHT);
  else {
      set_height((held_stack.size() - 1) * (CARD_OVERLAP) + Card::CARD_HEIGHT );
      set_width(Card::CARD_WIDTH);
  }

  stack_set_flip(held_stack.get_container());
}

bool Tableau::can_push(Card card) const {
    return can_push_to_tableau(card, held_stack.get_container());
}



