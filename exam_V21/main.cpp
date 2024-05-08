#include "Graph.h"
#include "Window.h"
#include "std_lib_facilities.h"

#include "Gameoflife.h"

int main()
{
	using namespace Graph_lib;

	// Enable runtime multithreading support for FLTK
	Fl::lock();

	// Configure the number of cells in the Game of life universe
	// and the graphical window's title.
	constexpr int x_cells = 50;
	constexpr int y_cells = 50;
	const string window_title = "Conway's Game of Life";

	// Create an instance of the Gameoflife window.
	Gameoflife gol{x_cells, y_cells, window_title};

	// Run Window::gui_main() to execute the Graph_lib/FLTK loop
	return Graph_lib::gui_main();
}
