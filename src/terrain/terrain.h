#ifndef RAYLIB_GAME_SRC_TERRAIN_H_
#define RAYLIB_GAME_SRC_TERRAIN_H_

#include "raylib.h"
extern float scale;

class Terrain {
 protected:
  const Texture2D *texture;
  bool blocking;

 public:
  Rectangle sourceRect;
  Vector2 position{};
  Terrain(Vector2 pos, const Texture2D *tex, bool blocking = true);
  bool CheckTopCollision(Rectangle hitbox, float playerSpeed) const;
  bool CheckSideCollision(Rectangle hitbox, float playerSpeed) const;
  bool CheckBottomCollision(Rectangle hitbox, float playerSpeed) const;

  void Draw();

};

#endif 
