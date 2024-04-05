#ifndef RAYLIB_GAME_SRC_DECORATIONS_DECORATION_H_
#define RAYLIB_GAME_SRC_DECORATIONS_DECORATION_H_

#include "raylib-cpp.hpp"
extern float scale;

class Decoration {
  const raylib::Texture *texture;
  raylib::Vector2 position;
  raylib::Rectangle rec;

 public:
  Decoration(raylib::Vector2 pos, const raylib::Texture *tex);
  Decoration(raylib::Vector2 pos, const raylib::Texture *tex, raylib::Rectangle rec);
  void Draw() const;
};

#endif 
