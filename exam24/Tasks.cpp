#include "Tasks.h"
#include "CardDeck.h"
#include "Entity.h"
#include "ImageAtlas.h"
#include "Pile.h"
#include "utils.h"
#include <filesystem>

#include <fstream>


// TASK: T3
bool inside_box(TDT4102::Point point, Rectangle rectangle) {
// BEGIN: T3
// Write your answer to assignment T3 here, between the //BEGIN: T3
// and // END: T3 comments. You should remove any code that is
// already there and replace it with your own.
    auto [x, y] = point;
    auto [x_r, y_r] = rectangle.top_left;

    // Sjekker om punktene er utenfor områdene og isåfall return false
    if (x > x_r + rectangle.width || x < x_r) {
        return false;
    } else if (y > y_r + rectangle.height || y < y_r) {
        return false;
    }

    // Har bestått begge testene og må ligge i området
    return true;
// END: T3
}

// TASK: T4
void stack_set_flip(std::vector<Card> &stack) {
// BEGIN: T4

    // Vi sjekker først om vectoren har innhold
    if (stack.empty()) {
        return;
    }

    // Vi skal bare flippe siste kortet i vektoren
    stack.at(stack.size() - 1).set_flipped(false);
    
// END: T4
}

// TASK: T6
std::string get_card_image_path(const Card &card) {
// BEGIN: T6  
    return std::string{IMAGE_DIR} + card.get_identifier() + ".png";
// END: T6
}


// TASK: T8
bool can_push_to_tableau(const Card card, std::vector<Card> cards)
{
// BEGIN: T8    

    // Vi sjekker først om bunken er tom
    // og om card er king
    if (cards.empty()) {
        return (card.get_rank() == CARD_K) ? true : false;
    } 

    // Først gjør vi det enkelt for oss selv og lager en top card variabel
    const Card topCard = cards.at(cards.size() - 1);

    // Vi bruker så motsatt testing av det vi ønsker slik at vi 
    // kan returne så tidlig som mulig så lenge bare en av testene ikke funger

    // Vi sjekker om topCard er nøyaktig en mer enn card
    if (topCard.get_rank() - card.get_rank() != 1) {
        return false;
    }

    // Vi sjekker om fargene er like
    if (topCard.get_color() == card.get_color()) {
        return false;
    }

    // All checks passed og kortet er gyldig
    return true;
// END: T8
}



// TASK: T9
bool is_valid_image_path(const std::filesystem::path &path) {
// BEGIN: T9

    // Leter litt rundt i cpp refrence og ser at filesystem::path har en metode
    // som heter .extension() som gir filtypen 
    auto extension = path.extension();

    // Sjekker opp imot tillatte filtyper
    if (extension == ".png") {
        return true;
    } else if (extension == ".jpg") {
        return true;
    } else if (extension == ".bmp") {
        return true;
    }

    return false;

// END: T9
}

// TASK: T11
// BEGIN: T11
std::ostream& operator<<(std::ostream& os, const Card& c) {
    return os << c.get_identifier();
}
// END: T11


// DO NOT TOUCH ANYTHING BELOW THIS POINT
void update_card_stack_positions(const TDT4102::Point anchor, std::vector<Card> &container) {

    auto pos = 0;
    for ( auto &card : container ) {
        int y_offset = pos++ * CARD_OVERLAP;


        card.set_position({anchor.x, anchor.y + y_offset});
    }
}



