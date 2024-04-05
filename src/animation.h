#ifndef RAYLIB_GAME_SRC_ANIMATION_H
#define RAYLIB_GAME_SRC_ANIMATION_H

#include <complex>
#include "raylib-cpp.hpp"
#include <memory>

using namespace std;

class Animation {
 private:
  string texturePath;
  shared_ptr<raylib::Texture2D> texture;
  raylib::Vector2 position;
  float updateTime;
  int width;
  int height;
  int rows;
  int firstRow;
  int lastRow;
  int currentRow{};
  raylib::Rectangle rectangle;
  float runningTime{};

 public:
//  ~Animation();
  float frame{};
  float scale{};
  int numberOfFrames;
  
  Animation(
	  const shared_ptr<raylib::Texture2D> texture,
	  int numberOfFrames,
	  float updateTime,
	  float scale = 4.f,
	  int rows = 1,
	  int firstRow = 0,
	  int lastRow = 0
  );
  
  Animation(
	  const string &texturePath,
	  int numberOfFrames,
	  float updateTime,
	  float scale = 4.f,
	  int rows = 1,
	  int firstRow = 0,
	  int lastRow = 0
  );

  void SetPosition(raylib::Vector2 pos);
  raylib::Vector2 GetPosition() const;
  float GetTextureHeight() const;
  float GetTextureWidth() const;
  bool Animate(raylib::Vector2 pos, bool facingRight = true);
  raylib::Rectangle GetSourceRec() const;
  void Reset();
  void DrawLastFrame(raylib::Vector2 pos);
  void DrawFirstFrame(raylib::Vector2 pos);
};

#endif 
