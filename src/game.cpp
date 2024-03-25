#include "game.h"

void Game::UpdateCamera() {
  camera.target = {player.position.x, GetScreenHeight() - GetScreenHeight() * 0.65f};
  camera.offset = {
	  static_cast<float>(GetScreenWidth()) / 2.0f - (player.GetTextureWidth() / 2),
	  static_cast<float>(GetScreenHeight()) / 2.0f - player.GetTextureHeight() / 2
  };

  camera.target.x = Clamp(player.position.x, minX, maxX);
  camera.target.y = Clamp(player.position.y - player.GetHeight(), minY, maxY);

}

Game::Game() {
  LoadTileMap();
  camera.zoom = 1.0f;
  player.position.y = 688;
  player.position.x = 1000;

  camera.offset = {
	  static_cast<float>(GetScreenWidth()) / 2.0f - (player.GetTextureWidth() / 2),
	  static_cast<float>(GetScreenHeight()) / 2.0f - player.GetTextureHeight() / 2
  };
}
void Game::Draw() {
  UpdateCamera();
  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
	player.direction = RIGHT;
	player.lastDirection = RIGHT;
  } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
	player.direction = LEFT;
	player.lastDirection = LEFT;
  } else { player.direction = STOP; }

  if (player.direction == RIGHT && !player.attacking && !player.blocked && !player.isDead
	  && player.position.x < maxX && player.position.x > minX) {
	bg1X -= 1;
	bg2X -= 2;
	bg3X -= 3;

	if (bg1X <= -background1.width * scale * BG_SCALE) bg1X = 0;
	if (bg2X <= -background2.width * scale * BG_SCALE) bg2X = 0;
	if (bg3X <= -background3.width * scale * BG_SCALE) bg3X = 0;
  }

  if (player.direction == LEFT && !player.attacking && !player.blocked && !player.isDead && player.position.x > minX
	  && player.position.x < maxX) {
	bg1X += 1;
	bg2X += 2;
	bg3X += 3;

	if (bg1X >= 0) bg1X = -background1.width * scale * BG_SCALE;
	if (bg2X >= 0) bg2X = -background2.width * scale * BG_SCALE;
	if (bg3X >= 0) bg3X = -background3.width * scale * BG_SCALE;
  }

  Vector2 bg1Pos{bg1X, 0};
  Vector2 bg1Pos_2{bg1X + background1.width * scale * BG_SCALE, 0};
  Vector2 bg2Pos{bg2X, 0};
  Vector2 bg2Pos_2{bg2X + background2.width * scale * BG_SCALE, 0};

  Vector2 bg3Pos{bg3X, 0};
  Vector2 bg3Pos_2{bg3X + background3.width * scale * BG_SCALE, 0};

  DrawTextureEx(background1, bg1Pos, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background1, bg1Pos_2, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background2, bg2Pos, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background2, bg2Pos_2, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background3, bg3Pos, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background3, bg3Pos_2, 0.0f, scale * BG_SCALE, WHITE);

  BeginMode2D(camera);
  {
	bool collision = false;
	bool sideCollision = false;
	float yPos;
	float xPos;

	for (auto &terrain : terrains) {
	  auto [coll, y] = terrain.CheckTopCollision(player.hitbox, player.upwardsVelocity);
	  if (coll) {
		collision = true;
		yPos = y;
		break;
	  }
	}

	for (auto &terrain : terrains) {
	  auto [sideColl, x] = terrain.CheckSideCollision(player.hitbox, RUN_SPEED + player.upwardsVelocity / 2.0f);
	  if (sideColl) {
		sideCollision = true;
		xPos = x;
		break;
	  }
	}

	if (collision) {
	  player.SetOnGround(true);
	  player.position.y = yPos - player.GetTextureHeight();
	  player.upwardsVelocity = 0;
	  player.falling = false;
	} else {
	  player.SetOnGround(false);
	}

	if (sideCollision) {
	  player.blocked = true;
	  if (xPos > player.hitbox.x) {
		player.rightBlocked = true;
		player.leftBlocked = false;
	  } else if (xPos < player.hitbox.x + player.GetWidth()) {
		player.leftBlocked = true;
		player.rightBlocked = false;
	  }
	  player.SetXPosition(xPos);
	} else {
	  player.blocked = false;
	  player.leftBlocked = false;
	  player.rightBlocked = false;
	}
	
	DrawTileMap();
	for (auto &enemy : skeletons) {
	  enemy.Draw();
	}
	player.Draw();

  }
  EndMode2D();

#ifdef LOG
  // Stats
  DrawText(TextFormat("Player x: %f", player.position.x), 10, 10, 50, WHITE);
  DrawText(TextFormat("Player y: %f", player.position.y), 10, 60, 50, WHITE);
  DrawText(TextFormat("Camera x: %f", camera.target.x), 10, 110, 50, WHITE);
  DrawText(TextFormat("Camera y: %f", camera.target.y), 10, 160, 50, WHITE);
  DrawText(TextFormat("Camera offset x: %f", camera.offset.x), 10, 210, 50, WHITE);
  DrawText(TextFormat("Camera offset y: %f", camera.offset.y), 10, 260, 50, WHITE);

  // Guide lines
