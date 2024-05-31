#include "Tasks.h"
#include <AnimationWindow.h>
#include <algorithm>
#include <atomic>
#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <type_traits>
#include <widgets/Button.h>

// Task T1: Getting the width
//
// Implement the code for getting the private  field in the  class.
unsigned int Level::get_width() const noexcept {
// BEGIN: T1
//
// Write your answer to assignment T1 here, between the // BEGIN: T1
// and // END: T1 comments. You should remove any code that is
// already there and replace it with your own.
    return width;
// END: T1
}


// Task T2: Getting the height
//
// Implement the code for getting the private  field in the  class.
unsigned int Level::get_height() const noexcept {
// BEGIN: T2
//
// Write your answer to assignment T2 here, between the // BEGIN: T2
// and // END: T2 comments. You should remove any code that is
// already there and replace it with your own.
    return height;
// END: T2
}


// Task T3: Checking whether a Tile has an image
//
// %
bool Tile::has_image() const noexcept
{
// BEGIN: T3
//
// Write your answer to assignment T3 here, between the // BEGIN: T3
// and // END: T3 comments. You should remove any code that is
// already there and replace it with your own.
    if (image == nullptr) {
        return false;
    } else { 
        return true;
    }
// END: T3
}


// TASK: Region Constructor
// Task T4:  constructor
//
// The purpose of the Region struct is to represent a multi-tile area. It has two fields:  and end, both of which are instances of . The constructor should assign the lowest x- and y-values among the two points to the  field, and the highest x- and y-values to the  field.
//
// Write an implementation of this constructor.
Region::Region(const TDT4102::Point p1, const TDT4102::Point p2)
{
// BEGIN: T4
//
// Write your answer to assignment T4 here, between the // BEGIN: T4
// and // END: T4 comments. You should remove any code that is
// already there and replace it with your own.
    if (p1.x > p2.x) {
        begin.x = p1.x;
        end.x = p2.x;
    } else {
        end.x = p1.x;
        begin.x = p2.x; 
    }

    if (p1.y > p2.y) {
        begin.y = p1.y;
        end.y = p2.y;
    } else {
        end.y = p1.y;
        begin.y = p2.y; 
    }

// END: T4
}

// Task T5: Moving the camera
//
// Up until this point you've been staring at the same region of the level. We would like the camera to be functional so that we can
// pan the camera around. Using the  object, get references to the instances of  and  and use them
// to  get keyboard input and  move the camera based on said input. A description of how the function should work follows:
void CameraController::handleInput(Context &ctx) {
    TDT4102::AnimationWindow &window = ctx.getWindow();
    Camera &camera = ctx.getCamera();

    int scrollSpeed =
        window.is_key_down(KeyboardKey::LEFT_SHIFT) ?
            m_scrollSpeed * 4 : m_scrollSpeed;


// BEGIN: T5
//
// Write your answer to assignment T5 here, between the // BEGIN: T5
// and // END: T5 comments. You should remove any code that is
// already there and replace it with your own.
    if (window.is_key_down(KeyboardKey::W)) {
        camera.translateY(-scrollSpeed);
    }
    if (window.is_key_down(KeyboardKey::S)) {
        camera.translateY(scrollSpeed);
    }
    if (window.is_key_down(KeyboardKey::A)) {
        camera.translateX(-scrollSpeed);
    }
    if (window.is_key_down(KeyboardKey::D)) {
        camera.translateX(scrollSpeed);
    }
// END: T5
}



// Task T6: Setting one tile
//
// The coordinate conforms to the internal coordinate representation as shown in the end of this documnt (p. 8). A coordinate $(x,y)$ in a world that is $W
void Level::set_tile_at(TDT4102::Point coordinate, int tile)
{
// BEGIN: T6
//
// Write your answer to assignment T6 here, between the // BEGIN: T6
// and // END: T6 comments. You should remove any code that is
// already there and replace it with your own.
    int index = coordinate.y * width + coordinate.x;

    if (index < tiles.size()) {
        tiles.at(index) = tile;
    }
// END: T6
}


