#include "AnimationWindow.h"
#include "Foundation.h"
#include "Pile.h"
#include <algorithm>
#include <cassert>
#include <functional>
#include <random>

// ------------------------------------------------------------
#include "Entity.h"
#include "Card.h"
#include "CardDeck.h"
#include "Renderers.h"
#include "Tableau.h"
#include "Tasks.h"


///< Generates a new sorted deck
std::vector<Card> newDeck() {
    std::vector<Card> result{};

    for ( int i = CARD_A; i <= CARD_K; i++ ) {
        result.emplace_back(i, Suit::DIAMONDS);
        result.emplace_back(i, Suit::SPADES);
        result.emplace_back(i, Suit::CLUBS);
        result.emplace_back(i, Suit::HEARTS);
    }

    return result;
}

///< Shuffles a deck in-place.
void shuffleCollection(std::vector<Card> &deck) {
    std::random_device rd{};
    std::mt19937 twister{rd()};

    std::shuffle(deck.begin(), deck.end(), twister);
};

std::vector<Foundation> makeFoundationSlots() {
    std::vector<Foundation> result{};

    result.emplace_back(TDT4102::Point{20, 10});
    result.emplace_back(TDT4102::Point{20 + 69, 10});
    result.emplace_back(TDT4102::Point{20 + 69*2, 10});
    result.emplace_back(TDT4102::Point{20 + 69*3, 10});

    return result;
};

std::vector<Tableau> makeTableauSlots() {

    std::vector<Tableau> result{};

    result.emplace_back();
    result.emplace_back();
    result.emplace_back();
    result.emplace_back();
    result.emplace_back();
    result.emplace_back();
    result.emplace_back();

    result[0].set_position({20, Card::CARD_HEIGHT*3});
    result[1].set_position({20 + 1*69 + 1*10, Card::CARD_HEIGHT*3});
    result[2].set_position({20 + 2*69 + 2*10, Card::CARD_HEIGHT*3});
    result[3].set_position({20 + 3*69 + 3*10, Card::CARD_HEIGHT*3});
    result[4].set_position({20 + 4*69 + 4*10, Card::CARD_HEIGHT*3});
    result[5].set_position({20 + 5*69 + 5*10, Card::CARD_HEIGHT*3});
    result[6].set_position({20 + 6*69 + 6*10, Card::CARD_HEIGHT*3});

    return result;
};


static std::vector<Tableau> tableaus;
static std::vector<Foundation> foundations;

/**
 * The game state class.
 *
 * This works as a POD structure with some additional utility functions.
 */
struct GameState {

    /// The index of the currently selected tableau. See `tableaus`
    int tableau_idx{-1};

    /// The index of the selected card in the tableau.
    int tableau_stack_idx{-1};

    /// True when the user has selected the pile.
    bool pile_selected{false};

    /// The index of the currently selected foundation. See `foundations`.
    int foundation_idx{-1};

    void reset() {
        tableau_idx = -1;
        tableau_stack_idx= -1;
        pile_selected= false;
        foundation_idx= -1;
    }

    void select_pile() {
        reset();

        if ( pile.empty() ) return;

        pile_selected = true;
    }

    void select_tableau(int idx_, int stack_idx_) {
        reset();
        tableau_idx = idx_;

        if ( stack_idx_ == -1 ) {
            tableau_stack_idx = tableaus[idx_].get_held_stack().size() - 1;
        } else {
            tableau_stack_idx = stack_idx_;
        }
;
    }

    bool has_selection() {
        return tableau_idx >= 0 || pile_selected || foundation_idx >= 0;
    }
};


static GameState state{};

struct DropButton : TDT4102::Button {
    explicit DropButton(TDT4102::Point location, unsigned int width, unsigned int height, std::string label) :
         Button{location, width, height, label} {}
};

struct FoundationDropButton : TDT4102::Button {
    explicit FoundationDropButton(TDT4102::Point location, unsigned int width, unsigned int height, std::string label) :
         Button{location, width, height, label} {}
};


