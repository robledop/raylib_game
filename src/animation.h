#ifndef RAYLIB_GAME_SRC_ANIMATION_H_
#define RAYLIB_GAME_SRC_ANIMATION_H_

#include <complex>
#include "raylib.h"
using namespace std;
extern float scale;

class Animation {
 private:
  Texture2D texture;
  Rectangle rectangle;
  Vector2 position;
  float updateTime;
  float runningTime{};
  float frame{};
  int numberOfFrames;
  int width;
  int height;

 public:
  Animation(const char *texturePath, int numberOfFrames, float updateTime);

  void SetPosition(Vector2 pos);
  Vector2 GetPosition() const;
  float GetTextureHeight() const;
  float GetTextureWidth() const;
  void UpdateScale();
  bool Animate(Vector2 pos, bool facingRight = true);
};

#endif //RAYLIB_GAME_SRC_ANIMATION_H_
