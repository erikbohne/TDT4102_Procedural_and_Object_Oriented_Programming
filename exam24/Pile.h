#pragma once

#include "Entity.h"
#include "Card.h"
#include "widgets/Button.h"
#include <deque>

struct Pile : Entity {

    Pile() = default;

    Pile(std::vector<Card> &&deck);

    void rotate();

    void delete_and_rotate();

    const std::deque<Card> &get_container() const;

    bool empty() const;

    Card const &current() const;

  private:
    std::deque<Card> cards;
    Card current_;
};

struct PileButton : TDT4102::Button {
    explicit PileButton(TDT4102::Point location, unsigned int width, unsigned int height, std::string label) :
         Button{location, width, height, label} {}
};

extern Pile pile;



