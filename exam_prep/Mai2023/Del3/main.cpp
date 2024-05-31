#include <AnimationWindow.h>
#include <widgets/Button.h>
#include <filesystem>
#include <atomic>
#include <optional>
#include <type_traits>
#include <functional>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cassert>
#include "Tasks.h"

#define GAME 0
#define DRAW_TEST_QUAD 0

extern bool show_walkable_overlay;

int main() {

    auto tile_pool = TileLoader::load("tiles/tile_info");
    auto lvl = LevelLoader::load("./level_save");

    TDT4102::AnimationWindow window(50, 50, 768, 492, "4102Game");
    Context ctx(&window, std::make_shared<Camera>());

    CameraController camController{1};

    ctx.getCamera().focusOn({0,0}, window.width(), window.height() );

    bool lmb_held = false;

    TileSelector tile_selector(-1, tile_pool.get_tile_ids().size() - 1);

    int active_tile = 0;


    // -----------------------------------------------------
    // -------------------- GUI ELEMENTS -------------------
    // -----------------------------------------------------
    IncrementButton increment_btn{};
    IncrementButton::setTileSelector(&tile_selector);
    window.add(increment_btn);

    DecrementButton decrement_btn{};
    DecrementButton::setTileSelector(&tile_selector);
    window.add(decrement_btn);

    SaveButton save_btn{};
    SaveButton::setLevel(&lvl);
    window.add(save_btn);

    OverlayButton overlay_btn{};
    window.add(overlay_btn);

    LevelRenderer renderer(ctx, lvl, tile_pool);
    PlacementOverlay placement_overlay{ctx};
    WalkableOverlay walkable_overlay{lvl};

    TDT4102::Point placement_begin;
    TDT4102::Point placement_end;

    while (!window.should_close()) {

        // ------------------------------------------------------------
        // HANDLE INPUT
        // ------------------------------------------------------------
        auto hovered_tile = CoordinateSystem::to_grid(ctx, window.get_mouse_coordinates());
        active_tile = tile_selector.get_current();


        int placement_id;
        bool placement_walkable;
        if ( active_tile < 0 ) {
            placement_id = -1;
            placement_walkable = false;
            placement_overlay.reset_tile();
        }
        else {
            placement_id = tile_pool.get_tile_ids()[static_cast<size_t>(active_tile)];
            placement_walkable = tile_pool.get_tile(placement_id)->walkable;
            auto tile = tile_pool.get_tile(placement_id);
            placement_overlay.set_tile(tile);
        }

        placement_overlay.set_tile(tile_pool.get_tile(placement_id));


        bool is_lmb_down     = window.is_left_mouse_button_down();
        bool nothing_clicked = ! is_lmb_down && ! lmb_held;
        bool initial_click   =   is_lmb_down && ! lmb_held;
        bool released        = ! is_lmb_down &&   lmb_held;

        if ( nothing_clicked) {
            placement_begin = hovered_tile;
            placement_overlay.set_begin(hovered_tile);
            placement_overlay.set_end(hovered_tile);
            placement_end = hovered_tile;
        }

        if ( initial_click ) {
            placement_begin = hovered_tile;
            placement_overlay.set_begin(hovered_tile);
        }

        if ( lmb_held && ! initial_click ) {
            placement_overlay.set_end(hovered_tile);
            placement_end = hovered_tile;
        }

        if ( released ) {
            lvl.set_tile_region(
                    placement_begin,
                    placement_end,
                    placement_id,
                    placement_walkable
            );
        }


        lmb_held = window.is_left_mouse_button_down();

        camController.handleInput(ctx);

        tile_selector.handle_input(window);

        window.next_frame();


        // ------------------------------------------------------------
        // RENDER
        // ------------------------------------------------------------
        renderer.render();
        if ( show_walkable_overlay ) {
            walkable_overlay.render(ctx);
        }
        placement_overlay.render();

        /// ============================================================
        /// Draw a preview of the currently selected tile
        /// ============================================================

        auto preview_tile = tile_pool.get_tile(placement_id);

        TilePreview::render(ctx.getWindow(), preview_tile);

        if ( show_walkable_overlay ) {

            auto anchor = CoordinateSystem::to_screen(ctx, placement_begin)
                + TDT4102::Point{0, TILE_WIDTH};

            TDT4102::Color preview_color;

            if ( preview_tile->walkable ) {
                preview_color = TDT4102::Color{0, 255, 0, 255};
            } else {
                preview_color = TDT4102::Color{255, 0, 0, 255};
            }

            QuadRenderer::render(ctx, anchor, preview_color);
        }
    }

    return 0;
}

