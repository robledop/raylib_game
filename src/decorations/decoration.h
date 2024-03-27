#ifndef RAYLIB_GAME_SRC_DECORATIONS_DECORATION_H_
#define RAYLIB_GAME_SRC_DECORATIONS_DECORATION_H_

#include "raylib.h"
extern float scale;

class Decoration {
  const Texture *texture;
  Vector2 position;
  Rectangle rec;

 public:
  Decoration(Vector2 pos, const Texture *tex);
  Decoration(Vector2 pos, const Texture *tex, Rectangle rec);
  void Draw() const;
};

#endif 
