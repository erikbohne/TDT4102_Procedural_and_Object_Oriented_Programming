#pragma once
#include "AnimationWindow.h"

using ImageAtlasStored = std::shared_ptr<TDT4102::Image>;
using ImageAtlasContainer = std::unordered_map<std::string, ImageAtlasStored>;


/**
 * A singleton class to manage instances of TDT4102::Image. Its purpose
 * is to keep images in memory instead of loading images repeatedly.
 */
class ImageAtlas {

public:
  static ImageAtlas &getInstance();

  static bool add_image(const std::string &key, const std::string &filename);
  static ImageAtlasStored get_image(const std::string &filename);

  static bool has_image(const std::string &key);

  static void load_default_atlas();

private:
    ImageAtlas() = default;

    ImageAtlasContainer container{};

    void makeInstance();

    static ImageAtlas instance;
    static bool constructed;

};



