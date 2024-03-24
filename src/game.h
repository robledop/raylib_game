#ifndef RAYLIB_GAME_SRC_GAME_H_
#define RAYLIB_GAME_SRC_GAME_H_

#include "raylib.h"
#include "raymath.h"
#include "config.h"
#include "player.h"
#include "level_manager.h"

class Game {
 private:
  Player player{};
  LevelManager levelManager{ASSETS_PATH"levels/level1/level1.txt"};
  Texture2D background1 = LoadTexture(ASSETS_PATH"levels/level1/background_layer_1.png");
  Texture2D background2 = LoadTexture(ASSETS_PATH"levels/level1/background_layer_2.png");
  Texture2D background3 = LoadTexture(ASSETS_PATH"levels/level1/background_layer_3.png");
  Camera2D camera{};
  float bg1X{};
  float bg2X{};
  float bg3X{};
  void UpdateCamera();

 public:
  Game();
  void Draw();
};

#endif 
