#ifndef ALL_H_4KNCEGJI
#define ALL_H_4KNCEGJI


#include <AnimationWindow.h>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>
#include <widgets/Button.h>
#include <cmath>


static constexpr int EMPTY_TILE_ID = -1;

static constexpr int WORLD_WIDTH  = 6;
static constexpr int WORLD_HEIGHT = 6;


constexpr static int TILE_SIZE = 64;

constexpr static int TILE_WIDTH = TILE_SIZE / 2;
constexpr static int TILE_HEIGHT = TILE_SIZE / 4;


// Forward declarations
class TileSelector;
class DecrementButton;
class SaveButton;
class OverlayButton;
class CameraController;
class Camera;
class Context;
class DebouncedInput;
class Level;
class LevelLoader;
class LevelWriter;
class TileRenderer;
class QuadRenderer;
class LevelRenderer;
class PlacementOverlay;
class WalkableOverlay;
class Player;
class TilePool;
class TileLoader;
class TileSelector;
struct TilePreview;
struct RenderUtils;
struct Region;
struct CoordinateSystem;
struct PlayerControllable;
struct Tile;
struct TileDescriptor;


static bool show_walkable_overlay = false;


struct Tile
{
    Tile(int id, bool walkable, const std::filesystem::path tile_image_path);

    Tile(const Tile &other);
    Tile &operator=(const Tile &other);

    Tile(Tile &&rhs);
    Tile &operator=(Tile &&rhs);

    bool has_image() const noexcept;


    int id;
    bool walkable;
    std::shared_ptr<TDT4102::Image> image;
};


class IncrementButton : public TDT4102::Button {
public:

    IncrementButton ();

    ~IncrementButton() {}

    static void callback();

    static void setTileSelector(TileSelector * const _ts);

private:
    static TileSelector *ts;
};




class DecrementButton : public TDT4102::Button {
public:

    DecrementButton ();

    void test() ;

    ~DecrementButton() ;

    static void callback() ;

    static void setTileSelector(TileSelector * const _ts) ;



private:
    static TileSelector *ts;
};



class SaveButton : public TDT4102::Button {
public:
    SaveButton();

    ~SaveButton() ;

    static void callback() ;

    static void setLevel(const Level *lvl) ;


private:
    static const Level *level;
};


class OverlayButton : public TDT4102::Button
{
public:
    OverlayButton() : TDT4102::Button(OverlayButton::render_location, 100, 40, "Overlay") {
        setCallback(OverlayButton::callback);
    }

    static void callback() {
        show_walkable_overlay = ! show_walkable_overlay;
    }

private:
    static constexpr TDT4102::Point render_location{125, 258};
};


struct TilePreview
{
    static constexpr TDT4102::Point render_location{46,65};
    static void render(TDT4102::AnimationWindow &window, std::optional<Tile> &tile);
};





class CameraController {
public:
    CameraController(int speed);

    void setScrollSpeed(int speed) noexcept;

    void handleInput(Context &ctx);

private:
    int m_scrollSpeed = 1;
};




/*! \class Camera
 *  \brief Handles panning around by giving offset vectors.
 */
class Camera
{
public:
    Camera();
    explicit Camera(TDT4102::Point initialPoint);

    void focusOn(TDT4102::Point focus, int screenWidth, int screenHeight) noexcept;

    void translateX(int delta) noexcept;
    void translateY(int delta) noexcept;

    const TDT4102::Point getPosition() const noexcept;
    const TDT4102::Point getCorrectionVector() const noexcept;

    const std::array<float, 4> &getProjectionMatrix() const noexcept;

    const std::array<float, 4> &getInverseProjectionMatrix() const noexcept;


protected:
    TDT4102::Point position;

    static constexpr std::array<float, 4> projMatrix = {
        TILE_WIDTH, -TILE_WIDTH,
        TILE_HEIGHT, TILE_HEIGHT
    };


