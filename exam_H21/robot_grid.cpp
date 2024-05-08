#include "robot_grid.h"

// Task G1: drawing grid lines
//
// Implement the code for drawing the lines of the robot grid,
// i.e. the RobotGrid::draw_grid_lines()-function. To solve this
// assignment, use the window.draw_line() function to draw the lines
// and the following class-defined variables to determine the layout of
// the grid:
//
//
//  - x_pos and y_pos: the coordinates of the upper-left corner
// of the grid
//  - w_size and h_size: the width and height of the grid
//  - cell_width and cell_height: the width and height of a cell
void RobotGrid::draw_grid_lines()
{
    // BEGIN: G1

    for (int i = 0; i < h_size; i += cell_height) {
      window.draw_line(TDT4102::Point{x_pos, i}, TDT4102::Point{w_size, i});
    }

    for (int i = 0; i < w_size; i += cell_width) {
      window.draw_line(TDT4102::Point{i, y_pos}, TDT4102::Point{i, h_size});
    }

    // END: G1
}

// Task G2: Get the center of a grid cell
//
// Write the function RobotGrid::get_grid_cell_center_coord()
// that, given the x and y coordinates of a grid cell, returns
// the on-screen coordinates of the center of that cell. For example,
// the center of the grid cell (1, 1)
// could be located (150, 150)
// pixels (depending on the width and height of the grid cells) from
// the top-left corner of the application window. You can calculate
// this using the same values that you used to solve Assignment
// G1.
Point RobotGrid::get_grid_cell_center_coord(int x, int y) const
{
  // BEGIN: G2
  //
  // Write your answer to assignment G2 here, between the // BEGIN: G2
  // and // END: G2 comments. You should remove any code that is
  // already there and replace it with your own.

  int xp = x_pos + (cell_width * x) + (cell_width / 2);
  int yp = y_pos + (cell_height * y) + (cell_height / 2);
  return {xp, yp};

  // END: G2
}

// Task G3: Making a robot
//
// Implement the code for adding a new robot to the grid, the
// RobotGrid::make_robot()-function. You do this by making an
// instance of the Robot class (defined in robot.h) and adding it
// to the robots map. You do not have to check that the position
// and name is valued, we will handle that in a later task.  Keep in
// mind that robots is a map from string to unique_ptr&lt;Robot&gt;.
//
// You have to do task G4 (draw robot) and update part of the code
// described in task S2 in order to test this code. Note that the
// robots will not get the correct color before task S1 has been
// solved.
void RobotGrid::make_robot(string name, Point pos, Color color)
{
  check_name_available(name);
  check_coord_bounds(pos);
  check_coord_empty(pos, name, false);

  // BEGIN: G3
  //
  // Write your answer to assignment G3 here, between the // BEGIN: G3
  // and // END: G3 comments. You should remove any code that is
  // already there and replace it with your own.

  robots.insert({name,make_unique<Robot>(name, pos, color)});

  // END: G3
}

// Task G4: Drawing the robots
//
// Write the code for representing the robots on the grid, the
// RobotGrid::draw_robots() function. A robot is represented by a
// circle that is drawn within the boundaries of the grid cell where
// the robot is positioned. The circle is filled with the color of
// the robot and the name of the robot is written on top of the
// circle, starting from the left edge of, and vertically centered
// within, the bounding grid cell. You do not have to check that the
// position and name is valued, we will handle that in a later task.
void RobotGrid::draw_robots()
{
  // BEGIN: G4
  //
  // Write your answer to assignment G4 here, between the // BEGIN: G4
  // and // END: G4 comments. You should remove any code that is
  // already there and replace it with your own.


  for (const auto& robot : robots) {
    Point pos = get_grid_cell_center_coord(robot.second->pos);
    window.draw_circle(pos, 30, robot.second->color);
    window.draw_text(pos, robot.second->name, TDT4102::Color::gray);
  }

  // END: G4
}

