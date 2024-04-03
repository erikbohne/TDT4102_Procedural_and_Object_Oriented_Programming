#include "Tile.h"



// For aa sette Tilelabel i henhold til state
const std::map<Cell, std::string> cellToSymbol{{Cell::closed, ""},
									 			{Cell::open, ""},
									 	  		{Cell::flagged, "|>"}};

Tile::Tile(TDT4102::Point pos, int size) : 
	Button({pos.x, pos.y}, 1.5*size, size, "") {
		setButtonColor(TDT4102::Color::silver);
	}

void Tile::open()
{
	if (this->state == Cell::flagged) {
		set_label(cellToSymbol.at(Cell::flagged));
		return;
	}
	this->state = Cell::open;
	if (this->isMine) {
		set_label("X");
		set_label_color(TDT4102::Color::red);
	}
}

void Tile::flag()
{
	if (this->state == Cell::flagged) {
		this->state = Cell::closed;
		set_label("");
	} else {
		this->state = Cell::flagged;
		set_label(cellToSymbol.at(Cell::flagged));
	}
}

bool Tile::getMine()
{
	return this->isMine;
}

void Tile::setMine()
{
	this->isMine = true;
}

void Tile::setAdjMines(int n)
{
	if (n == 0) {
		set_label("");
	} else {
		set_label(std::to_string(n));
		set_label_color(minesToColor.at(n));
	}
}