    static constexpr std::array<float, 4> inv_projMatrix = [](){

        float w = 1.0f / (2.0f * static_cast<float>(TILE_WIDTH));
        float h = 1.0f / (2.0f * static_cast<float>(TILE_HEIGHT));

        return std::array<float, 4>{
              w, h,
            - w, h};
    }();
};











/*! \class Context
 *  \brief Brief class description
 *
 *  Detailed description
 */

class Context
{
public:
    Context(TDT4102::AnimationWindow *window, std::shared_ptr<Camera> cam);

    Camera &getCamera() noexcept;

    const Camera &getCamera() const noexcept;

    TDT4102::AnimationWindow &getWindow() noexcept;

    const TDT4102::AnimationWindow &getWindow() const noexcept;

private:
    std::shared_ptr<Camera> cam;

    // BE CAREFUL, the lifetime of the context should be contained within that of the AnimationWindow
    // TODO: Fix this
    TDT4102::AnimationWindow *window;
};


TDT4102::Point matmul2(const std::array<float, 4> &matrix, TDT4102::Point point);


struct Region
{
    Region(const TDT4102::Point p1, const TDT4102::Point p2);

    TDT4102::Point begin;
    TDT4102::Point end;
};

class Level
{
public:
    Level();
    Level(unsigned int _width, unsigned int _height) : width{_width}, height{_height} {
        tiles.resize(width * height, -1);
        walkable.resize(width * height, false);

        std::fill(tiles.begin(), tiles.end(), -1);
    }

    bool is_walkable(const TDT4102::Point coordinate) const;
    int tile_at(const TDT4102::Point coordinate) const;
    void set_tile_at(const TDT4102::Point coordinate, const int tile);
    void set_tile_region(TDT4102::Point begin, TDT4102::Point end, int tile, bool walkable);
    void set_walkable_at(const TDT4102::Point coordinate, const bool walkable);

    unsigned int get_width() const noexcept;
    unsigned int get_height() const noexcept;

private:
    unsigned int width = 1;
    unsigned int height = 1;

    std::vector<int> tiles = {0};
    std::vector<bool> walkable = {false};

    friend class LevelLoader;
    friend class LevelWriter;
};




class LevelLoader {
public:
    static Level load(std::filesystem::path path);

private:
    LevelLoader();
};

class LevelWriter {
public:
    static bool write(std::filesystem::path path, const Level &level);

private:
    LevelWriter();
};





class TileRenderer
{
public:
    static void render(Context &ctx, const Tile &tile, TDT4102::Point anchor);
};

class QuadRenderer
{
public:
    static void render(Context &ctx, TDT4102::Point anchor, TDT4102::Color color);
};

struct CoordinateSystem {
    static TDT4102::Point to_screen(const Context &ctx, TDT4102::Point grid_point);
    static TDT4102::Point to_grid(const Context &ctx, TDT4102::Point screen_coordinate);
};

class LevelRenderer
{
public:
    LevelRenderer(Context &ctx, Level &lvl, TilePool &pool);

    void render() const;
private:
    Context &ctx;
    Level &lvl;
    TilePool &pool;

};

class PlacementOverlay {
public:
    PlacementOverlay(Context &ctx);

    void reset_tile();

    void render();

    void set_begin(TDT4102::Point _begin);
    void set_end(TDT4102::Point _end);

    void set_tile(Tile _tile);
    void set_tile(std::optional<Tile> _tile);

private:
    Context &ctx;

    Tile active_tile{-1, false, ""};

    TDT4102::Point begin;
    TDT4102::Point end;
};

class WalkableOverlay {
public:
    WalkableOverlay(const Level &lvl);

    void render(Context &ctx);
private:
    const Level &lvl;
};





TDT4102::Point operator+(const TDT4102::Point p1, const TDT4102::Point p2);

TDT4102::Point operator-(const TDT4102::Point p1, const TDT4102::Point p2);
TDT4102::Point operator-(const TDT4102::Point &p1);


