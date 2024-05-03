#pragma once

#include "AnimationWindow.h"
#include "std_lib_facilities.h"
#include <memory>
#include <sstream>

struct color_map_def : public map<std::string, Graph_lib::Color::Color_type> {
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
    this->operator[]("dark_yellow") = Color::dark_yellow;
    this->operator[]("dark_blue") = Color::dark_blue;
    this->operator[]("dark_magenta") = Color::dark_magenta;
    this->operator[]("dark_cyan") = Color::dark_cyan;
    this->operator[]("gray") = Color::gray;
    this->operator[]("mid_gray") = Color::mid_gray;
    this->operator[]("dark_gray") = Color::dark_gray;
    this->operator[]("light_gray") = Color::light_gray;
  }
  ~color_map_def()
  {
  }
};

class ImageRenderer
{
public:
  ImageRenderer(AnimationWindow &window, int x, int y, string file_name);
  void draw_image();

private:
  AnimationWindow &window;

  int x;
  int y;
  int width;

  color_map_def color_map;

  // Internal representation of an image
  map<char, Graph_lib::Color::Color_type> colors;
  vector<unique_ptr<vector<Graph_lib::Color::Color_type>>> image;

  void read_image(string file_name);
  void read_image_colors(ifstream &image_file_stream, int ncolors);
  void read_image_pixels(ifstream &image_file_stream, int width, int height);

  // Construction helper function
  void add_color(char ref, string color_name);
  void add_pixel(Graph_lib::Color::Color_type color);
  void add_line();
  Graph_lib::Color::Color_type get_color_value(string color);
  void draw_pixel(Point point, Graph_lib::Color::Color_type color);
};

