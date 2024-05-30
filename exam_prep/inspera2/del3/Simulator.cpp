#include "Simulator.h"

using SIM_RAND_DISTRIB = std::uniform_int_distribution<>;
using SIM_RAND_TYPE = SIM_RAND_DISTRIB::result_type;
static constexpr auto SIM_RAND_MIN = std::numeric_limits< SIM_RAND_TYPE >::min();
static constexpr auto SIM_RAND_MAX = std::numeric_limits< SIM_RAND_TYPE >::max();

// ---------------------------------
// ------------ HELPERS ------------
// ---------------------------------
double magnitude(FloatingPoint a)
{
    return std::sqrt(std::pow(a.x, 2) + std::pow(a.y, 2));
}

int randomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    SIM_RAND_DISTRIB distrib(min, max);

    return distrib(gen);
}

template<typename DerivedType, typename BaseType>
inline bool isInstanceOf(BaseType *ptr) {
   return dynamic_cast<DerivedType *> (ptr) != nullptr;
}

// ---------------------------------
// --------- FLOATINGPOINT ---------
// ---------------------------------
FloatingPoint operator-(FloatingPoint a, FloatingPoint b) { return {a.x - b.x, a.y - b.y}; }
FloatingPoint operator*(FloatingPoint a, double b) { return {a.x * b, a.y * b}; }
FloatingPoint operator/(FloatingPoint a, double b) { return {a.x / b, a.y / b}; }
bool operator==(FloatingPoint a, FloatingPoint b) { return (int(a.x) == int(b.x) && int(a.y) == int(b.y)); }

// Task T1: Overload the + operator for the FloatingPoint structure.
// BEGIN: T1
FloatingPoint operator+(FloatingPoint a, FloatingPoint b) { return {a.x + b.x, a.y + b.y}; }
// END: T1

// ---------------------------------
// ------------- BIRD --------------
// ---------------------------------
Bird::Bird (FloatingPoint position, FloatingPoint velocity, Color color, double size)
    : position{position}, velocity{velocity}, originalColor{color}, displayColor{color}, size{size} {};

FloatingPoint Bird::getPosition() noexcept
{
    return position;
}

FloatingPoint Bird::getVelocity() noexcept
{
    return velocity;
}

void Bird::setVelocity(FloatingPoint velocity)
{
    this->velocity = velocity;
}

Color Bird::getOriginalColor() noexcept
{
    return originalColor;
}

Color Bird::getDisplayColor() noexcept
{
    return displayColor;
}

// Task T2: Update the position of the bird using
// its current position and velocity.
void Bird::updatePosition()
{
// BEGIN: T2
    position = position + velocity;
// END: T2
}

void Bird::update()
{
    updateVelocity();
    updatePosition();
}

// Task T8: Orient the birds so that they are facing
// in the direction they are headed.
void Bird::draw(AnimationWindow &window) const
{
// BEGIN: T8
    const double PI = 3.14159265;

    double direction = atan2(velocity.y, velocity.x);

    FloatingPoint p1 = {
        position.x + cos(direction) * size, 
        position.y + sin(direction) * size
    };
    FloatingPoint p2 = {
        position.x + cos(direction + (2*PI/3)) * size, 
        position.y + sin(direction + (2*PI/3)) * size
    };
    FloatingPoint p3 = {
        position.x + cos(direction - (2*PI/3)) * size, 
        position.y + sin(direction - (2*PI/3)) * size
    };
    
    window.draw_triangle(
        {static_cast<int> (p1.x), static_cast<int> (p1.y)},
        {static_cast<int> (p2.x), static_cast<int> (p2.y)},
        {static_cast<int> (p3.x), static_cast<int> (p3.y)},
        displayColor
    );
// END: T8
}

vector<shared_ptr<Bird>> Dove::getFriends() const noexcept
{
    return friends;
}

void Dove::setColor(Color color)
{
    displayColor = color;
}

// Task T6: Split the birds into friends and foes based on type
// and visual range.
// BEGIN: T6

