#pragma once

#include "std_lib_facilities.h"
#include <cmath>
#include "AnimationWindow.h"
#include "widgets/Button.h"

#ifndef SCALE
#define SCALE 0.91
#endif

#ifndef FRIEND_RADIUS
#define FRIEND_RADIUS (SCALE * 60)
#endif

#ifndef SEPARATION_RADIUS
#define SEPARATION_RADIUS (FRIEND_RADIUS/1.3)
#endif

#ifndef AVOID_RADIUS
#define AVOID_RADIUS (SCALE * 90)
#endif

#ifndef MAX_SPEED
#define MAX_SPEED (2.1 * SCALE)
#endif

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1400
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 800
#endif

// ---------------------------------
// --------- FLOATINGPOINT ---------
// ---------------------------------
struct FloatingPoint {
    double x;
    double y;
};

// ---------------------------------
// ------------- BIRD --------------
// ---------------------------------
class Bird
{
public:
    Bird (FloatingPoint position, FloatingPoint velocity, Color color, double size);
    virtual ~Bird () {};

    FloatingPoint getPosition() noexcept;
    FloatingPoint getVelocity() noexcept;
    void setVelocity(FloatingPoint velocity);
    Color getOriginalColor() noexcept;
    Color getDisplayColor() noexcept;

    void draw(AnimationWindow &window) const;
    void updatePosition();
    void update();

    virtual void updateVelocity() = 0;
    virtual void makeFriendsAndFoes(vector<shared_ptr<Bird>> &birds) = 0;

protected:
    FloatingPoint position;
    FloatingPoint velocity;

    const Color originalColor;
    Color displayColor;
    double size;

    vector<shared_ptr<Bird>> foes;

    FloatingPoint calculateAvoidance();
};

class Dove : public Bird
{
public:
    Dove (FloatingPoint position, FloatingPoint velocity, Color color, double size) 
        : Bird (position, velocity, color, size) {};
    virtual ~Dove () {};
    
    vector<shared_ptr<Bird>> getFriends() const noexcept;
    void setColor(Color color);

    void updateVelocity() override;
    void makeFriendsAndFoes(vector<shared_ptr<Bird>> &birds) override;

private:
    vector<shared_ptr<Bird>> friends;

    FloatingPoint calculateCohesion();
    FloatingPoint calculateSeparation();
    FloatingPoint calculateAlignment();
};

// Task T11: Complete the Hawk class.
// BEGIN: T11
class Hawk : public Bird
{

public:
    Hawk (FloatingPoint position, FloatingPoint velocity, Color color, double size);

    virtual ~Hawk () {};

    std::array<FloatingPoint, 4> controlPoints;
    double time=0.0;

    void generateControlPoints(const int widthRange, const int heightRange);
    FloatingPoint calculateBezierVelocity();
    void updateVelocity();
    void makeFriendsAndFoes(vector<shared_ptr<Bird>> &birds);
};
// END: T11

// ---------------------------------
// ----------- SIMULATOR -----------
// ---------------------------------
class Simulator
{
public:
    Simulator (AnimationWindow &window);
    
    bool simulationEnabled = false;
    
    void drawUniverse() const;
    void simulate();
    
    void toggleSimulation();
    void resetSimulation();
    void applyConfiguration(int numBirds, int numHawks);
private:
    AnimationWindow &window;
    vector<shared_ptr<Bird>> birds;
  
    int numDoves = 32;
    int numHawks = 2;
    bool simulationReset = false;
    bool doveSpawnKeysPressed = false;
    bool hawkSpawnKeysPressed = false;

    void boundBird(shared_ptr<Bird> &bird);
    void createBirds();
    void createDove(FloatingPoint position, FloatingPoint velocity, Color color);
    void createHawk(FloatingPoint position, FloatingPoint velocity);
    void addBird();
    void colorBirds();
};

// ---------------------------------
// -------------- GUI --------------
// ---------------------------------
class ToggleButton : public Button {
public:
    ToggleButton ();
    ~ToggleButton ();

    void callback();
    static void setSimulator(Simulator* const _sim);

private:
    static Simulator *sim;
};

class ResetButton : public Button {
public:
    ResetButton ();
    ~ResetButton ();

    static void callback();
    static void setSimulator(Simulator* const _sim);

private:
    static Simulator *sim;
};
