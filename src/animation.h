#ifndef RAYLIB_GAME_SRC_ANIMATION_H
#define RAYLIB_GAME_SRC_ANIMATION_H

#include <complex>
#include "raylib.h"
using namespace std;

class Animation {
 private:
  string texturePath;
  Texture2D texture;
  Vector2 position;
  float updateTime;
  int width;
  int height;
  int rows;
  int firstRow;
  int lastRow;
  int currentRow{};
  Rectangle rectangle;
  float runningTime{};

 public:
  ~Animation();
  float frame{};
  float scale{};
  int numberOfFrames;
  Animation(const char *texturePath, int numberOfFrames, float updateTime, float scale = 4.f, int rows = 1, int firstRow = 0, int lastRow = 0);

  void SetPosition(Vector2 pos);
  Vector2 GetPosition() const;
  float GetTextureHeight() const;
  float GetTextureWidth() const;
  bool Animate(Vector2 pos, bool facingRight = true);
  Texture2D GetTexture() const;
  Rectangle GetSourceRec() const;
  void Reset();
  void DrawLastFrame(Vector2 pos);
  void DrawFirstFrame(Vector2 pos);
};

#endif 
