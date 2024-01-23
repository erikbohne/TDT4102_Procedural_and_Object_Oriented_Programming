#include "std_lib_facilities.h"
#include "AnimationWindow.h"

int main() {
    int w = 1200;
    int h = 1200;
    TDT4102::AnimationWindow window{
        100,
        100, 
        w, 
        h, 
        "Pythagoras"
    };

    // Define triangle points
    TDT4102::Point point1{250, 250};
    TDT4102::Point point2{250, 500}; 
    TDT4102::Point point3{500, 250};

    // Draw the triangle
    window.draw_triangle(point1, point2, point3, Color::red);

    // Draw squares on each side of the triangle
    // Square on the vertical side
    window.draw_quad(point1, point2, {0, 500}, {0, 250}, Color::blue);

    // Square on the horizontal side
    window.draw_quad(point1, point3, {500, 0}, {250, 0}, Color::green);

    // Square on the hypotenuse
    window.draw_quad(point2, point3, {750, 500}, {500, 750}, Color::yellow);

    window.wait_for_close();
    return 0;
}
