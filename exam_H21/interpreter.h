#include "robot_grid.h"
#include "std_lib_facilities.h"
#include <optional>
#include <sstream>


struct color_map_def : public map<std::string, Color> {
  color_map_def()
  {
    this->operator[]("red") = Color::red;
    this->operator[]("blue") = Color::blue;
    this->operator[]("green") = Color::green;
    this->operator[]("yellow") = Color::yellow;
    this->operator[]("white") = Color::white;
    this->operator[]("black") = Color::black;
    this->operator[]("magenta") = Color::magenta;
    this->operator[]("cyan") = Color::cyan;
    this->operator[]("dark_red") = Color::dark_red;
    this->operator[]("dark_green") = Color::dark_green;
    this->operator[]("dark_blue") = Color::dark_blue;
    this->operator[]("dark_magenta") = Color::dark_magenta;
    this->operator[]("dark_cyan") = Color::dark_cyan;
    this->operator[]("gray") = Color::gray;
    this->operator[]("dark_gray") = Color::dark_gray;
    this->operator[]("light_gray") = Color::light_gray;
  }
  ~color_map_def()
  {
  }
};

class Interpreter {
private:
    RobotGrid &grid;
    color_map_def color_map;
    Color get_color(string color_name);
public:
    void execute_instruction(istringstream instruction);
    Interpreter(RobotGrid &grid);
};