#pragma once

#include "Entity.h"
#include "Card.h"

struct Foundation : Entity {


    Foundation(Point anchor);

    void rotate();

    bool can_push(Card card) const;

    bool push(Card card);

    std::vector<Card> &get_container();
    const std::vector<Card> &get_container() const;

  private:
    std::vector<Card> cards;
};