// Task T7: Setting a cell to be walkable
//
// Write the function so that the  vector in the  set the walkable flag for a selected cell.
void Level::set_walkable_at(TDT4102::Point coordinate, bool walkable)
{
// BEGIN: T7
//
// Write your answer to assignment T7 here, between the // BEGIN: T7
// and // END: T7 comments. You should remove any code that is
// already there and replace it with your own.
    unsigned int index = coordinate.y * width + coordinate.x;

    if (index < tiles.size()) {
        this->walkable.at(index) = walkable;
    }
// END: T7
}


// Task T8: Placement overlay
//
// The placement overlay should already be visible. The tile following your cursor is the placement overlay. When you hold the left mouse button, however, you will notice that the tile stays behind. This is because the placement overlay is supposed to show you the region you have selected.
//
// Extend the function to render the same tile over the region spanned by the two fields,  and .
void PlacementOverlay::render()
{
    bool has_image = active_tile.has_image();

    auto get_cell_coordinate = [&] (int x, int y) {
        return CoordinateSystem::to_screen(ctx, {x,y});
    };

// BEGIN: T8
//
// Write your answer to assignment T8 here, between the // BEGIN: T8
// and // END: T8 comments. You should remove any code that is
// already there and replace it with your own.
    Region r{begin, end};

    for (int x = r.begin.x; x <= r.end.x; x++) {
        for (int y = r.begin.y; y <= r.end.y; y++) {
            auto anchor = get_cell_coordinate(x,y);

            if ( has_image ) {
                TileRenderer::render(ctx, active_tile, anchor);
            } else {
                anchor = anchor + TDT4102::Point{0, TILE_WIDTH};
                QuadRenderer::render(ctx, anchor, TDT4102::Color{255,255,255,255});
            }
        }
    }

// END: T8
}


// Task T9: Updating a region
//
// Given the two points,  and , apply the previously implemented
void Level::set_tile_region(TDT4102::Point begin, TDT4102::Point end, int tile, bool walkable)
{
// BEGIN: T9
//
// Write your answer to assignment T9 here, between the // BEGIN: T9
// and // END: T9 comments. You should remove any code that is
// already there and replace it with your own.
    Region r{begin, end};

    for (int x = r.begin.x; x <= r.end.x; x++) {
        for (int y = r.begin.y; y <= r.end.y; y++) {
            set_tile_at({x,y}, tile);
            set_walkable_at({x,y}, walkable);
        }
    }
// END: T9
}

Tile::Tile(const Tile &other) : id{other.id}, walkable{other.walkable}, image{other.image} {}

// TASK: Copy assignment operator
// Task T10: Copy Assignment Operator
//
// Write the copy assignment operator such that all fields in  are copied from an existing instance.
Tile &Tile::operator=(const Tile &other)
{
// BEGIN: T10
//
// Write your answer to assignment T10 here, between the // BEGIN: T10
// and // END: T10 comments. You should remove any code that is
// already there and replace it with your own.
    this->id = other.id;
    this->walkable = other.walkable;
    this->image = other.image;

    return *this;
// END: T10
}

// Task T11: Reading a single tile descriptor
//
// Write the function
TileDescriptor TileLoader::process_line(std::string line)
{
// BEGIN: T11
//
// Write your answer to assignment T11 here, between the // BEGIN: T11
// and // END: T11 comments. You should remove any code that is
// already there and replace it with your own.

    std::istringstream ss{line};

    int id;
    std::string img_path;
    bool walkable;

    ss >> id >> img_path >> walkable;

    return TileDescriptor{id, img_path, walkable};
// END: T11
}

