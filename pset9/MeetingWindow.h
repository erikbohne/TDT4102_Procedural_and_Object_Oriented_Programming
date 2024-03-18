#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include <string>

class MeetingWindow : public TDT4102::AnimationWindow {
    private:
        static constexpr int pad = 10;
        static constexpr int btnW = 100;
        static constexpr int btnH = 50;
        static constexpr int fldW = 10;
        static constexpr int fldH = 10;

        int x;
        int y;
        int width;
        int height;
        std::string title;

        TDT4102::Button quitBtn; 
    public:
        MeetingWindow(int x, int y, int w, int h, const string& title) :
            TDT4102::AnimationWindow(x, y, w, h, title),
            quitBtn({400, 0}, btnW, btnH, "Quit"),
            x(x), y(y), width(w), height(h), title(title) 
            {
                add(quitBtn);
                quitBtn.setCallback(std::bind(&MeetingWindow::cb_quit, this));
            };

        void cb_quit() { close(); };
};