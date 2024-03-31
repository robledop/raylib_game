#ifndef RAYLIB_GAME_SRC_GAME_H_
#define RAYLIB_GAME_SRC_GAME_H_

#include "raylib.h"
#include "raymath.h"
#include "config.h"
#include "player.h"
#include "include/tileson.hpp"
#include "terrain/collision_body.h"
#include "enemies/skeleton.h"
#include "shop.h"

class Game {
 private:
  bool* showDebugInfo;
  float maxX;
  float minX{800.f};
  float maxY;
  float minY{};
  std::map<std::tuple<int, int>, tson::Tile *> tileData;
  std::map<std::tuple<int, int>, tson::Tile *> tileBackgroundData;
  std::map<std::tuple<int, int>, tson::Tile *> interactablesData;
  vector<CollisionBody> terrains;
  vector<CollisionBody> interactables;
  vector<Shop*> shops;
  vector<Skeleton*> skeletons;
  tson::Tileson tileson{};
  std::unique_ptr<tson::Map> map;
  Player player{};
  Texture2D background1;
  float bg1ParallaxX{};
  Texture2D background2;
  float bg2ParallaxX{};
  Texture2D background3;
  float bg3ParallaxX{};
  ::map<string ,Texture2D> tileTextures;
  Camera2D camera{};
  float bg1X{};
  float bg2X{};
  float bg3X{};
  void UpdateCamera();

 public:
  Game(bool* showDebugInfo);
  ~Game();
  void Draw();
  void LoadTileMap();
  void DrawTileMap() const;
  void DrawTiledBackground() const;
  void DrawInteractables();
};

#endif 
