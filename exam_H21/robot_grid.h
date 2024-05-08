#pragma once

#include <memory>
#include <vector>

#include "std_lib_facilities.h"

#include "AnimationWindow.h"
#include "robot.h"

class RobotGrid {
private:
    // The window we should draw to
    AnimationWindow& window;

    const int x_pos;
    const int y_pos;
    const int target_w_size;
    const int target_h_size;
    int w_size;
    int h_size;
    int rows;
    int cols;
    int cell_width;
    int cell_height;

    map<string, unique_ptr<Robot>> robots;

    // Private functions
    void draw_robots();
    void draw_grid_lines();
    Point get_grid_cell_center_coord(int x, int y) const;
    Point get_grid_cell_center_coord(Point pos) const;
    Point get_grid_cell_edge_coord(int x, int y) const;
    Point get_grid_cell_edge_coord(Point pos) const;
    void check_coord_bounds(Point p) const;
    void check_name_available(string name) const;
    void check_name_exists(string name) const;
    void check_coord_empty(Point p, string name, bool is_moving) const;

public:
    RobotGrid(AnimationWindow &window, int x,
            int y, int w, int h, int rows, int cols);

    // Draw the universe
    void draw_universe();

    // Operations
    void make_grid(int rows, int cols);
    void make_robot(string name, Point pos, Color color);
    void delete_robot(string name);
    void move_robot(string name, Point pos);
    void recolor_robot(string name, Color color);
    void clear_robots();
    void rename_robot(string name, string new_name);


};