std::ostream &operator<<(std::ostream &stream, const TDT4102::Point &point);

std::istream &operator>>(std::istream &stream, Tile &tile);





struct PlayerControllable
{
    TDT4102::Point position;

    int max_move_length = 1;

    bool canMoveTo(TDT4102::Point new_position, const Level &lvl);

    void moveTo(TDT4102::Point new_position, const Level &lvl);
};

class Player : public PlayerControllable
{
public:

    Player() = delete;

    explicit Player(std::filesystem::path spritePath);

    void draw(TDT4102::AnimationWindow &window, const Context &ctx);

private:
    TDT4102::Image sprite;
};





struct TileDescriptor
{
    int id;
    std::string filename;
    bool walkable;
};

class TilePool
{
public:
    using KeyType = int;

    std::optional<Tile> get_tile(KeyType key);

    const std::vector<int> &get_tile_ids() const;

    bool add_tile(const KeyType &key, Tile tile);

private:
    std::unordered_map<KeyType, Tile> tile_pool;
    std::vector<int> tile_ids;

    friend class TileLoader;
};


class TileLoader
{
public:
    static TilePool load(const std::filesystem::path descriptor_file_path);
    static TileDescriptor process_line(std::string line);

private:
    TileLoader() = delete;
};





class TileSelector
{
public:

    TileSelector() = delete;

    TileSelector(int min, int max) : current_tile_id{min}, min{min}, max{max} { }

    TileSelector(const TileSelector &ts) :
        current_tile_id{ts.current_tile_id}, min{ts.min}, max{ts.max}
    { }

    TileSelector &operator=(const TileSelector &ts) {
        current_tile_id = ts.current_tile_id;
        min = ts.min;
        max = ts.max;

        return *this;
    }

    ~TileSelector() {}

    // TASK
    // Pressing `0`, `+` or `-` will update the currently selected tile.
    // Before doing this task, these button presses are repeated as long as the
    // keys are held. When the game is refreshing and taking input repeatedly,
    // once each frame, you are going to find difficulties in precisely
    // selecting the tiles you want.
    //
    // This task is asking you to keep track of whether this instance of
    // TileSelector sees the "initial" key press or if the key has been held,
    // meaning it has been "down" for more than 1 frame.
    //
    // The current state of the `0`, `+` and `-` keys are given below. Extend
    // the class to store three boolean values for each key respectively and
    // make sure the `reset`, `increment`, and `decrement` functions are called
    // only for initial key presses.

    void handle_input(TDT4102::AnimationWindow &window) {
        auto key_0 =  window.is_key_down(KeyboardKey::KEY_0);
        auto plus  =  window.is_key_down(KeyboardKey::PLUS);
        auto minus =  window.is_key_down(KeyboardKey::MINUS);

        auto initial_press_zero = !  keys_held[0] && key_0;
        auto initial_press_plus = !  keys_held[1] && plus;
        auto initial_press_minus = ! keys_held[2]  && minus;

        keys_held[0] = key_0;
        keys_held[1] = plus;
        keys_held[2] = minus;

        if (initial_press_zero) {
            reset();
        }

        if (initial_press_plus) {
            increment();
        }

        if (initial_press_minus) {
            decrement();
        }
    }

    int get_current() const noexcept
    {
        return current_tile_id;
    }


    // TASK T.1
    // Write an increment function that increases `current_tile_id` by one.
    // It should not, however, exceed `max`.
    void increment() noexcept {
        current_tile_id = std::min(current_tile_id + 1, max);
    }


    // TASK T.2
    // Write an increment function that decreases `current_tile_id` by one.
    // It should not, however, be lower than `min`.
    void decrement() noexcept {
        current_tile_id = std::max(current_tile_id - 1, min);
    }

    void reset() noexcept {
        current_tile_id = min;
    }

private:
    int current_tile_id;
    int min;
    int max;

    bool keys_held[3]{false};
};


#endif