//	  DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), RED);
#endif
  if (player.isDead) {
	DrawText("You died!", GetScreenWidth() / 2 - MeasureText("You died!", 50) / 2, GetScreenHeight() / 2, 50, RED);
  }
}
void Game::LoadTileMap() {
  map = tileson.parse("assets/tiled/level1.json");
  if (map->getStatus() == tson::ParseStatus::OK) {
	//You can loop through every container of objects
//	for (auto &layer : map->getLayers()) {
//	  if (layer.getType() == tson::LayerType::ObjectGroup) {
//		for (auto &obj : layer.getObjects()) {
//		  //Just iterate through all the objects
//		}
//		//Or use these queries:
//
//		//Gets the first object it finds with the name specified
////                tson::Object *player = layer.firstObj("player"); //Does not exist in demo map->..
//
//		//Gets all objects with a matching name
////                std::vector<tson::Object> enemies = layer.getObjectsByName("goomba"); //But we got two of those
//
//		//Gets all objects of a specific type
//		std::vector<tson::Object> objects = layer.getObjectsByType(tson::ObjectType::Object);
//
//		//Gets a unique object by its name.
//		tson::Object *uniqueObj = layer.getObj(2);
//	  }
//	}

	tson::Layer *layer = map->getLayer("Collision Layer");

	if (layer->getType() == tson::LayerType::TileLayer) {
	  //When the map is of a fixed size, you can get the tiles like this
	  if (!map->isInfinite()) {
		tileData = layer->getTileData();

		maxX = (layer->getSize().x * 24 * 3) - 1200;
		maxY = (layer->getSize().y * 24 * 3) - 700;

		for (auto &t : tileData) {
		  Vector2 pos = {static_cast<float>(get<0>(t.first) * 24 * 3), static_cast<float>(get<1>(t.first) * 24 * 3)};
		  auto drawingRect = t.second->getDrawingRect();
		  Rectangle collisionRect = {
			  static_cast<float>(pos.x),
			  static_cast<float>(pos.y),
			  static_cast<float>(drawingRect.width * 3 * scale),
			  static_cast<float>(drawingRect.height * 3 * scale)
		  };

		  CollisionBody terrain = CollisionBody(pos, collisionRect, true);
		  terrains.push_back(terrain);
		}
	  }
	}

	tson::Layer *bg1 = map->getLayer("Background1");
	tson::Layer *bg2 = map->getLayer("Background2");
	tson::Layer *bg3 = map->getLayer("Background3");

	string bg1ImagePath = bg1->getImage();
	bg1ImagePath = bg1ImagePath.replace(0, 2, "assets");
	background1 = LoadTexture(bg1ImagePath.c_str());
	bg1ParallaxX = bg1->getParallax().x;

	string bg2ImagePath = bg2->getImage();
	bg2ImagePath = bg2ImagePath.replace(0, 2, "assets");
	background2 = LoadTexture(bg2ImagePath.c_str());
	bg2ParallaxX = bg2->getParallax().x;

	string bg3ImagePath = bg3->getImage();
	bg3ImagePath = bg3ImagePath.replace(0, 2, "assets");
	background3 = LoadTexture(bg3ImagePath.c_str());
	bg3ParallaxX = bg3->getParallax().x;

	tson::Layer *enemyLayer = map->getLayer("Enemies");
	for (auto &e : enemyLayer->getTileData()) {
	  auto x = static_cast<float>(get<0>(e.first) * 24 * 3);
	  auto y = static_cast<float>(get<1>(e.first) * 24 * 3) - 86;
	  skeletons.push_back(Skeleton{
		  {static_cast<float>(x),
		   static_cast<float>(y)},
		  {x, y, 24, 24}, player});
	}

  } else //Error occurred
  {
	std::cout << map->getStatusMessage();
  }
}
void Game::DrawTileMap() {
  for (auto tile : tileData) {
	if (tile.second != nullptr) {
	  Rectangle sourceRect =
		  {static_cast<float>(tile.second->getDrawingRect().x), static_cast<float>(tile.second->getDrawingRect().y),
		   static_cast<float>(tile.second->getDrawingRect().width),
		   static_cast<float>(tile.second->getDrawingRect().height)};
	  Vector2
		  position = {static_cast<float>(get<0>(tile.first) * 24 * 3), static_cast<float>(get<1>(tile.first) * 24 * 3)};
	  Rectangle destRect = {position.x, position.y, 24 * 3, 24 * 3};
	  DrawTexturePro(tileSet, sourceRect, destRect, {}, 0, WHITE);
	}
  }
}
