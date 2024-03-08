#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

// Abstrakt klasse. Arvende konkrete klasser må implementere funksjonen draw()
// som tegner former i vinduet de skal bli vist i.
class Emoji
{
public:
    virtual void draw(AnimationWindow&) = 0;
    virtual ~Emoji(){}; //destruktør
};


// Face er en klasse som arver fra Emoji. 
class Face : public Emoji 
{
protected:
    TDT4102::Point center;
    int radius;
public:
    Face(TDT4102::Point center, int radius) : center(center), radius(radius) {};
    
    virtual void draw(AnimationWindow& win) override {
        win.draw_circle(center, radius);
    };

    virtual ~Face(){}; //destruktør
};


class EmptyFace : public Face
{
public:
    TDT4102::Point left_eye;
    TDT4102::Point right_eye;
    int eye_radius;
public:
    EmptyFace(Point c, int r, int eyeR) 
        : Face(c, r),
          left_eye{c.x - r/4, c.y - r/4},
          right_eye{c.x + r/4, c.y - r/4},
          eye_radius{eyeR} {}

    void draw(AnimationWindow& win) override {
        Face::draw(win);
        win.draw_circle(left_eye, eye_radius);
        win.draw_circle(right_eye, eye_radius);
    };
};