// Task T12: Dynamic Loading of Tiles
//
// In the  directory, there is a file named
TilePool TileLoader::load(const std::filesystem::path descriptor_file_path)
{

    auto imgpool = TilePool{};

// BEGIN: T12
//
// Write your answer to assignment T12 here, between the // BEGIN: T12
// and // END: T12 comments. You should remove any code that is
// already there and replace it with your own.
    imgpool.add_tile(0, Tile(0, false, "tiles/house_00.png"));
    imgpool.add_tile(1, Tile(1, false, "tiles/house_01.png"));
    imgpool.add_tile(2, Tile(2, false, "tiles/house_02.png"));
    imgpool.add_tile(50, Tile(50, false, "tiles/house_50.png"));

    // imgpool.tile_ids.push_back(0);
    // imgpool.tile_ids.push_back(1);
    // imgpool.tile_ids.push_back(2);
    // imgpool.tile_ids.push_back(50);

    return imgpool;
// END: T12
}

// Task T13: Saving the level
//
// Implement a save function for a  instance by open a file stream, throw an error if the file failed to open, write the width and height header, write the tile ID block, write the walkable flag block.
//
// NOTE: The beginning of each line is always an alphanumeric character, i.e., there should not be a tab at the beginning of a line.
bool LevelWriter::write(std::filesystem::path path, const Level &level)
{
    int width =  static_cast<int>(level.get_width());
    int height = static_cast<int>(level.get_height());

    auto tile_at = [&level] (int y, int x) {
        return level.tile_at({x,y});
    };

    auto walkable_at = [&level] (int y, int x) {
        return level.is_walkable({x,y});
    };

// BEGIN: T13
//
// Write your answer to assignment T13 here, between the // BEGIN: T13
// and // END: T13 comments. You should remove any code that is
// already there and replace it with your own.
    return false;
// END: T13
}



// ============================================================
// PROVIDED FUNCTIONS BEYOND THIS POINT
// ============================================================

CameraController::CameraController(int speed) : m_scrollSpeed{speed} {}

void CameraController::setScrollSpeed(int speed) noexcept {
    m_scrollSpeed = speed;
}

Camera::Camera() : position{0,0} {}
Camera::Camera(TDT4102::Point initialPoint) : position{initialPoint} {}

void Camera::focusOn(TDT4102::Point focus, int screenWidth, int screenHeight) noexcept {
    position.x = focus.x - screenWidth / 2;
    position.y = focus.x - screenHeight / 2;
}

void Camera::translateX(int delta) noexcept {
    position.x += delta;
}

void Camera::translateY(int delta) noexcept {
    position.y += delta;
}


const TDT4102::Point Camera::getPosition() const noexcept {
    return position;
}


const TDT4102::Point Camera::getCorrectionVector() const noexcept {
    return TDT4102::Point{-position.x, -position.y};
}


const std::array<float, 4> &Camera::getProjectionMatrix() const noexcept
{
    return Camera::projMatrix;
}

const std::array<float, 4> &Camera::getInverseProjectionMatrix() const noexcept
{
    return Camera::inv_projMatrix;
}


Context::Context(TDT4102::AnimationWindow *window, std::shared_ptr<Camera> cam) :
    cam{cam}, window{window} { }

Camera &Context::getCamera() noexcept {
    return *cam;
}


const Camera &Context::getCamera() const noexcept {
    return *cam;
}

TDT4102::AnimationWindow &Context::getWindow() noexcept {
    return *window;
}

const TDT4102::AnimationWindow &Context::getWindow() const noexcept {
    return *window;
}


TDT4102::Point matmul2(const std::array<float, 4> &matrix, TDT4102::Point point)
{
    TDT4102::Point result;

    result.x = static_cast<int>(
        std::floor(
        static_cast<float>(point.x) * matrix[0] +
        static_cast<float>(point.y) * matrix[1]
        )
    );


    result.y = static_cast<int>(
        std::floor(
        static_cast<float>(point.x) * matrix[2] +
        static_cast<float>(point.y) * matrix[3]
        )
    );

    return result;
}

Level::Level() : width{1}, height{1} {
    tiles.resize(1,-1);
    walkable.resize(1,false);
}

