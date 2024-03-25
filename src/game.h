#ifndef RAYLIB_GAME_SRC_GAME_H_
#define RAYLIB_GAME_SRC_GAME_H_

#include "raylib.h"
#include "raymath.h"
#include "config.h"
#include "player.h"
#include "level_manager.h"
#include "include/tileson.hpp"
#include "terrain/collision_body.h"
#include "enemies/skeleton.h"

class Game {
 private:
  float maxX;
  float minX{800.f};
  float maxY;
  float minY{};
  vector<tson::Tileset> tilesets;
  std::map<std::tuple<int, int>, tson::Tile *> tileData;
  vector<CollisionBody> terrains;
  vector<Skeleton> skeletons;
  tson::Tileson tileson{};
  std::unique_ptr<tson::Map> map;
  Player player{};
  Texture2D background1;
  float bg1ParallaxX{};
  Texture2D background2;
  float bg2ParallaxX{};
  Texture2D background3;
  float bg3ParallaxX{};
  Texture2D tileSet = LoadTexture("assets/tilesets/oak_woods_tileset.png");
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
