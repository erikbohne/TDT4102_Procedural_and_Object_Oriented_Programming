#include "MinesweeperWindow.h"
#include <iostream>

MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) : 
	// Initialiser medlemsvariabler, bruker konstruktoren til AnimationWindow-klassen
	AnimationWindow{x, y, width * cellSize, (height + 1) * cellSize, title},
	width{width}, height{height}, mines{mines}
{
	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->setCallback(std::bind(&MinesweeperWindow::cb_click, this));
			auto temp = tiles.back().get();
			add(*temp); 
		}
	}
	// Legg til miner paa tilfeldige posisjoner
	for (int i = 0; i < mines; ++i) {
		int x = rand() % width;
		int y = rand() % height;
		at(Point{x * cellSize, y * cellSize})->setMine();
	}
}

vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}
	return points;
}

int MinesweeperWindow::countMines(vector<Point> coords) const {
	int count = 0;
	for (Point p : coords) {
		if (at(p)->getMine()) {
			++count;
		}
	}
	return count;
}

void MinesweeperWindow::openTile(Point xy) {
	shared_ptr<Tile>& tile = at(xy);
	if (tile.get()->getState() != Cell::closed) {
		return;
	}
	tile.get()->open();
	if (tile.get()->getMine()) {
		cout << "Game over!" << endl;
	} else {
		vector<Point> adj = adjacentPoints(xy);
		int mines = countMines(adj);
		tile.get()->setAdjMines(mines);
		if (mines == 0) {
			for (Point p : adj) {
				openTile(p);
			}
		}
	}

}

void MinesweeperWindow::flagTile(Point xy) {
	shared_ptr<Tile>& tile = at(xy);
	if (tile.get()->getState() == Cell::open) {
		return;
	}
	tile.get()->flag();
}

//Kaller openTile ved venstreklikk og flagTile ved hoyreklikk
void MinesweeperWindow::cb_click() {
	
	Point xy{this->get_mouse_coordinates()};

	if (!inRange(xy)) {
		return;
	}
	if (this->is_left_mouse_button_down()) {
		openTile(xy);
	}
	else if(this->is_right_mouse_button_down()){
		flagTile(xy);
	}
}