/**
 * Moves the currently selected card(s) to the target foundation.
 *
 * @param target_idx The index of the tableau to drop the cards on.
 */
void move_cards_foundation(int target_idx) {
    auto &target_foundation = foundations[target_idx];

    // The case where the pile is selected as the source.
    if  ( state.pile_selected ) {
        auto pc = pile.current();

        if ( target_foundation.can_push(pc) ) {
            target_foundation.push(pc);
            pile.delete_and_rotate();
        }

        state.reset();

        return;
    }

    // The case where a tableau is selected as the source.
    if ( state.tableau_idx < 0 || state.tableau_idx >= tableaus.size() ) {
        state.reset();
        return;
    }

    auto &from_container = tableaus[state.tableau_idx].get_held_stack();

    if ( from_container.size() == 0 ) { return; }

    if ( foundations[target_idx].can_push(from_container.get_container().back()) ) {
        auto res = from_container.pop_top_n(1);

        if ( ! res.empty() ) {
            foundations[target_idx].push(res.back());
        }
    };

    state.reset();


}

/**
 * Moves the currently selected card(s) to the target tableau.
 *
 * @param target_idx Index of the target tableau. See `tableaus`.
 */
void move_to_tableau(int target_idx)
{
    auto &to_tableau = tableaus[target_idx];
    auto &to_stack = to_tableau.get_held_stack();

    // ========================================
    // Move tableau to tableau
    // ========================================
    if ( state.tableau_idx < 0 || target_idx < 0) {
        return;
    }

    // Pop the selected cards
    auto &from_stack = tableaus[state.tableau_idx].get_held_stack();
    int num_cards_to_pop = from_stack.size() - state.tableau_stack_idx;
    auto res = from_stack.pop_top_n(num_cards_to_pop);


    while ( res.size() && to_tableau.can_push(res.back())) {
        to_stack.push_unchecked(res.back());
        res.pop_back();
    }


    // Push it back to where it came from if not valid for push
    while ( res.size() ) {
        from_stack.push_unchecked(res.back());
        res.pop_back();
    }

    state.reset();

}


void move_cards_tableau(int target_idx) {
    // Determine selected cards

    auto &to_tableau = tableaus[target_idx];
    auto &to_stack = to_tableau.get_held_stack();

    // ========================================
    // Move pile to tableau
    // ========================================
    if ( state.pile_selected ) {
        auto res = pile.current();

        if ( to_tableau.can_push(res) ) {
            to_tableau.get_held_stack().push_unchecked(res);
            pile.delete_and_rotate();
        }

        state.reset();
        return;
    }

    // ========================================
    // Move foundation to tableau
    // ========================================
    if ( state.foundation_idx >= 0 ) {
        auto &sel_foundation = foundations[state.foundation_idx];
        auto &from_container = sel_foundation.get_container();

        if ( from_container.empty() ) {
            return;
        }

        auto cand_card = from_container.back();

        if ( to_tableau.can_push(cand_card) ) {
            from_container.pop_back();
            to_stack.push_unchecked(cand_card);
        }
    }


    move_to_tableau(target_idx);

    // Unselect
    state.reset();
}

// ========================================
// UI Callbacks
// ========================================
void move_tableau(int idx) { move_cards_tableau(idx); }
void select_tableau(int idx) { state.select_tableau(idx, -1); }
void move_foundation(int idx) { move_cards_foundation(idx); }
void select_foundation(int idx) { state.reset(); state.foundation_idx = idx; }
void select_pile() { state.select_pile(); }
void rotate_pile() { pile.rotate(); }

