#pragma once

#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "robot_grid.h"
#include "interpreter.h"


class Application {
private:
    AnimationWindow window;
    RobotGrid grid;
    Interpreter interpreter;

    // Window widgets
    TDT4102::Button btn_run_program;
    TDT4102::Button btn_load_program;
    TDT4102::Button btn_save_program;
    TDT4102::TextInput in_program;
    TDT4102::TextInput out_execution_trace;
    TDT4102::TextInput in_execution_speed;

    int step_delay = 60;
    istringstream program_stream;

    // Private functions
    void execute_program(string stream);
    string load_program(string file_name);
    void save_program(string file_name, string contents);
    bool is_int(const string& s);

    // Callback functions
    void cb_btn_run_program();
    void cb_btn_load_program();
    void cb_btn_save_program();

public:
    Application();
    void run();
};
