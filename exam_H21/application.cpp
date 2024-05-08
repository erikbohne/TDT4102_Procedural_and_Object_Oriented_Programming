#include "application.h"

// Task A1: Loading a program from a file
//
// Implement the function Application::load_program() to read the
// contents of the file given in the parameter file_name and return
// its contents as a string. Make sure to include the whitespace from
// the file in the string. This makes it possible to load a program
// from a file to the Control script-window in the
// application. Some test-programs have been included in the
// handout-code. You can use these to test this function if you don't
// want/have time to make your own test cases. Make sure to handle
// potential problems with opening the file
// appropriately.
string Application::load_program(string file_name)
{
  // BEGIN: A1
  //
  // Write your answer to assignment A1 here, between the // BEGIN: A1
  // and // END: A1 comments. You should remove any code that is
  // already there and replace it with your own.

    ifstream file(file_name);
    if (file.is_open()) {
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    } else {
        throw runtime_error("Failed to open file: " + file_name);
    }

  // END: A1
}

// Task A2: Saving a program to a file
//
// Implement the function Application::save_program() to write
// the value of the string parameter contents to the file with the
// name given as the parameter file_name. This makes it possible to
// save the current script from the Control script-window to a
// file. Make sure to handle potential problems with opening the file
// appropriately.
void Application::save_program(string file_name, string contents)
{
  // BEGIN: A2
  //
  // Write your answer to assignment A2 here, between the // BEGIN: A2
  // and // END: A2 comments. You should remove any code that is
  // already there and replace it with your own.

    ofstream file(file_name);
    if (file.is_open()) {
        file << contents;
        file.close();
    } else {
        throw runtime_error("Failed to open file: " + file_name);
    }

  // END: A2
}

// Task A3: Checking if a string is a number
// 
// Implement the function Application::is_int() to check if a string
// is an int. The function should return true if the input can be converted
// to an integer and false otherwise.
bool Application::is_int(const string& s)
{
  // BEGIN: A3
  //
  // Write your answer to assignment A3 here, between the // BEGIN: A3
  // and // END: A3 comments. You should remove any code that is
  // already there and replace it with your own.

    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;

  // END: A3

}

// |
// | END OF ASSIGNMENTS
// |

// Callback functions
void Application::cb_btn_run_program() {
    if (is_int(in_execution_speed.getText())) {
        step_delay = 60/stoi(in_execution_speed.getText());
    }
    program_stream = istringstream(in_program.getText());
    out_execution_trace.setText("");
}

void Application::cb_btn_load_program() {
    in_program.setText(load_program("programs/prog1.txt"));
}

void Application::cb_btn_save_program() {
    save_program("programs/progNew.txt", in_program.getText());
}

// The main loop of the program
void Application::run() {
    string command;
    int counter = 0;
    while(!window.should_close()) {
        if (counter > step_delay) {
            getline(program_stream, command);
            if (command != "") {
                interpreter.execute_instruction(istringstream(command));
                out_execution_trace.setText(out_execution_trace.getText() + command + "\n");
                btn_run_program.setVisible(false);
            } else {
                btn_run_program.setVisible(true);
            }
            counter = 0;
        }

        grid.draw_universe();
        window.next_frame();
        counter++;
    }
}


Application::Application() 
    : window(50, 50, 1024, 768, "Robot commander"),
    grid{window, 10, 10, 650, 650, 1, 1},
    interpreter{grid},
    btn_run_program(TDT4102::Point{700, 230}, 300, 50, "Run program"),
    btn_load_program(TDT4102::Point{700, 280}, 300, 50, "Load program from file"),
    btn_save_program(TDT4102::Point{700, 330}, 300, 50, "Save program to file"),
    in_program(TDT4102::Point{700, 0}, 300, 230, ""), 
    in_execution_speed(TDT4102::Point{700, 420}, 300, 30, "Frames per second"),
    out_execution_trace(TDT4102::Point{700, 480}, 300, 230, "Execution trace")

{
    window.add(btn_run_program);
    window.add(btn_load_program);
    window.add(btn_save_program);

    window.add(in_execution_speed);
    window.add(in_program);
    window.add(out_execution_trace);
    
    in_program.setText("make_grid     6     6\n"
                    "make_robot    bob   2      2 green\n"
                    "make_robot    alice 4      4 blue\n"
                    "move_robot    bob   2      3\n"
                    "move_robot    alice 4      5\n"
                    "recolor_robot alice yellow\n"
                    "rename_robot  bob   roy\n"
                    "move_robot    roy 5      5\n"
                    "delete_robot  roy\n"
                    "delete_robot  alice\n");

	btn_run_program.setCallback(std::bind(&Application::cb_btn_run_program,this));
    btn_load_program.setCallback(std::bind(&Application::cb_btn_load_program,this));
	btn_save_program.setCallback(std::bind(&Application::cb_btn_save_program,this));
}