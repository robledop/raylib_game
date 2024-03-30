#include "game.h"

void Game::UpdateCamera() {
  camera.target = {player.position.x,
				   static_cast<float>(GetScreenHeight()) -
					   static_cast<float>(GetScreenHeight()) * 0.65f};
  camera.offset = {static_cast<float>(GetScreenWidth()) / 2.0f -
	  (player.GetTextureWidth() / 2),
				   static_cast<float>(GetScreenHeight()) / 2.0f -
					   player.GetTextureHeight() / 2};

  camera.target.x = Clamp(player.position.x, minX, maxX);
  camera.target.y = Clamp(player.position.y - player.GetHeight(), minY, maxY);
}

Game::Game() {
  camera.zoom = 1.0f;
  player.position.y = 688;
  player.position.x = 1000;

  camera.offset = {static_cast<float>(GetScreenWidth()) / 2.0f -
	  (player.GetTextureWidth() / 2),
				   static_cast<float>(GetScreenHeight()) / 2.0f -
					   player.GetTextureHeight() / 2};
  LoadTileMap();
  for (auto &enemy : skeletons) {
	enemy.Init();
  }
}
void Game::Draw() {
  player.Init();
  UpdateCamera();
  if (!player.isDead &&
	  (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) ||
		  IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))) {
	player.direction = RIGHT;
	player.lastDirection = RIGHT;
  } else if (!player.isDead &&
	  (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) ||
		  IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT))) {
	player.direction = LEFT;
	player.lastDirection = LEFT;
  } else {
	player.direction = STOP;
  }

  if (player.direction == RIGHT && !player.attacking && !player.blocked &&
	  !player.isDead && player.position.x < maxX && player.position.x > minX) {
	bg1X -= 1;
	bg2X -= 2;
	bg3X -= 3;

	if (bg1X <= -background1.width * scale * BG_SCALE)
	  bg1X = 0;
	if (bg2X <= -background2.width * scale * BG_SCALE)
	  bg2X = 0;
	if (bg3X <= -background3.width * scale * BG_SCALE)
	  bg3X = 0;
  }

  if (player.direction == LEFT && !player.attacking && !player.blocked &&
	  !player.isDead && player.position.x > minX && player.position.x < maxX) {
	bg1X += 1;
	bg2X += 2;
	bg3X += 3;

	if (bg1X >= 0)
	  bg1X = -background1.width * scale * BG_SCALE;
	if (bg2X >= 0)
	  bg2X = -background2.width * scale * BG_SCALE;
	if (bg3X >= 0)
	  bg3X = -background3.width * scale * BG_SCALE;
  }

  const Vector2 bg1Pos{bg1X, 0};
  const Vector2 bg1Pos_2{bg1X + background1.width * scale * BG_SCALE, 0};
  const Vector2 bg2Pos{bg2X, 0};
  const Vector2 bg2Pos_2{bg2X + background2.width * scale * BG_SCALE, 0};

  const Vector2 bg3Pos{bg3X, 0};
  const Vector2 bg3Pos_2{bg3X + background3.width * scale * BG_SCALE, 0};

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
	  auto [coll, y] =
		  terrain.CheckTopCollision(player.hitbox, player.upwardsVelocity);
	  if (coll) {
		collision = true;
		yPos = y;
		break;
	  }
	}

	for (auto &terrain : terrains) {
	  auto [sideColl, x] = terrain.CheckSideCollision(
		  player.hitbox, RUN_SPEED + player.upwardsVelocity / 2.0f);
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

	DrawInteractables();
	DrawTiledBackground();
	DrawTileMap();
	player.Draw();
	for (auto &enemy : skeletons) {
	  enemy.Draw();
	}
  }
  EndMode2D();

  // Draw the health bar in the top-left corner of the screen
  DrawRectangle(10, 10, player.maxHealth * 2, 10, BLACK);
  DrawRectangle(10, 10, player.health * 2, 10, RED);

