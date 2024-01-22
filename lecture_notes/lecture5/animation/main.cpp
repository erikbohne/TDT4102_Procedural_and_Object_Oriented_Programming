#include "std_lib_facilities.h"
#include "AnimationWindow.h"

int main() {
    TDT4102::AnimationWindow window;
    TDT4102::Point location = {100, 100};

    while(!window.should_close()) {
        window.next_frame();
        location.x++;
        window.draw_text(location, "Good morning");
    }
    return 0;
}

