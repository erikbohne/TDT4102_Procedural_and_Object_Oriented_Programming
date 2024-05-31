#include "day.h"
#include "util.h"
#include <sstream>
#include <stdexcept>
#include <string>

Day::Day(AnimationWindow &window, int xpos, int ypos, string city, int day,
         double temp, double wind_dir, double wind_speed, string symbol,
         double precip_amount)
    : window{window}, xpos{xpos}, ypos{ypos}, city{city}, day{day}, temp{temp},
      wind_dir{wind_dir},
      wind_speed(wind_speed), symbol{window, xpos, ypos + 30, symbol},
      precip_amount{precip_amount}
{
}

// Task D1: Rendering a day
//
// Now, we use the helper functions defined previously to render a
// day of the weather forecast. To add text to the forecast, the function
// draw_text(Point pos, string value) is provided. Where applicable,
// round floating point numbers to one decimal and make sure that the
// appropriate unit is appended. For positioning the text, use the
// variables xpos and ypos which holds the coordinates of the upper
// right corner of a day. The list below tells you which information
// should be present in the forecast, the text's relative y-offset and
// the variable of the Day class where the information is found. Use
// the variables xpos and ypos together with the relative y-offsets
// to construct the Point parameter pos of the draw_text
// function.
//
//
//  - The day of the week. Y-position: 20, variable: day
//  - The temperature. Y-position: 100, variable temp
//  - The wind speed and direction: Y-position: 120, variables: wind_speed, wind_dir
//  - The amount of precipitation: Y-position: 140, variable: precip_amount
void Day::show_day()
{
  // BEGIN: D1

  draw_text({xpos,ypos+20}, format_weekday(day));
  draw_text({xpos,ypos+100}, format_value(temp, 1, Unit::UNIT_DC));
  draw_text({xpos,ypos+120}, format_value(wind_speed, 1, Unit::UNIT_MS) + " " + format_wind_dir(wind_dir));
  draw_text({xpos,ypos+140}, format_value(precip_amount, 1, Unit::UNIT_MM));

  // END: D1

  // Draws the weather symbol implemented in tasks R1-R3. Don't remove
  // this line
  symbol.draw_image();
}

// |
// | END OF ASSIGNMENTS
// |

void Day::draw_text(Point pos, string text)
{
  window.draw_text(pos, text, TDT4102::Color::black, 10);
}

