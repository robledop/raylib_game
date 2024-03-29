#ifndef RAYLIB_GAME_SRC_ANIMATION_H
#define RAYLIB_GAME_SRC_ANIMATION_H

#include <complex>
#include "raylib.h"
using namespace std;

class Animation {
 private:
  Texture2D texture;
  Vector2 position;
  float updateTime;
  float runningTime{};
  float frame{};
  int width;
  int height;
  Rectangle rectangle;

 public:
  float scale{};
  int numberOfFrames;
  Animation(const char *texturePath, int numberOfFrames, float updateTime, float scale = 4.f);

  void SetPosition(Vector2 pos);
  Vector2 GetPosition() const;
  float GetTextureHeight() const;
  float GetTextureWidth() const;
  bool Animate(Vector2 pos, bool facingRight = true);
  Texture2D GetTexture() const;
  Rectangle GetSourceRec() const;
};

#endif //RAYLIB_GAME_SRC_ANIMATION_H