#ifdef LOG
  // Stats
  DrawText(TextFormat("Player x: %f", player.position.x), 10, 10, 50, WHITE);
  DrawText(TextFormat("Player y: %f", player.position.y), 10, 60, 50, WHITE);
  DrawText(TextFormat("Camera x: %f", camera.target.x), 10, 110, 50, WHITE);
  DrawText(TextFormat("Camera y: %f", camera.target.y), 10, 160, 50, WHITE);
  DrawText(TextFormat("Camera offset x: %f", camera.offset.x), 10, 210, 50,
		   WHITE);
  DrawText(TextFormat("Camera offset y: %f", camera.offset.y), 10, 260, 50,
		   WHITE);

  // Guide lines
//	  DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2,
//GetScreenHeight(), RED);
#endif
  if (player.isDead) {
	DrawText("You died!",
			 GetScreenWidth() / 2 - MeasureText("You died!", 50) / 2,
			 GetScreenHeight() / 2, 50, RED);
  }
}
void Game::LoadTileMap() {
  map = tileson.parse("assets/tiled/level1.json");
  if (map->getStatus() == tson::ParseStatus::OK) {
	// You can loop through every container of objects
	//	for (auto &layer : map->getLayers()) {
	//	  if (layer.getType() == tson::LayerType::ObjectGroup) {
	//		for (auto &obj : layer.getObjects()) {
	//		  //Just iterate through all the objects
	//		}
	//		//Or use these queries:
	//
	//		//Gets the first object it finds with the name specified
	////                tson::Object *player = layer.firstObj("player"); //Does
	///not exist in demo map->..
	//
	//		//Gets all objects with a matching name
	////                std::vector<tson::Object> enemies =
	///layer.getObjectsByName("goomba"); //But we got two of those
	//
	//		//Gets all objects of a specific type
	//		std::vector<tson::Object> objects =
	//layer.getObjectsByType(tson::ObjectType::Object);
	//
	//		//Gets a unique object by its name.
	//		tson::Object *uniqueObj = layer.getObj(2);
	//	  }
	//	}

	// Load all textures
	for (auto &ts : map->getTilesets()) {
	  string tileSetPath = ts.getImagePath().string();
	  if (tileSetPath != "") {
		tileSetPath = tileSetPath.replace(0, 2, "assets");
		if (tileTextures.count(tileSetPath) == 0) {
		  Texture2D tex = LoadTexture(tileSetPath.c_str());
		  tileTextures.insert(make_pair(tileSetPath, tex));
		}
	  }

	  for (auto &t : ts.getTiles()) {
		string path = t.getImage().string();
		if (path == "") continue;
		path = path.replace(0, 2, "assets");
		if (tileTextures.count(path) == 0) {
		  Texture2D tex = LoadTexture(path.c_str());
		  tileTextures.insert(make_pair(path, tex));
		}
	  }
	}

	tson::Layer *layer = map->getLayer("Collision Layer");

	if (layer->getType() == tson::LayerType::TileLayer) {
	  // When the map is of a fixed size, you can get the tiles like this
	  if (!map->isInfinite()) {
		tileData = layer->getTileData();

		maxX = (layer->getSize().x * 24 * 3) - 1200;
		maxY = (layer->getSize().y * 24 * 3) - 700;

		for (auto &t : tileData) {
		  Vector2 pos = {static_cast<float>(get<0>(t.first) * 24 * 3),
						 static_cast<float>(get<1>(t.first) * 24 * 3)};
		  const auto drawingRect = t.second->getDrawingRect();
		  const Rectangle collisionRect = {
			  static_cast<float>(pos.x), static_cast<float>(pos.y),
			  static_cast<float>(drawingRect.width * 3 * scale),
			  static_cast<float>(drawingRect.height * 3 * scale)};

		  CollisionBody terrain = CollisionBody(pos, collisionRect, true);
		  terrains.push_back(terrain);
		}
	  }
	}

	tson::Layer *tileBackgroundLayer = map->getLayer("Tiled Background");
	if (tileBackgroundLayer->getType() == tson::LayerType::TileLayer) {
	  tileBackgroundData = tileBackgroundLayer->getTileData();
	}

	const tson::Layer *bg1 = map->getLayer("Background1");
	const tson::Layer *bg2 = map->getLayer("Background2");
	const tson::Layer *bg3 = map->getLayer("Background3");

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

	const tson::Layer *enemyLayer = map->getLayer("Enemies");
	for (auto &e : enemyLayer->getTileData()) {
	  const auto x = static_cast<float>(get<0>(e.first) * 24 * 3);
	  const auto y = static_cast<float>(get<1>(e.first) * 24 * 3) - 86;
	  const auto rect = e.second->getDrawingRect();
	  skeletons.push_back(
		  Skeleton{{static_cast<float>(x), static_cast<float>(y)},
				   {x, y, static_cast<float>(rect.width * 5),
					static_cast<float>(rect.height * 5)},
				   &player, &terrains});
	}

	const tson::Layer *interactableLayer = map->getLayer("Interactables");
	if (interactableLayer->getType() == tson::LayerType::TileLayer) {
	  interactablesData = interactableLayer->getTileData();

	  for (auto &i : interactablesData) {
		const auto tile = i.second;
		if (tile->getType() == "shop") {
		  const auto x = static_cast<float>(get<0>(i.first) * 24 * 3);
		  const auto y = static_cast<float>(get<1>(i.first) * 24 * 3);
		  const auto rect = i.second->getDrawingRect();
		  const auto collisionRect = Rectangle{x * 24 * 3, y * 24 * 3, rect.width * 3.f, rect.height * 3.f};
		  Shop shop = Shop{{x, y - collisionRect.height - 24 * 2}, collisionRect};
		  shops.push_back(shop);
		}
	  }

	} else {
	  TraceLog(LOG_ERROR, "Error occurred: %s", map->getStatusMessage().c_str());
	}
  }
}
void Game::DrawTileMap() const {
  for (auto [fst, snd] : tileData) {
	if (snd != nullptr) {
	  const Rectangle sourceRect = {
		  static_cast<float>(snd->getDrawingRect().x),
		  static_cast<float>(snd->getDrawingRect().y),
		  static_cast<float>(snd->getDrawingRect().width),
		  static_cast<float>(snd->getDrawingRect().height)};
	  const Vector2 position = {static_cast<float>(get<0>(fst) * 24 * 3),
								static_cast<float>(get<1>(fst) * 24 * 3)};
	  const Rectangle destRect = {position.x, position.y, 24 * 3, 24 * 3};
	  string path = snd->getTileset()->getImagePath().string();
	  path = path.replace(0, 2, "assets");
	  Texture2D tileSet = tileTextures.at(path);
	  DrawTexturePro(tileSet, sourceRect, destRect, {}, 0, WHITE);
	}
  }
}

