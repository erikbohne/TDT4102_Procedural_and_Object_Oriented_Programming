#pragma once

#include <filesystem>
#include <iostream>

#include "CardDeck.h"
#include "Card.h"

struct Rectangle {
    TDT4102::Point top_left;
    int width;
    int height;
};

/// Gets the default card image path.
std::string get_card_image_path(const Card &card);

/// Determines whether a point is inside a rectangular region.
bool inside_box(TDT4102::Point point, Rectangle rectangle);

/// Determines whether `path` is a valid
bool is_valid_image_path(const std::filesystem::path &path);

void stack_set_flip(std::vector<Card> &stack);

bool can_push_to_tableau(const Card card, std::vector<Card> cards);

void update_card_stack_positions(const TDT4102::Point anchor, std::vector<Card> &container);

std::pair<std::string, std::string> process_line(const std::string &line);

void load_image_atlas(const std::filesystem::path &path);





std::string get_playing_card_insertion_output(Card &card);

std::ostream &operator<<(std::ostream &, const Card &card);



