#ifndef RAYLIB_GAME_SRC_GAME_H_
#define RAYLIB_GAME_SRC_GAME_H_

#include "raylib.h"
#include "raymath.h"
#include "config.h"
#include "player.h"
#include "level_manager.h"
#include "include/tileson.hpp"
#include "terrain/terrain.h"

class Game {
 private:
  std::map<std::tuple<int, int>, tson::Tile *> tileData;
  vector<Terrain> terrains;
  tson::Tileson tileson{};
  std::unique_ptr<tson::Map> map;
  Player player{};
//  LevelManager levelManager{"assets/levels/level1/level1.txt"};
  Texture2D background1 = LoadTexture("../assets/levels/level1/background_layer_1.png");
  Texture2D background2 = LoadTexture("../assets/levels/level1/background_layer_2.png");
  Texture2D background3 = LoadTexture("../assets/levels/level1/background_layer_3.png");
  Texture2D tileSet = LoadTexture("../assets/oak_woods_tileset.png");
  Camera2D camera{};
  float bg1X{};
  float bg2X{};
  float bg3X{};
  void UpdateCamera();

 public:
  Game();
  void Draw();
  void LoadTileMap();
  void DrawTileMap();
};

#endif 