double distance(FloatingPoint a, FloatingPoint b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Dove::makeFriendsAndFoes(vector<shared_ptr<Bird>> &birds)
{
    friends.clear();
    foes.clear();

    for (const auto& bird : birds) {
        // Make sure we dont add itself
        if (bird.get() == this) {
            continue; 
        }

        // Check if dove
        if (isInstanceOf<Dove>(bird.get()) && distance(bird.get()->getPosition(), this->position) < FRIEND_RADIUS) {
            friends.push_back(bird);
        }

        // Check if hawk
        else if (isInstanceOf<Hawk>(bird.get()) && distance(bird.get()->getPosition(), this->position) < AVOID_RADIUS) {
            foes.push_back(bird);
        }
    }

}
// END: T6

// Task T7: Update the velocity of the Dove based on cohesion, separation,
// alignment and avoidance.
void Dove::updateVelocity()
{
// BEGIN: T7
    FloatingPoint newSpeed = velocity
                            + calculateCohesion()
                            + calculateAlignment()
                            + calculateSeparation()
                            + calculateAvoidance();

    if (magnitude(newSpeed) > MAX_SPEED) {
        newSpeed.x /= MAX_SPEED;
        newSpeed.y /= MAX_SPEED; 
    }

    velocity = newSpeed;
// END: T7
}

#ifndef HAWK_IS_IMPLEMENTED
Hawk::Hawk (FloatingPoint position, FloatingPoint velocity, Color color, double size)
    : Bird (position, velocity, color, size) {
    generateControlPoints(WINDOW_WIDTH, WINDOW_HEIGHT);
};
#endif

// Derivative of the Cubic Bezier Curve (velocity)
#ifndef HAWK_IS_IMPLEMENTED
FloatingPoint Hawk::calculateBezierVelocity()
{
    FloatingPoint velocity;

    FloatingPoint velocity1 = (controlPoints.at(1) - controlPoints.at(0)) * 3 * std::pow((1.0 - time), 2.0);
    FloatingPoint velocity2 = (controlPoints.at(2) - controlPoints.at(1)) * 6 * (1.0 - time) * time;
    FloatingPoint velocity3 = (controlPoints.at(3) - controlPoints.at(2)) * 3 * std::pow(time, 2.0);
    
    velocity.x = velocity1.x + velocity2.x + velocity3.x;
    velocity.y = velocity1.y + velocity2.y + velocity3.y;
    
    return velocity;
}
#endif

// Generates four control points for the Bezier Curve
#ifndef HAWK_IS_IMPLEMENTED
void Hawk::generateControlPoints(const int widthRange, const int heightRange)
{
        controlPoints.at(0) = position;
        controlPoints.at(1) = position * 2 - controlPoints.at(2);
        controlPoints.at(2) = {
            static_cast<double> (randomInt(0, SIM_RAND_MAX)) / (static_cast<double> (SIM_RAND_MAX/widthRange)),
            static_cast<double> (randomInt(0, SIM_RAND_MAX)) / (static_cast<double> (SIM_RAND_MAX/heightRange))
        };
        controlPoints.at(3) = {
            static_cast<double> (randomInt(0, SIM_RAND_MAX)) / (static_cast<double> (SIM_RAND_MAX/widthRange)),
            static_cast<double> (randomInt(0, SIM_RAND_MAX)) / (static_cast<double> (SIM_RAND_MAX/heightRange))
        };
}
#endif

#ifndef HAWK_IS_IMPLEMENTED
void Hawk::updateVelocity()
{
    FloatingPoint newVelocity;
    
    FloatingPoint avoidance = calculateAvoidance();
    FloatingPoint bezier = calculateBezierVelocity() * 0.00001;

    // Bezier Curves traverses for t in [0, 1]
    time += static_cast<double>(rand()) / static_cast<double>(SIM_RAND_MAX * 449.0);
    if (time >= 1){
        time = 0.0;
        generateControlPoints(WINDOW_WIDTH, WINDOW_HEIGHT);
    }
    
    newVelocity.x = velocity.x + avoidance.x + bezier.x;
    newVelocity.y = velocity.y + avoidance.y + bezier.y;

    if (magnitude(newVelocity) > MAX_SPEED) {
        newVelocity = (newVelocity / magnitude(newVelocity)) * MAX_SPEED;
    }
 
    velocity = newVelocity;
}
#endif

#ifndef HAWK_IS_IMPLEMENTED
void Hawk::makeFriendsAndFoes(vector<shared_ptr<Bird>> &birds)
{
    foes.clear();

    for (auto &other : birds) {
        bool isFoe = (
            (other.get() != this) &&
            (isInstanceOf<Hawk>(other.get())) &&
            (std::sqrt(std::pow(other->getPosition().x - position.x, 2)
                + std::pow(other->getPosition().y - position.y, 2)) < AVOID_RADIUS)
        );
        if (isFoe) {
            foes.push_back(other);
        }
    }
}
#endif

FloatingPoint Bird::calculateAvoidance()
{
    FloatingPoint avoidance {0.0, 0.0};
    
    for (auto &other : foes) {
        if (std::sqrt(std::pow(other->getPosition().x - position.x, 2)
                + std::pow(other->getPosition().y - position.y, 2)) < AVOID_RADIUS) {
            FloatingPoint difference = (position - other->position);
            difference = difference / magnitude(difference);
            avoidance.x = avoidance.x + difference.x;
            avoidance.y = avoidance.y + difference.y;
        }
    }

    return avoidance;
}

FloatingPoint Dove::calculateCohesion()
{
    FloatingPoint cohesion {0.0, 0.0};
    int friendCount = static_cast<int> (friends.size());

    if (friendCount > 0) {
        for (auto &other : friends) {
                cohesion.x = cohesion.x + other->getPosition().x;
                cohesion.y = cohesion.y + other->getPosition().y;
        }

        cohesion = cohesion / friendCount;
        cohesion = cohesion - position;
        cohesion = cohesion * 0.05;
    }
    
    return cohesion;
}

FloatingPoint Dove::calculateSeparation()
{
    FloatingPoint separation {0.0, 0.0};

    for (auto &other : friends) {
        FloatingPoint difference = (position - other->getPosition());
        difference = difference / magnitude(difference);
        separation.x = separation.x + difference.x;
        separation.y = separation.y + difference.y;
    } 
    
    return separation;
}

FloatingPoint Dove::calculateAlignment()
{
    FloatingPoint alignment {0.0, 0.0};

    for (auto &other : friends) {
            alignment.x = alignment.x + other->getVelocity().x;;
            alignment.y = alignment.y + other->getVelocity().y;
            alignment = alignment / magnitude(other->getVelocity());
    }
    
    return alignment;
}

// ---------------------------------
// ----------- SIMULATOR -----------
// ---------------------------------
Simulator::Simulator(AnimationWindow &window) : window{window}
{
    createBirds();
}

void Simulator::drawUniverse() const
{
    for (auto &bird : birds) {
        bird->draw(window);
    }
}

void Simulator::simulate()
{
    addBird();

    for (auto &bird : birds) {
        bird->makeFriendsAndFoes(birds);
        bird->update();
        boundBird(bird);
    }

    colorBirds();
}

// Update the color of the bird based on its flock so that birds in
// the same flock have the same color.
// BEGIN: T9

// getDoves returns a vector containing a shared pointer to every dove in the simulation.
vector<shared_ptr<Dove>> getDoves(vector<shared_ptr<Bird>> &birds)
{
    vector<shared_ptr<Dove>> doves;
    for (auto &bird : birds) {
        bool isDove = isInstanceOf<Dove>(bird.get());
        if (isDove) {
            auto dove = std::dynamic_pointer_cast<Dove>(bird);
            doves.push_back(dove);
        }
    }
    return doves;
}

// getFlock uses recursion to collect the flock to which a given dove belongs.
void getFlock(shared_ptr<Dove> dove, vector<shared_ptr<Dove>> &flock)
{
    if (std::find(flock.begin(), flock.end(), dove) != flock.end()) {
        return;
    }
    
    flock.push_back(dove);
    for (auto bird : dove->getFriends()) {
        auto friendDove = std::dynamic_pointer_cast<Dove>(bird);
        getFlock(friendDove, flock);
    }
}

void Simulator::colorBirds()
{
    vector<shared_ptr<Dove>> doves = getDoves(birds);

    for (auto& dove : doves) {
        vector<shared_ptr<Dove>> flock;
        getFlock(dove, flock);

        if (flock.size() > 1) {
            for (auto& dove : flock) {
                TDT4102::Color color{static_cast<unsigned char>(rand() % 256), static_cast<unsigned char>(rand() % 256), static_cast<unsigned char>(rand() % 256)};
                dove.get()->setColor(color);
            }
        }
    }
}
// END: T9

// Task T10: Implement functionallity to add birds during the simulation.
void Simulator::addBird()
{
// BEGIN: T10
    if (window.is_left_mouse_button_down() && window.is_key_down(KeyboardKey::D)) {
        Point point = window.get_mouse_coordinates();
        FloatingPoint bird_point{static_cast<double>(point.x), static_cast<double>(point.y)};
        createDove(bird_point, {2,2}, TDT4102::Color::alice_blue);
    }
// END: T10
}

// Motivates birds to stay on screen. 
void Simulator::boundBird(shared_ptr<Bird> &bird)
{
    FloatingPoint newVelocity = bird->getVelocity();

    if ((bird->getPosition().x < -200) && (bird->getVelocity().x < 0)) {
        newVelocity.x = -(newVelocity.x);
    } else if ((bird->getPosition().x > window.width() + 200) && (bird->getVelocity().x > 0)) {
        newVelocity.x = -(newVelocity.x);
    }

    if ((bird->getPosition().y < -200) && (bird->getVelocity().y < 0)) {
        newVelocity.y = -(newVelocity.y);
    } else if ((bird->getPosition().y > window.height() + 200) && (bird->getVelocity().y > 0)) {
        newVelocity.y = -(newVelocity.y);
    }

    bird->setVelocity(newVelocity);
}

void Simulator::createBirds()
{
    birds.clear();
    
    for (int i = 0; i < numDoves; i++) {
        FloatingPoint position {
            static_cast<double> (randomInt(0, SIM_RAND_MAX)) / (static_cast<double> (SIM_RAND_MAX/window.width())),
            static_cast<double> (randomInt(0, SIM_RAND_MAX)) / (static_cast<double> (SIM_RAND_MAX/window.height()))
        };
        FloatingPoint velocity {
            static_cast<double>(randomInt(SIM_RAND_MIN, SIM_RAND_MAX)) / static_cast<double>(SIM_RAND_MAX),
            static_cast<double>(randomInt(SIM_RAND_MIN, SIM_RAND_MAX)) / static_cast<double>(SIM_RAND_MAX)
        };
        Color color {
            static_cast<unsigned char> (randomInt(0, 255)),
            static_cast<unsigned char> (randomInt(0, 255)),
            static_cast<unsigned char> (randomInt(0, 255))
        };
        createDove(position, velocity, color);
    }
    
#ifndef HAWK_IS_IMPLEMENTED
    for (int i = 0; i < numHawks; i++) {
        FloatingPoint position {
            static_cast<double> (rand()) / (static_cast<double> (SIM_RAND_MAX/window.width())),
            static_cast<double> (rand()) / (static_cast<double> (SIM_RAND_MAX/window.height()))
        };
        FloatingPoint velocity {
            static_cast<double> (randomInt(-1, 1)),
            static_cast<double> (randomInt(-1, 1))
        };
        createHawk(position, velocity);
    }
#endif
}

void Simulator::createDove(FloatingPoint position, FloatingPoint velocity, Color color)
{
    shared_ptr<Bird> dove = make_shared<Dove>(position, velocity, color, 10.0);
    birds.push_back(dove);
}

#ifndef HAWK_IS_IMPLEMENTED
void Simulator::createHawk(FloatingPoint position, FloatingPoint velocity)
{
    shared_ptr<Bird> hawk = make_shared<Hawk>(position, velocity, Color::black, 20.0);
    birds.push_back(hawk);
}
#endif

void Simulator::toggleSimulation()
{
    simulationEnabled = !simulationEnabled;
    simulationReset = false;
}

void Simulator::resetSimulation()
{
    if (!(simulationReset || simulationEnabled)) {
        simulationEnabled = false;
        createBirds();
        simulationReset = true;
    }
}

void Simulator::applyConfiguration(int numDoves, int numHawks)
{
    if (!(simulationEnabled)) {
        simulationEnabled = false;
        simulationReset = true;
        this->numDoves = numDoves;
        this->numHawks = numHawks;
        createBirds();
    }
}

// ---------------------------------
// -------------- GUI --------------
// ---------------------------------
ToggleButton::ToggleButton() : Button({20, 5}, 200, 50, "Start")
{
    setCallback(bind(&ToggleButton::callback, this));
    setLabelColor(Color::sea_shell);
    setButtonColor(Color::sea_green);
    setButtonColorHover(Color::gray);
    setButtonColorActive(Color::gray);
}

ToggleButton::~ToggleButton() {}

void ToggleButton::callback()
{
    ToggleButton::sim->toggleSimulation();
    if (sim->simulationEnabled) {
        setButtonColor(Color::brown);
        setLabel("Stop");
    } else {
        setButtonColor(Color::sea_green);
        setLabel("Start");
    }
}

void ToggleButton::setSimulator(Simulator* const _sim)
{
    sim = _sim;
}

Simulator* ToggleButton::sim = nullptr;

ResetButton::ResetButton () : Button({220, 5}, 200, 50, "Reset")
{
    setCallback(ResetButton::callback);
    setLabelColor(Color::sea_shell);
    setButtonColor(Color::chocolate);
    setButtonColorHover(Color::gray);
    setButtonColorActive(Color::gray); 
}

ResetButton::~ResetButton() {}

// Task T4: Reset the simulation by calling resetSimulation
// on the Simulator instance in ResetButton.
void ResetButton::callback()
{
// BEGIN: T4
    sim->resetSimulation();
// END: T4
}

void ResetButton::setSimulator(Simulator* const _sim)
{
    sim = _sim;
}

Simulator* ResetButton::sim = nullptr;
