#ifndef RAYLIB_GAME_SRC_GAME_H_
#define RAYLIB_GAME_SRC_GAME_H_

#include "config.h"
#include "player.h"
#include "include/tileson.hpp"
#include "terrain/collision_body.h"
#include "enemies/skeleton.h"
#include "shop.h"
#include "chest.h"
#include "items/coins/bronze_coin.h"
#include "reactor.h"
#include "enemies/boss.h"
#include <memory>

using namespace std;

class Game {
 private:
  shared_ptr<raylib::Texture2D> skeletonIdleTexture; 
  shared_ptr<raylib::Texture2D> skeletonAttackTexture;
  shared_ptr<raylib::Texture2D> skeletonHitTexture;
  shared_ptr<raylib::Texture2D> skeletonWalkTexture;
  shared_ptr<raylib::Texture2D> skeletonDeathTexture;
  
  unique_ptr<Boss> boss;
  Animation coinAnimation;
  raylib::Texture2D potionTexture;
  unique_ptr<bool> showDebugInfo;
  float maxX;
  float minX{800.f};
  float maxY;
  float minY{};
  std::map<std::tuple<int, int>, tson::Tile *> tileData;
  std::map<std::tuple<int, int>, tson::Tile *> tileBackgroundData;
  std::map<std::tuple<int, int>, tson::Tile *> interactablesData;
  unique_ptr<vector<unique_ptr<CollisionBody>>> terrains;
  vector<CollisionBody> interactables;
  vector<unique_ptr<Shop>> shops;
  vector<unique_ptr<Chest>> chests;
  vector<unique_ptr<BronzeCoin>> bronzeCoins;
  vector<unique_ptr<Skeleton>> skeletons;
  tson::Tileson tileson{};
  std::unique_ptr<tson::Map> map;
  unique_ptr<Player> player;
  raylib::Texture2D background1;
  float bg1ParallaxX{};
  raylib::Texture2D background2;
  float bg2ParallaxX{};
  raylib::Texture2D background3;
  float bg3ParallaxX{};
  std::map<string, Texture2D> tileTextures;
  raylib::Camera2D camera{};
  float bg1X{};
  float bg2X{};
  float bg3X{};
  void UpdateCamera();

 public:
  unique_ptr<Reactor<raylib::Vector2>> reactor = make_unique<Reactor<raylib::Vector2>>();
  Game(bool *showDebugInfo);
  void Draw();
  void LoadTileMap();
  void DrawTileMap() const;
  void DrawTiledBackground() const;
  void DrawInteractables();
  void Start();
  void LoadEnemies();
  void DrawCollectables();
};

#endif 