bool Level::is_walkable(const TDT4102::Point coordinate) const
{
    if ( coordinate.x >= 0 && coordinate.y >= 0 ) {
        unsigned int X = static_cast<unsigned int>(coordinate.x);
        unsigned int Y = static_cast<unsigned int>(coordinate.y);
        return walkable.at( Y * width + X);
    }
    return false;
}


int Level::tile_at(TDT4102::Point coordinate) const
{
    if ( coordinate.x >= 0 && coordinate.y >= 0 ) {
        unsigned int X = static_cast<unsigned int>(coordinate.x);
        unsigned int Y = static_cast<unsigned int>(coordinate.y);
        return tiles.at(Y * width + X);
    }

    return EMPTY_TILE_ID;
}

Level LevelLoader::load(std::filesystem::path path)
{
    std::ifstream level_file{path};


    if ( ! level_file.is_open() ) {
        throw std::runtime_error("ERROR -- LevelLoader: Could not open" + path.string());
    }

    std::string current_line;
    std::getline(level_file, current_line);
    std::istringstream ss{current_line};

    // Read level dimensions
    unsigned int width, height;
    ss >> width;
    ss >> height;

    Level result{width, height};

    std::getline(level_file, current_line);

    // Load tiles

    unsigned int index = 0;
    while ( current_line.find("END") == std::string::npos ) {

        ss.clear();
        ss.str(current_line);

        while ( ss.good() )
        {
            int tile = -1;
            ss >> tile;
            result.tiles.at(index++) = tile;
        }

        std::getline(level_file, current_line);
    }

    std::getline(level_file, current_line);

    index = 0;
    while ( current_line.find("END") == std::string::npos ) {
        ss.clear();
        ss.str(current_line);


        while ( ss.good() )
        {
            int walkable = 0;
            ss >> walkable;
            result.walkable.at(index++) = walkable > 0 ? true : false;
        }

        std::getline(level_file, current_line);
    }

    level_file.close();

    return result;
}


void TileRenderer::render(Context &ctx, const Tile &tile, TDT4102::Point anchor)
{

    auto &window = ctx.getWindow();

    if ( tile.image )
        window.draw_image(anchor, *tile.image);
}

void QuadRenderer::render(Context &ctx, TDT4102::Point anchor, TDT4102::Color color)
{
    std::array<TDT4102::Point, 4> quad;

    quad[0] = {anchor.x + TILE_WIDTH, anchor.y};
    quad[1] = {anchor.x + TILE_SIZE, anchor.y + TILE_HEIGHT};
    quad[2] = {anchor.x + TILE_WIDTH, anchor.y + TILE_HEIGHT * 2};
    quad[3] = {anchor.x, anchor.y + TILE_HEIGHT};

    ctx.getWindow().draw_quad(quad[0], quad[1], quad[2], quad[3], color);

    ctx.getWindow().draw_line(quad[0], quad[1], TDT4102::Color{255,0,0,255});
    ctx.getWindow().draw_line(quad[1], quad[2], TDT4102::Color{255,0,0,255});
    ctx.getWindow().draw_line(quad[2], quad[3], TDT4102::Color{255,0,0,255});
    ctx.getWindow().draw_line(quad[3], quad[0], TDT4102::Color{255,0,0,255});

}

LevelRenderer::LevelRenderer(Context &ctx, Level &lvl, TilePool &pool) : ctx{ctx}, lvl{lvl}, pool{pool}
{ }

void LevelRenderer::render() const
{
    const int width =  static_cast<int>(lvl.get_width());
    const int height = static_cast<int>(lvl.get_height());

    for ( int y = 0; y < height; y++ )
        for ( int x = 0; x < width; x++ )
        {
            const auto tile_id = lvl.tile_at({x,y});
            auto opt_tile = pool.get_tile(tile_id);

            const bool has_tile = opt_tile.has_value();

            auto render_position = CoordinateSystem::to_screen(ctx, TDT4102::Point{x,y});
            if ( has_tile && opt_tile->has_image() ) {
                TileRenderer::render(ctx, opt_tile.value(), render_position);
            }
            else {
                render_position.y += TILE_WIDTH;
                QuadRenderer::render(ctx, render_position, TDT4102::Color{255,255,255,255});
            }
        }
}

