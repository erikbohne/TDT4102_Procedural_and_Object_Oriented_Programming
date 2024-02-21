#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "bouncingBall.h"

constexpr Point BOUNCE_WINDOW_TOP_LEFT{50, 50};
constexpr int BOUNCE_WINDOW_WIDTH{800}; 
constexpr int BOUNCE_WINDOW_HEIGHT{500};

std::map<int, Color> color_map = {
    {1, Color::red},
    {2, Color::green},
    {3, Color::blue},
    {4, Color::yellow}
};

void bouncingBall() {
    AnimationWindow window{BOUNCE_WINDOW_TOP_LEFT.x, BOUNCE_WINDOW_TOP_LEFT.y, 
                           BOUNCE_WINDOW_WIDTH, BOUNCE_WINDOW_HEIGHT, "Bouncing ball"};
    
    const int radius{30};
    int alpha{1};
    int velocity{2};
    Color colour_up{Color::blue};
    Color colour_down{Color::blue};
    int x{0};
    int y{360};
    int increment_x{0};
    int increment_y{0};
    int count_bounce_top{0};
    int count_bounce_bottom{0};
    int count_num_passes{0};

    // read from configuration file
    std::filesystem::path config_file{"konfigurasjon.txt"};
    std::ifstream is{config_file};
    BouncingBallConfig slow, fast;
    is >> slow >> fast;

    // initialise the run
    velocity = fast.velocity;
    colour_up = color_map.at(fast.color_up);
    colour_down = color_map.at(fast.color_down);

    while (!window.should_close()) {
        // determine increments based on the velocity
        increment_x = velocity * cos(alpha);
        increment_y = velocity * sin(alpha);

        // movement i x-direction
        if ((increment_x + x) > window.width()) {
            // reached right side - wrap around to the leftmost
            x = 0;
            // increment counter which counts number of full left-to-right passes
            count_num_passes++;
            // alternate between slow and fast configuration every fifth pass
            if (count_num_passes % 5 == 0) {
                // change configuration
                // update both velcity and colors
                if (velocity == slow.velocity) {
                    velocity = fast.velocity;
                    colour_up = color_map.at(fast.color_up);
                    colour_down = color_map.at(fast.color_down);
                } else {
                    velocity = slow.velocity;
                    colour_up = color_map.at(slow.color_up);
                    colour_down = color_map.at(slow.color_down);
                }
    
            }
        } else {
            // moving rightwards
            x += increment_x;
        }

        // movement i y-direction
        if ((y + increment_y) < 0) {
            // reached top - bounce back
            count_bounce_top++;
            alpha = -alpha;
        } else if ((y + increment_y) > BOUNCE_WINDOW_HEIGHT) {
            // reached bottom - bounce back
            count_bounce_bottom++;
            alpha = -alpha;
        }
        // move upwards
        y += increment_y;

        window.draw_circle({x, y}, radius, colour_down);
        window.next_frame();
    }
}

std::istream& operator>>(std::istream& is, BouncingBallConfig& cfg) {
    int up, down, vel;
    is >> up >> down >> vel;
    cfg = {up, down, vel};
    return is;
}