// Task G5: Deleting a robot
//
// Implement the code for deleting a robot from the grid, the
// RobotGrid::delete_robot()-function. Remember that the robots
// that are currently visible on the grid are members of the robots
// map.
//
// You have to update part of the code described in task S2 in
// order to test this code.
void RobotGrid::delete_robot(string name)
{
  check_name_exists(name);

  // BEGIN: G5
  //
  // Write your answer to assignment G5 here, between the // BEGIN: G5
  // and // END: G5 comments. You should remove any code that is
  // already there and replace it with your own.

  robots.erase(name);

  // END: G5
}

// Task G6: Move a robot
//
// Implement the code for moving a robot, i.e. the
// RobotGrid::move_robot()-function. Do this by changing the
// corresponding Robot class instance in the robots-
// map.
//
// You have to update part of the code described in task S2 in
// order to test this code.
void RobotGrid::move_robot(string name, Point pos)
{
  check_name_exists(name);
  check_coord_bounds(pos);
  check_coord_empty(pos, name, true);

  // BEGIN: G6
  //
  // Write your answer to assignment G6 here, between the // BEGIN: G6
  // and // END: G6 comments. You should remove any code that is
  // already there and replace it with your own.

  robots.at(name)->pos = pos;

  // END: G6
}

// Task G7: Recolor a robot
//
// Implement the code for changing the color of a robot,
// i.e. function RobotGrid::recolor_robot().
void RobotGrid::recolor_robot(string name, Color color)
{
  check_name_exists(name);

  // BEGIN: G7
  //
  // Write your answer to assignment G7 here, between the // BEGIN: G7
  // and // END: G7 comments. You should remove any code that is
  // already there and replace it with your own.

  robots.at(name)->color = color;

  // END: G7

}

// Task G8: Clear the grid
//
// Implement the code for removing all robots from the grid,
// i.e. function RobotGrid::clear_robot().
void RobotGrid::clear_robots()
{
  // BEGIN: G8
  //
  // Write your answer to assignment G8 here, between the // BEGIN: G8
  // and // END: G8 comments. You should remove any code that is
  // already there and replace it with your own.

  robots.clear();

  // END: G8

}

// Task G9: Rename a robot
//
// Implement the code for renaming a robot, i.e. the
// RobotGrid::rename_robot()-function. Remember to also change the
// robot's key in the robots map! Thus, there is more to this than
// simply changing the name field of a Robot
// object.
void RobotGrid::rename_robot(string name, string new_name)
{
  check_name_exists(name);
  check_name_available(new_name);

  // BEGIN: G9
  //
  // Write your answer to assignment G9 here, between the // BEGIN: G9
  // and // END: G9 comments. You should remove any code that is
  // already there and replace it with your own.

  robots.at(name)->name = new_name;

  // END: G9
}

// Task G10: Checking coordinate bounds
//
// This function, RobotGrid::check_coord_bounds(), checks if the
// coordinates passed to the function as the point p are
// valid. Valid coordinates are: $0 <= x < cols$ and $0 <= y <
// rows$. If coordinates are not valid, the function should throw an
// exception with a descriptive error message.
void RobotGrid::check_coord_bounds(Point p) const
{
  // BEGIN: G10
  //
  // Write your answer to assignment G10 here, between the // BEGIN: G10
  // and // END: G10 comments. You should remove any code that is
  // already there and replace it with your own.
  if (p.x < 0 || p.x >= cols) {
    throw invalid_argument("x position is out of bounds");
  }

  if (p.y < 0 || p.y >= rows) {
    throw invalid_argument("y position is out of bounds");
  }

  // END: G10

}

// Task G11: Check if robot name is available
//
// This function, RobotGrid::check_name_available(), checks if
// the name is available for use by a robot. This is the case if
// the value of the parameter name is NOT a key in the robots
// map. If the name is already in use, the function should throw an
// exception with a descriptive error message.
void RobotGrid::check_name_available(string name) const
{
  // BEGIN: G11
  //
  // Write your answer to assignment G11 here, between the // BEGIN: G11
  // and // END: G11 comments. You should remove any code that is
  // already there and replace it with your own.
  if (robots.find(name) != robots.end()) {
    throw string("Name already exists in robots list");
  }
  // END: G11
}

