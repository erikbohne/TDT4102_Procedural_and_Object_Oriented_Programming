#include <algorithm>
#include <atomic>
#include <chrono>
#include <exception>
#include <iostream>
#include <thread>
#include <vector>

#include "GUI.h"
#include "Graph.h"
#include "Window.h"

using namespace Graph_lib;

// Compile-time constants that set a number of attributes

// Button size
constexpr int button_width = 75;
constexpr int button_height = 20;

// Spacing between GUI elements
constexpr int margin = 5;

// How many steps are we allowed to make?
// Interval [min_steps, max_steps]
constexpr int min_steps = 1;
constexpr int max_steps = 100;

// Colors to either show or hide a Cell border.
// Same color ground, but different visibility.
const Color border_show = Color{Color::light_gray, Color::visible};
const Color border_hide = Color{Color::light_gray, Color::invisible};

// How wide and tall are the cells?
constexpr int cell_size = 10;

// How long between every automatic update when we play the animation?
// 10 steps/sec = 100 ms
// 30 steps/sec = 33 ms (roughly)
// 60 steps/sec = 16 ms (roughly)
constexpr auto animation_interval = 100ms;

class Cell
{
  public:
	enum class State { Dead = 0, Live };

	Cell(Point pos, int size);

	// Cell information
	int get_value() const;

	// Update the Cell's graphical representation
	void update();

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

	// Attach the Cell's graphical representation to win
	void attach_to(Window& win);

	// IO operators
	friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
	friend std::istream& operator>>(std::istream& is, Cell& cell);

  private:
	// The current state of this Cell
	State state;
	// A shared pointer to the graphical representation of the Cell.
	// The pointer points to an instance of Rectangle that is shared
	// between copies of the Cell.
	shared_ptr<Rectangle> rect;

	// Do not show the border by default.
	bool show_border = false;

	// Mappings between character, state and colors.
	inline static const std::array<Color, 2> colors{Color::black, Color::white};
	inline static const std::array<char, 2> chars{'.', '#'};
	inline static const std::map<char, State> char_to_state{{'.', State::Dead},
	                                                        {'#', State::Live}};
};

class Gameoflife : public Graph_lib::Window
{
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
	bool toggle_cell(Point pos);

	// Return a pointer to the Cell at point pos. If there's no cell at pos,
	// return nullptr.
	Cell* cell_at_pos(Point pos);

	// Handle the mouse-button clicks captured by handler(int).
	int click_handler(Point pos);

	// When the "Step" button is pressed, progress time.
	void step_pressed();

	// Display a graphical alert message to the user of the program.
	void alert(const std::string& message);

	// Load/store the currently displayed state.
	void load_state();
	void save_state();

	// Toggle lines in the grid to make it easier to distinguish between
	// individual cells.
	void toggle_gridlines();

	// FLTK override so that we can capture events and direct the processing
	// of events to our own routines.
	int handle(int event) override;

	// Number of cells in the x and y axis
	int x_cells, y_cells;

	// Store two Grids in an array.
	// They alternate in being the current and scratch grids.
	size_t current_grid = 0, scratch_grid = 1;
	std::array<Grid, 2> grid;

	// Provided
	// GUI buttons and input fields
	// These are all provided as part of the handout and you should
	// not need to modify these definitions.
	Button step_btn{{x_max() - button_width - margin, margin},
	                button_width,
	                button_height,
	                "Step",
	                cb_step};

	In_box steps_input{{x_max() - button_width * 2 - margin * 2, margin},
	                   button_width,
	                   button_height,
	                   "Number of steps"};

	In_box filename_input{
		{x_max() - button_width * 2 - margin * 2, button_height + 2 * margin},
		button_width,
		button_height,
		"Filename"};

	Button load_btn{
		{x_max() - button_width - margin, button_height + margin * 2},
		button_width,
		button_height,
		"Load",
		cb_load};

	Button save_btn{
		{x_max() - button_width - margin, button_height * 2 + margin * 3},
		button_width,
		button_height,
		"Save",
		cb_save};

	Button toggle_gridlines_btn{
		{x_max() - button_width * 2 - margin, button_height * 3 + margin * 4},
		button_width * 2,
		button_height,
		"Toggle grid lines",
		cb_toggle_gridlines};

	Button play_pause_btn{
		{x_max() - button_width * 2 - margin, button_height * 4 + margin * 5},
		button_width * 2,
		button_height,
		"Play/Pause",
		cb_play_pause};

	// Provided - Callback definitions
	static void cb_step(Address, Address win)
	{
		static_cast<Gameoflife*>(win)->step_pressed();
	}

	static void cb_load(Address, Address win)
	{
		static_cast<Gameoflife*>(win)->load_state();
	}

	static void cb_save(Address, Address win)
	{
		static_cast<Gameoflife*>(win)->save_state();
	}

	static void cb_toggle_gridlines(Address, Address win)
	{
		static_cast<Gameoflife*>(win)->toggle_gridlines();
	}

	// Provided
	static void cb_play_pause(Address, Address win)
	{
		static_cast<Gameoflife*>(win)->play_pause();
	}

	// Provided
	// The following methods are for calling
	// the step(int) method every `animation_interval` ms.
	// Play: spawn a thread that animate the universe.
	// Pause: stop animation and join thread.
	// For exam candidates, use the callback function
	// Gameoflife::cb_play_pause(Address, Address) in order
	// to get the animation effect.
	inline static atomic_bool playing = false;
	inline static thread worker;
	void play_pause();
	void animate();
};