TDT4102::Point CoordinateSystem::to_screen(const Context &ctx, const TDT4102::Point grid_point)
{
    auto correction = ctx.getCamera().getCorrectionVector();

    return matmul2(ctx.getCamera().getProjectionMatrix(), grid_point) + correction;
}

TDT4102::Point CoordinateSystem::to_grid(const Context &ctx, const TDT4102::Point screen_coordinate)
{
    const Camera &cam = ctx.getCamera();
    const auto correction = cam.getCorrectionVector();

    auto adjusted_coordinate = screen_coordinate - correction - TDT4102::Point{TILE_WIDTH,TILE_WIDTH};

    TDT4102::Point inverse = matmul2(
            ctx.getCamera().getInverseProjectionMatrix(),
            adjusted_coordinate);

    return inverse;
}

// =======================================================
// ================== Placement Overlay ==================
// =======================================================
PlacementOverlay::PlacementOverlay(Context &ctx) : ctx{ctx} {}

void PlacementOverlay::reset_tile()
{
    active_tile = Tile(-1, false, "");
}




void PlacementOverlay::set_tile(Tile _tile)
{
    active_tile = _tile;
}

void PlacementOverlay::set_tile(std::optional<Tile> _tile)
{
    if ( _tile.has_value() )
        set_tile(_tile.value() );
}


void PlacementOverlay::set_begin(TDT4102::Point _begin)
{
    begin = _begin;
}
void PlacementOverlay::set_end(TDT4102::Point _end)
{
    end = _end;
}


WalkableOverlay::WalkableOverlay(const Level &lvl) : lvl{lvl}
{ }


void WalkableOverlay::render(Context &ctx)
{

    auto render_position = [&ctx] (int grid_x, int grid_y) {
        return CoordinateSystem::to_screen(
                ctx, TDT4102::Point{grid_x,grid_y})
            + TDT4102::Point{0, TILE_WIDTH};
    };

    TDT4102::Color overlay_color{255,0,0,255};
    const int width =  static_cast<int>(lvl.get_width());
    const int height = static_cast<int>(lvl.get_height());

    for ( int y = 0; y < height; y++ )
        for ( int x = 0; x < width; x++ )
        {
            if ( lvl.is_walkable({x,y}) ) {
                overlay_color = TDT4102::Color{0,255,0,255};
            } else {
                overlay_color = TDT4102::Color{255,0,0,255};
            }

            QuadRenderer::render(ctx, render_position(x,y), overlay_color);
    }
}

TDT4102::Point operator+(const TDT4102::Point p1, const TDT4102::Point p2) {
    return TDT4102::Point{ p1.x+p2.x, p1.y+p2.y };
}


TDT4102::Point operator-(const TDT4102::Point p1, const TDT4102::Point p2) {
    return TDT4102::Point{ p1.x - p2.x, p1.y - p2.y };
}

TDT4102::Point operator-(const TDT4102::Point p1)
{
    return TDT4102::Point{-p1.x, -p1.y};
}


std::ostream &operator<<(std::ostream &stream, const TDT4102::Point &point) {
    stream << "{Point: (" << point.x << ", " << point.y << ")}";
    return stream;
}


Tile::Tile(int id, bool walkable, const std::filesystem::path tile_image_path)
    : id{id}, walkable{walkable}
{
    if ( std::filesystem::exists(tile_image_path ) ) {
        image = std::make_shared<TDT4102::Image>(tile_image_path);
    } else {
        image.reset();
    }

}