void Game::DrawTiledBackground() const {
  for (auto [coord, tile] : tileBackgroundData) {
	if (tile != nullptr) {
	  const Rectangle sourceRect = {
		  static_cast<float>(tile->getDrawingRect().x),
		  static_cast<float>(tile->getDrawingRect().y),
		  static_cast<float>(tile->getDrawingRect().width),
		  static_cast<float>(tile->getDrawingRect().height)
	  };

	  auto tileSetName = tile->getTileset()->getName();
	  if (tileSetName == "decorations") {
		float y;
		const float x = get<0>(coord) * 24 * 3;
		if (sourceRect.height > 24) {
		  y = get<1>(coord) * 24 * 3 - (sourceRect.height * 3 - 24 * 3);
		} else {
		  y = get<1>(coord) * 24 * 3 + (24 * 3 - sourceRect.height * 3);
		}

		const Rectangle destRect = {x, y, sourceRect.width * 3, sourceRect.height * 3};
		string path;
		if (tile->getImage() != "") {
		  path = tile->getImage().string();
		} else {
		  path = tile->getTileset()->getImagePath().string();
		}

		path = path.replace(0, 2, "assets");
		Texture2D t = tileTextures.at(path);

		DrawTexturePro(t, sourceRect, destRect, {}, 0, WHITE);
	  } else {
		const float x = get<0>(coord) * 24 * 3;
		const float y = get<1>(coord) * 24 * 3;

		const Rectangle destRect = {x, y, sourceRect.width * 3, sourceRect.height * 3};
		string path;
		if (tile->getImage() != "") {
		  path = tile->getImage().string();
		} else {
		  path = tile->getTileset()->getImagePath().string();
		}

		path = path.replace(0, 2, "assets");
		Texture2D t = tileTextures.at(path);

		DrawTexturePro(t, sourceRect, destRect, {}, 0, WHITE);
	  }

	}
  }
}

void Game::DrawInteractables() {
  for (auto &s : shops) {
	s.Draw();
  }
}
