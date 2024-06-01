#pragma once

#include "common.h"

/**
 * A base class that takes care of positioning and sizing of an `Entity`.
 */
struct Entity {
    using Point = TDT4102::Point;

    ~Entity() {}

    explicit Entity(Point position_, int width_, int height_)
        : position{position_}, width{width_}, height{height_}
    {
        ;
    }

    Entity() = default;
    Entity(const Entity& other) = default;
    Entity& operator=(const Entity& other) = default;
    Entity(Entity&& other) = default;
    Entity& operator=(Entity&& other) = default;


    Point get_position() const {
        return position;
    }

    void set_position(Point new_pos) {
        position = new_pos;
    }

    void set_width(int width_) {
        width = width_;
    }

    void set_height(int height_) {
        height = height_;
    }

    int get_width() const {
        return width;
    }

    int get_height() const {
        return height;
    }

    /**
     * A virtual method that can be overriden to take care of invariants.
     *
     * Example: updating card positions in a card stack.
     */
    virtual void update() {
        // No-op as base entity
    }

private:
    Point position;
    int width;
    int height;

};



