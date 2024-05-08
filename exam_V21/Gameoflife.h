#include <algorithm>
#include <atomic>
#include <chrono>
#include <exception>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"

// Compile-time constants that set a number of attributes

// Button size
constexpr int button_width = 100;
constexpr int button_height = 30;

// Spacing between GUI elements
constexpr int margin = 15;

// How many steps are we allowed to make?
// Interval [min_steps, max_steps]
constexpr int min_steps = 1;
constexpr int max_steps = 100;

// Colors to either show or hide a Cell border.
// Same color ground, but different visibility.
const TDT4102::Color border_show = TDT4102::Color::light_gray;
const TDT4102::Color border_hide = TDT4102::Color::transparent;

// How wide and tall are the cells?
constexpr int cell_size = 10;

// How long between every automatic update when we play the animation?
// 10 steps/sec = 100 ms
// 30 steps/sec = 33 ms (roughly)
// 60 steps/sec = 16 ms (roughly)
constexpr Uint64 animation_interval = 50;  // ms;

class Cell {
   public:
    enum class State { Dead = 0,
                       Live };

    Cell(TDT4102::Point pos, int size);

    // Cell information
    int get_value() const;

    // Update the Cell's graphical representation
    // void update();

    // Kill or resurrect the Cell
    void kill();
    void resurrect();

    // State modification
    void set_state(char c);

    // Cell information
    bool is_alive() const;
    char as_char() const;

    // Toggle the Cell's state
    void toggle();

    // Toggle the Cell's border visibility
    void toggle_border();

    int get_size() { return size; }
    TDT4102::Point get_pos() { return pos; }

    // Attach the Cell's graphical representation to win
    // void attach_to(Window& win);

    // IO operators
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
    friend std::istream& operator>>(std::istream& is, Cell& cell);

   private:
    // The current state of this Cell
    State state;
    // A shared pointer to the graphical representation of the Cell.
    // The pointer points to an instance of Rectangle that is shared
    // between copies of the Cell.
    // shared_ptr<Rectangle> rect;
    TDT4102::Point pos;
    int size;

    // Do not show the border by default.
    bool show_border = false;

    // Mappings between character, state and colors.
    inline static const std::array<TDT4102::Color, 2> colors{TDT4102::Color::black, TDT4102::Color::white};
    inline static const std::array<char, 2> chars{'.', '#'};
    inline static const std::map<char, State> char_to_state{{'.', State::Dead},
                                                            {'#', State::Live}};
};

class Gameoflife : public TDT4102::AnimationWindow {
   public:
    // Grid is an alias for a 2D vector containing unnamed Cell-objects.
    using Grid = std::vector<std::vector<Cell>>;

    Gameoflife(int x_cells, int y_cells, const std::string& window_title);

    friend std::ostream& operator<<(std::ostream& os,
                                    const Gameoflife& gameoflife);

    friend std::istream& operator>>(std::istream& is, Gameoflife& gameoflife);

    ~Gameoflife();

   private:
    // These four member functions gives the caller a reference
    // to the current and scratch grids.
    Grid& get_current_grid();
    Grid& get_scratch_grid();
    const Grid& get_current_grid() const;
    const Grid& get_scratch_grid() const;

    // Load/store from/to filename.
    void load(const std::string& filename);
    void save(const std::string& filename);

    // Progress the universe time by steps number of time steps.
    void step(int steps);
    // Perform _one_ step in time.
    void step();

    // Toggles the state of the cell at pos.
    // Returns true if it successfully toggled a cell, false otherwise.
    bool toggle_cell(TDT4102::Point pos);

    // Return a pointer to the Cell at point pos. If there's no cell at pos,
    // return nullptr.
    Cell* cell_at_pos(TDT4102::Point pos);

    // Handle the mouse-button clicks captured by handler(int).
    int click_handler(TDT4102::Point pos);

    // Helper function to only trigger a single click per mousedown
    bool left_mouse_clicked();

    // When the "Step" button is pressed, progress time.
    void step_pressed();

    // Display a graphical alert message to the user of the program.
    void alert(const std::string& message);

    // Load/store the currently displayed state.
    void load_state();
    void save_state();

    // Toggle lines in the grid to make it easier to distinguish between
    // individual cells.
    // void toggle_gridlines();

    // Number of cells in the x and y axis
    int x_cells, y_cells;

    size_t current_grid = 0, scratch_grid = 1;
    std::array<Grid, 2> grid;

    TDT4102::Button step_btn;

    TDT4102::TextInput steps_input;

    TDT4102::TextInput filename_input;

    TDT4102::Button load_btn;

    TDT4102::Button save_btn;

    TDT4102::Button play_pause_btn;

    void play_pause();
    bool playing = false;

   public:
    void run();
    void drawState();
};