int main() {

    // Load images
    load_image_atlas(std::string{IMAGE_DIR} + "/alternative/manifesto.txt");
    ImageAtlas::load_default_atlas();

    auto window = TDT4102::AnimationWindow(50, 50, 1024, 768, "AnimationWindow");

    // Set up the tableaus and foundation slots
    tableaus = makeTableauSlots();
    foundations = makeFoundationSlots();


    // Create a new shuffled deck
    auto deck = newDeck();
    shuffleCollection(deck);


    // ========================================
    // Set up GUI elements
    // ========================================
    PileButton button(TDT4102::Point{window.width() - 100, 10}, 100, 80, "Pile");
    PileButton unselectButton(TDT4102::Point{window.width() - 100, 100}, 100, 80, "Unselect");

    unselectButton.setCallback([] () { state.reset(); });


    // Create "Drop" buttons below their respective tableaus.
    DropButton tableau_drop_button0({tableaus[0].get_position().x, tableaus[0].get_position().y + 360}, 75, 75, "Drop");
    DropButton tableau_drop_button1({tableaus[1].get_position().x, tableaus[1].get_position().y + 360}, 75, 75, "Drop");
    DropButton tableau_drop_button2({tableaus[2].get_position().x, tableaus[2].get_position().y + 360}, 75, 75, "Drop");
    DropButton tableau_drop_button3({tableaus[3].get_position().x, tableaus[3].get_position().y + 360}, 75, 75, "Drop");
    DropButton tableau_drop_button4({tableaus[4].get_position().x, tableaus[4].get_position().y + 360}, 75, 75, "Drop");
    DropButton tableau_drop_button5({tableaus[5].get_position().x, tableaus[5].get_position().y + 360}, 75, 75, "Drop");
    DropButton tableau_drop_button6({tableaus[6].get_position().x, tableaus[6].get_position().y + 360}, 75, 75, "Drop");

    std::vector<std::reference_wrapper<DropButton>> tableau_drop_buttons{};
    tableau_drop_buttons.emplace_back(tableau_drop_button0);
    tableau_drop_buttons.emplace_back(tableau_drop_button1);
    tableau_drop_buttons.emplace_back(tableau_drop_button2);
    tableau_drop_buttons.emplace_back(tableau_drop_button3);
    tableau_drop_buttons.emplace_back(tableau_drop_button4);
    tableau_drop_buttons.emplace_back(tableau_drop_button5);
    tableau_drop_buttons.emplace_back(tableau_drop_button6);

    for ( int i = 0; i < tableau_drop_buttons.size(); i++) {
        auto &btn = tableau_drop_buttons[i].get();
        btn.setCallback(std::bind(move_tableau, i));
        window.add(btn);
    }

    DropButton tableau_select_button0({tableaus[0].get_position().x, tableaus[0].get_position().y + 300}, 75, 75, "Select");
    DropButton tableau_select_button1({tableaus[1].get_position().x, tableaus[1].get_position().y + 300}, 75, 75, "Select");
    DropButton tableau_select_button2({tableaus[2].get_position().x, tableaus[2].get_position().y + 300}, 75, 75, "Select");
    DropButton tableau_select_button3({tableaus[3].get_position().x, tableaus[3].get_position().y + 300}, 75, 75, "Select");
    DropButton tableau_select_button4({tableaus[4].get_position().x, tableaus[4].get_position().y + 300}, 75, 75, "Select");
    DropButton tableau_select_button5({tableaus[5].get_position().x, tableaus[5].get_position().y + 300}, 75, 75, "Select");
    DropButton tableau_select_button6({tableaus[6].get_position().x, tableaus[6].get_position().y + 300}, 75, 75, "Select");

    tableau_select_button0.setCallback(std::bind(select_tableau, 0));
    tableau_select_button1.setCallback(std::bind(select_tableau, 1));
    tableau_select_button2.setCallback(std::bind(select_tableau, 2));
    tableau_select_button3.setCallback(std::bind(select_tableau, 3));
    tableau_select_button4.setCallback(std::bind(select_tableau, 4));
    tableau_select_button5.setCallback(std::bind(select_tableau, 5));
    tableau_select_button6.setCallback(std::bind(select_tableau, 6));

    window.add(tableau_select_button0);
    window.add(tableau_select_button1);
    window.add(tableau_select_button2);
    window.add(tableau_select_button3);
    window.add(tableau_select_button4);
    window.add(tableau_select_button5);
    window.add(tableau_select_button6);

    // Create "Drop" buttons below their respective tableaus.
    FoundationDropButton foundation_drop_button0({foundations[0].get_position().x, foundations[0].get_position().y + Card::CARD_HEIGHT*2 - 20}, 75, 75, "Drop");
    FoundationDropButton foundation_drop_button1({foundations[1].get_position().x, foundations[1].get_position().y + Card::CARD_HEIGHT*2 - 20}, 75, 75, "Drop");
    FoundationDropButton foundation_drop_button2({foundations[2].get_position().x, foundations[2].get_position().y + Card::CARD_HEIGHT*2 - 20}, 75, 75, "Drop");
    FoundationDropButton foundation_drop_button3({foundations[3].get_position().x, foundations[3].get_position().y + Card::CARD_HEIGHT*2 - 20}, 75, 75, "Drop");

    std::vector<std::reference_wrapper<FoundationDropButton>> foundation_drop_buttons{};
    foundation_drop_buttons.emplace_back(foundation_drop_button0);
    foundation_drop_buttons.emplace_back(foundation_drop_button1);
    foundation_drop_buttons.emplace_back(foundation_drop_button2);
    foundation_drop_buttons.emplace_back(foundation_drop_button3);

    for ( int i = 0; i < foundation_drop_buttons.size(); i++) {
        auto &btn = foundation_drop_buttons[i].get();
        btn.setCallback(std::bind(move_foundation, i));
        window.add(btn);
    }

    FoundationDropButton select_fbutton0({foundations[0].get_position().x, foundations[0].get_position().y + Card::CARD_HEIGHT + 10 }, 75, 75, "Select");
    FoundationDropButton select_fbutton1({foundations[1].get_position().x, foundations[1].get_position().y + Card::CARD_HEIGHT + 10 }, 75, 75, "Select");
    FoundationDropButton select_fbutton2({foundations[2].get_position().x, foundations[2].get_position().y + Card::CARD_HEIGHT + 10 }, 75, 75, "Select");
    FoundationDropButton select_fbutton3({foundations[3].get_position().x, foundations[3].get_position().y + Card::CARD_HEIGHT + 10 }, 75, 75, "Select");

    select_fbutton0.setCallback(std::bind(select_foundation, 0));
    select_fbutton1.setCallback(std::bind(select_foundation, 1));
    select_fbutton2.setCallback(std::bind(select_foundation, 2));
    select_fbutton3.setCallback(std::bind(select_foundation, 3));

    window.add(select_fbutton0);
    window.add(select_fbutton1);
    window.add(select_fbutton2);
    window.add(select_fbutton3);

    // Set up the pile button
    button.setCallback(rotate_pile);


    PileButton selectPileButton{ TDT4102::Point{window.width() - 200, 100}, 100, 80, "Select" };

    selectPileButton.setCallback(select_pile);

    window.add(selectPileButton);
    window.add(button);
    window.add(unselectButton);



    // ========================================
    // Distribute cards among tableaus and pile
    // ========================================
    for ( size_t i = 0; i < tableaus.size(); i++ ) {

        auto &tableau = tableaus[i];

        CardDeck &currentStack = tableau.get_held_stack();

        for ( int j = 0; j < i+1; j++ ) {
            currentStack.push_unchecked(deck.back());
            deck.pop_back();

            currentStack.back().set_flipped(true);
        }

        currentStack.back().set_flipped(false);
    }

    pile = Pile(std::move(deck));
    pile.set_position({window.width() - Card::CARD_WIDTH*3, 10});
    pile.set_width(Card::CARD_WIDTH);
    pile.set_height(Card::CARD_HEIGHT);


    while ( ! window.should_close() )
    {

        if ( ! state.has_selection() ) {
            for ( auto &btn : tableau_drop_buttons ) {
                btn.get().setVisible(false);
            }
            for ( auto &btn : foundation_drop_buttons ) {
                btn.get().setVisible(false);
            }
        } else {
            for ( auto &btn : tableau_drop_buttons ) {
                btn.get().setVisible(true);
            }
            for ( auto &btn : foundation_drop_buttons) {
                if ( state.foundation_idx >= 0 ) {
                    btn.get().setVisible(false);
                } else {
                    btn.get().setVisible(true);
                }
            }
        }

        window.next_frame();

        TDT4102::Point mouse_coords = window.get_mouse_coordinates();

        for ( auto &slot : tableaus) {
            slot.update();
            window.draw_rectangle(slot.get_position(), slot.get_width(), slot.get_height(), TDT4102::Color::gray, TDT4102::Color::black);
        }

        for ( auto &slot : foundations) {
            slot.update();
            window.draw_rectangle(slot.get_position(), slot.get_width(), slot.get_height(), TDT4102::Color::gray, TDT4102::Color::black);
        }



        // ========================================
        // Render *highlight* boxes for selected cards
        // ========================================
        if ( state.tableau_idx >= 0 ) {
            auto &tableau = tableaus[state.tableau_idx];

            auto anchor = tableau.get_position();

            // Adjustment for overlapping cards
            auto yoff = state.tableau_stack_idx * CARD_OVERLAP;
            auto maxY = tableau.get_height();

            window.draw_rectangle(
                    TDT4102::Point{anchor.x-4, anchor.y + yoff},
                    tableau.get_width()+8,
                    maxY-yoff,
                    TDT4102::Color::orange,
                    TDT4102::Color::orange);
        }

        if ( state.pile_selected ) {
            auto anchor = pile.get_position();
            window.draw_rectangle(TDT4102::Point{anchor.x-4, anchor.y}, pile.get_width()+8, pile.get_height(), TDT4102::Color::orange, TDT4102::Color::orange);
        }

        if ( state.foundation_idx >= 0 ) {
            auto &sel_foundation = foundations[state.foundation_idx];
            auto anchor = sel_foundation.get_position();
            anchor.x -= 4;

            window.draw_rectangle(anchor, sel_foundation.get_width() + 8, sel_foundation.get_height(), TDT4102::Color::orange);
        }

        // ========================================
        // Render the cards themselves
        // ========================================
        for ( auto &tableau : tableaus ) {
            CardDeckRenderer::render(window, tableau.get_held_stack());
        }

        for ( auto &foundation : foundations ) {
            FoundationRenderer::render(window, foundation);
        }


        // ========================================
        // Logic for selecting cards when LMB is pressed
        // ========================================
        if ( window.is_left_mouse_button_down() ) {


            // Select foundation
            for ( int i = 0; i < foundations.size(); i++ )
            {
                Foundation &foundation = foundations[i];
                if ( inside_box(mouse_coords, Rectangle{foundation.get_position(), foundation.get_width(), foundation.get_height()} ) ) {
                    state.reset();
                    state.foundation_idx = i;
                }
            }


            // Select tableau
            for ( int i = 0; i < tableaus.size(); i++ )
            {
                Tableau &tableau = tableaus[i];

                if ( inside_box(window.get_mouse_coordinates(), Rectangle{tableau.get_position(), tableau.get_width(), tableau.get_height() }) ) {

                    auto &container = tableau.get_held_stack().get_container();

                    // Get the clicked card's index in the stack.
                    int max_card_index = container.size() - 1;

                    // The number of offsets (overlaps) from the top of the stack to the clicked point.
                    int num_offsets = (mouse_coords.y - tableau.get_position().y) / CARD_OVERLAP;

                    // The prospective card index
                    auto idx = static_cast<int>(std::min(int(container.size()) - 1, num_offsets));

                    // Avoid selecting cards that are flipped by incrementing
                    // the index to the first non-flipped card.
                    while ( idx >= 0 && container[idx].is_flipped() ) {
                        idx++;
                    }

                    state.select_tableau(i, idx);
                }
            }

            // Select pile
            if ( inside_box(mouse_coords, Rectangle{pile.get_position(), pile.get_width(), pile.get_height()}))
            {
                state.select_pile();
            }
        }

        PileRenderer::render(window, pile);

    }

    return 0;
}