Tile::Tile(Tile &&rhs) : id{rhs.id}, walkable{rhs.walkable}, image{rhs.image}
{
    rhs.image.reset();
    rhs.walkable = true;
    rhs.id = -1;
}

Tile &Tile::operator=(Tile &&rhs)
{
    image = rhs.image;
    rhs.image.reset();

    id = rhs.id;
    rhs.id = 0;

    walkable = rhs.walkable;
    rhs.walkable = true;

    return *this;
}

std::optional<Tile> TilePool::get_tile(KeyType key) {
    auto iter = tile_pool.find(key);


    if ( iter != tile_pool.cend() ) {
        auto &x = tile_pool.at(key);
        return x;
    }

    return std::optional<Tile>();
}

bool TilePool::add_tile(const KeyType &key, Tile tile)
{

    tile_pool.emplace(key, tile);
    tile_ids.push_back(key);

    return true;
}



const std::vector<int> &TilePool::get_tile_ids() const
{
    return tile_ids;
}

IncrementButton::IncrementButton() : TDT4102::Button({110, 20}, 100, 40, "+") {
        setCallback(IncrementButton::callback);
    }


void IncrementButton::callback() {
        IncrementButton::ts->increment();
}


void IncrementButton::setTileSelector(TileSelector * const _ts) {
        ts = _ts;
}

TileSelector *IncrementButton::ts = nullptr;


DecrementButton::DecrementButton () : TDT4102::Button({20, 20}, 100, 40, "-") {
    setCallback(DecrementButton::callback);
}

void DecrementButton::test() {
    ts->decrement();
}

DecrementButton::~DecrementButton() {}

void DecrementButton::callback() {
    DecrementButton::ts->decrement();
}

void DecrementButton::setTileSelector(TileSelector * const _ts) {
    ts = _ts;
}

TileSelector *DecrementButton::ts = nullptr;


SaveButton::SaveButton() : TDT4102::Button({20, 258}, 100, 40, "Save")
{
    setCallback(SaveButton::callback);
}

SaveButton::~SaveButton() { }

void SaveButton::callback() {

    try {
        LevelWriter::write("level_save", *level);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }


}

void SaveButton::setLevel(const Level *lvl) {
    level = lvl;
}

const Level * SaveButton::level = nullptr;


void TilePreview::render(TDT4102::AnimationWindow &window, std::optional<Tile> &tile)
{
    if ( tile.has_value() ) {
        window.draw_image(render_location, *(tile.value().image), 128, 128);
    } else {
        window.draw_rectangle(render_location, 128,128, TDT4102::Color{200,200,200,255});
    }
}

bool PlayerControllable::canMoveTo(TDT4102::Point new_position, const Level &lvl)
{
    bool within_bounds_x = new_position.x >= 0 && new_position.x < WORLD_WIDTH;
    bool within_bounds_y = new_position.y >= 0 && new_position.y < WORLD_HEIGHT;
    bool within_bounds = within_bounds_x && within_bounds_y;

    if ( ! within_bounds ) return false;

    bool reachable = std::max( std::abs(new_position.x - position.x),
            std::abs(new_position.y - position.y)) <= max_move_length;

    // int tile_index = new_position.y * WORLD_WIDTH + new_position.x;

    bool walkable = lvl.is_walkable(new_position);


    return reachable && walkable;
}

void PlayerControllable::moveTo(TDT4102::Point new_position, const Level &lvl)
{
    if ( ! canMoveTo(new_position, lvl) ) return;

    position = new_position;
}



Player::Player(std::filesystem::path spritePath) {
    sprite = TDT4102::Image(spritePath);
}

void Player::draw(TDT4102::AnimationWindow &window, const Context &ctx)
{
    // TODO: Maybe error here
    auto anchor = CoordinateSystem::to_screen(ctx, {position.x,position.y});

    anchor.y += sprite.height - TILE_SIZE + TILE_HEIGHT;
    anchor.x += TILE_WIDTH - sprite.width / 2;

    window.draw_image(anchor, sprite);
}



