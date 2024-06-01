#pragma once

#include "Foundation.h"
#include "ImageAtlas.h"
#include "Pile.h"
#include "Tasks.h"
#include "common.h"
#include "CardDeck.h"
#include <AnimationWindow.h>
#include <algorithm>



class CardRenderer {

public:

    static void render(TDT4102::AnimationWindow &renderer, const Card &card, TDT4102::Point anchor) {
        draw_image(renderer, card, {anchor.x, anchor.y});
    }

    static void draw_joker(TDT4102::AnimationWindow &renderer, TDT4102::Point anchor, CardColor color) {
        static std::shared_ptr<TDT4102::Image> red_joker;
        static std::shared_ptr<TDT4102::Image> black_joker;
        if ( ! red_joker ) {
            red_joker = std::make_shared<TDT4102::Image>("./images/JkrRed.png");
        }
        if ( ! black_joker ) {
            black_joker = std::make_shared<TDT4102::Image>("./images/JkrBlk.png");
        }

        if ( color == CardColor::RED ) {
            renderer.draw_image(anchor, *red_joker);
        } else {
            renderer.draw_image(anchor, *black_joker);
        }
    }

    static void draw_back(TDT4102::AnimationWindow &renderer, TDT4102::Point anchor)
    {

        static std::shared_ptr<TDT4102::Image> back;
        if ( ! back ) {
            back = std::make_shared<TDT4102::Image>("./images/backR.png");
        }

        renderer.draw_image(anchor, *back, Card::CARD_WIDTH, Card::CARD_HEIGHT);
    }

    static void draw_card_text(TDT4102::AnimationWindow &renderer, const Card &card, TDT4102::Point anchor )
    {
        TDT4102::Point text_anchor = {anchor.x, anchor.y - 5};

        renderer.draw_text(text_anchor, std::to_string(card.get_rank()), TDT4102::Color::black, 16);
    }

    static void draw_image(TDT4102::AnimationWindow &renderer, const Card &card, TDT4102::Point anchor ) {

        if ( card.is_flipped() ) {
            draw_back(renderer, anchor);
            return;
        }

        std::string card_image_filename = get_card_image_path(card);

        if ( ! is_valid_image_path(card_image_filename) ) {
            draw_joker(renderer, anchor, card.get_color());
            draw_card_text(renderer, card, anchor);
            return;
        }


        std::string card_identifier = card.get_identifier();

        // Select based on implemented get_identifier
        std::string &key = card_identifier.empty() || card.is_flipped() ? card_image_filename : card_identifier;

        auto img_ptr = ImageAtlas::get_image(key);

        if ( ! img_ptr ) {
            // Invalid image, render the joker
            draw_joker(renderer, anchor, card.get_color());
            draw_card_text(renderer, card, anchor);
        } else {
            renderer.draw_image({anchor.x, anchor.y}, *img_ptr, Card::CARD_WIDTH, Card::CARD_HEIGHT);
        }

    }

};

class CardDeckRenderer {
    public:
    static void render(TDT4102::AnimationWindow &renderer, const CardDeck &stk) {

        auto &stack = stk.get_container();

        std::for_each(std::begin(stack), std::end(stack), [&renderer] (auto &card) {
            CardRenderer::render(renderer, card, card.get_position());
        });
    }
};

class PileRenderer {
public:
    static void render(TDT4102::AnimationWindow &renderer, const Pile &pile) {

        if ( pile.empty() ) return;

        auto &cur = pile.current();

        CardRenderer::render(renderer, cur, pile.get_position());
    }

};

class FoundationRenderer {
public:
    static void render(TDT4102::AnimationWindow &renderer, const Foundation &foundation) {

        auto stack = foundation.get_container();

        if ( stack.empty() ) return;

        CardRenderer::render(renderer, stack.back(), foundation.get_position());

    }

};



