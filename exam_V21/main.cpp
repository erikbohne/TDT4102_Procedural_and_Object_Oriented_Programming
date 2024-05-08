#include "Gameoflife.h"
#include "std_lib_facilities.h"

using namespace TDT4102;

int main() {
    // Configure the number of cells in the Game of life universe
    // and the graphical window's title.
    constexpr int x_cells = 50;
    constexpr int y_cells = 50;
    const string window_title = "Conway's Game of Life";

    // Create an instance of the Gameoflife window.
    Gameoflife gol{x_cells, y_cells, window_title};
    gol.run();
    gol.wait_for_close();

    return 0;
}
