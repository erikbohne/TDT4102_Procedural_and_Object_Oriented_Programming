#pragma once

#include "AnimationWindow.h"
#include "std_lib_facilities.h"
#include <memory>
#include <sstream>

struct color_map_def : public map<std::string, TDT4102::Color> {
  color_map_def()
  {
    this->operator[]("red") = TDT4102::Color::red;
    this->operator[]("blue") = TDT4102::Color::blue;
    this->operator[]("green") = TDT4102::Color::green;
    this->operator[]("yellow") = TDT4102::Color::yellow;
    this->operator[]("white") = TDT4102::Color::white;
    this->operator[]("black") = TDT4102::Color::black;
    this->operator[]("magenta") = TDT4102::Color::magenta;
    this->operator[]("cyan") = TDT4102::Color::cyan;
    this->operator[]("dark_red") = TDT4102::Color::dark_red;
    this->operator[]("dark_green") = TDT4102::Color::dark_green;
    this->operator[]("dark_blue") = TDT4102::Color::dark_blue;
    this->operator[]("dark_magenta") = TDT4102::Color::dark_magenta;
    this->operator[]("dark_cyan") = TDT4102::Color::dark_cyan;
    this->operator[]("gray") = TDT4102::Color::gray;
    this->operator[]("mid_gray") = TDT4102::Color::mid_gray;
    this->operator[]("dark_gray") = TDT4102::Color::dark_gray;
    this->operator[]("light_gray") = TDT4102::Color::light_gray;
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
  map<char, TDT4102::Color> colors;
  vector<unique_ptr<vector<TDT4102::Color>>> image;

  void read_image(string file_name);
  void read_image_colors(ifstream &image_file_stream, int ncolors);
  void read_image_pixels(ifstream &image_file_stream, int width, int height);

  // Construction helper function
  void add_color(char ref, string color_name);
  void add_pixel(TDT4102::Color color);
  void add_line();
  TDT4102::Color get_color_value(string color);
  void draw_pixel(TDT4102::Point point, TDT4102::Color color);
};