// Task G12: Check if robot exists
//
// This function, RobotGrid::check_name_exists(), checks if there
// exists a robot named name. This is the case if the value of
// name is a key in the robots map. If the name is NOT already
// in use, the function should throw an exception with a descriptive
// error message.
void RobotGrid::check_name_exists(string name) const
{
  // BEGIN: G12
  //
  // Write your answer to assignment G12 here, between the // BEGIN: G12
  // and // END: G12 comments. You should remove any code that is
  // already there and replace it with your own.
  if (robots.find(name) == robots.end()) {
    throw string("Robot does not exist in robots list");
  }

  // END: G12

}

// Task G13: Check if a grid coordinate is empty
//
// This function, RobotGrid::check_coord_empty(), checks if there
// is a robot in the grid cell corresponding to the coordinates given
// in the parameterp.  The parameter is_moving is true when the
// function is called as part of executing the move_robot
// instruction and false when the function is called as part of
// executing the make_robot instruction. name is the name of the
// robot that is being moved or created. The distinction between
// moving and creating is important because we allow a robot to be
// moved to itself. That is, the program:
//
// make_robot tao 1 1 blue
// move_robot tao 1 1
//
// is valid, whereas the program:
//
// make_robot tao 1 1 blue
// make_robot fatima 1 1 green
//
// is not.
//
// The function should throw an exception with a descriptive error
// message if a grid cell is already occupied by another robot. Keep
// the move to self-move exception described above in
// mind.
void RobotGrid::check_coord_empty(Point p, string name, bool is_moving) const
{
  // BEGIN: G13
  //
  // Write your answer to assignment G13 here, between the // BEGIN: G13
  // and // END: G13 comments. You should remove any code that is
  // already there and replace it with your own.

  for (auto&robot : robots) {
    if (robot.second->pos.x == p.x && robot.second->pos.y == p.y) {
      if (name != robot.first || !is_moving) {
        throw string("There is already a robot at this position");
      }
    }
  }
  
  // END: G13

}

//
// END OF ASSIGNMENTS
//
// Draws the grid lines and the robots

void RobotGrid::draw_universe() 
{
  draw_grid_lines();
  draw_robots();
}

// Returns the edge coordinate of a grid cell
Point RobotGrid::get_grid_cell_edge_coord(Point pos) const
{
  auto [x, y] = pos;
  return get_grid_cell_edge_coord(x, y);
}

Point RobotGrid::get_grid_cell_edge_coord(int x, int y) const
{
  int xp = x_pos + (cell_width * x);
  int yp = y_pos + (cell_height * y) + (cell_height / 2);
  return {xp, yp};
}

// Returns the edge coordinate of a grid cell
Point RobotGrid::get_grid_cell_center_coord(Point pos) const
{
  auto [x, y] = pos;
  return get_grid_cell_center_coord(x, y);
}

// Initializes the values of the grid
void RobotGrid::make_grid(int rows, int cols)
{
  if (rows == 0 || cols == 0) {
    throw invalid_argument("Arguments of make_grid must be greater than 0");
  }
  // Crashing have been observed for large grids
  if (rows > 100 || cols > 100) {
    throw invalid_argument("Arguments of make_grid must be less than 100");
  }

  this->rows = rows;
  this->cols = cols;
  //the four lines below were wrong in the original handout (mixing of cols and rows), but this error would not have been visible if all tested cases had grids of N*N (square)
  cell_width = target_w_size / cols; 
  cell_height = target_h_size / rows;
  w_size = cell_width * cols;
  h_size = cell_height * rows;

  clear_robots();
}

RobotGrid::RobotGrid(AnimationWindow &window,
                     int x, int y, int w, int h, int rows = 1, int cols = 1)
    : window(window), x_pos(x), y_pos(y),
      target_w_size(w), target_h_size(h), w_size(w), h_size(h), rows(rows),
      cols(cols), cell_width(w_size / rows), cell_height(h_size / rows)
{
}