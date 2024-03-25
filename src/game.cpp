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

//  if (player.direction == RIGHT && !player.attacking && !player.blocked && !player.isDead
//	  && player.position.x<maxX && player.position.x>minX) {
//	bg1X -= 1;
//	bg2X -= 2;
//	bg3X -= 3;
//
//	if (bg1X <= -background1.width * scale * BG_SCALE) bg1X = 0;
//	if (bg2X <= -background2.width * scale * BG_SCALE) bg2X = 0;
//	if (bg3X <= -background3.width * scale * BG_SCALE) bg3X = 0;
//  }

//  if (player.direction == LEFT && !player.attacking && !player.blocked && !player.isDead && player.position.x > minX
//	  && player.position.x < maxX) {
//	bg1X += 1;
//	bg2X += 2;
//	bg3X += 3;
//
//	if (bg1X >= 0) bg1X = -background1.width * scale * BG_SCALE;
//	if (bg2X >= 0) bg2X = -background2.width * scale * BG_SCALE;
//	if (bg3X >= 0) bg3X = -background3.width * scale * BG_SCALE;
//  }

//  Vector2 bg1Pos{bg1X, 0};
//  Vector2 bg1Pos_2{bg1X + background1.width * scale * BG_SCALE, 0};
//  Vector2 bg2Pos{bg2X, 0};
//  Vector2 bg2Pos_2{bg2X + background2.width * scale * BG_SCALE, 0};
//
//  Vector2 bg3Pos{bg3X, 0};
//  Vector2 bg3Pos_2{bg3X + background3.width * scale * BG_SCALE, 0};

//  DrawTextureEx(background1, bg1Pos, 0.0f, scale * BG_SCALE, WHITE);
//  DrawTextureEx(background1, bg1Pos_2, 0.0f, scale * BG_SCALE, WHITE);
//  DrawTextureEx(background2, bg2Pos, 0.0f, scale * BG_SCALE, WHITE);
//  DrawTextureEx(background2, bg2Pos_2, 0.0f, scale * BG_SCALE, WHITE);
//  DrawTextureEx(background3, bg3Pos, 0.0f, scale * BG_SCALE, WHITE);
//  DrawTextureEx(background3, bg3Pos_2, 0.0f, scale * BG_SCALE, WHITE);


  BeginMode2D(camera);
  {

	for (auto &terrain : terrains) {
	  auto [collision, yPos] = terrain.CheckTopCollision(player.hitbox, player.upwardsVelocity);
	  if (!collision && round(player.position.y) != round(yPos - player.GetTextureHeight())) {
		player.SetOnGround(false);
	  } else if (collision) {
		player.SetOnGround(true);
		player.position.y = yPos - player.GetTextureHeight();
		player.upwardsVelocity = 0;
		player.falling = false;
	  }

	  auto [sideCollision, xPos] = terrain.CheckSideCollision(player.hitbox, RUN_SPEED + player.upwardsVelocity / 2.0f);
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
	}

	DrawTileMap();
	player.draw();
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
  map = tileson.parse("../assets/tiled/level1.json");
  if (map->getStatus() == tson::ParseStatus::OK) {
	//Get color as a rgba color object
//	tson::Colori bgColor = map->getBackgroundColor(); //RGBA with 0-255 on each channel

	//This color can be compared with Tiled hex string
//	if (bgColor == "#ffaa07")
//	  printf("Cool!");

	//Or you can compare them with other colors
//	tson::Colori otherColor{255, 170, 7, 255};
//	if (bgColor == otherColor)
//	  printf("This works, too!");

	//You can also get the color as float, transforming values if they are already in their int form, from max 255 to 1.f
//	tson::Colorf bgColorFloat = bgColor.asFloat();

	//Or the other way around
//	tson::Colori newBg = bgColorFloat.asInt();

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

	tson::Layer *layer = map->getLayer("Main Layer");
	tson::Tileset *tileset = map->getTileset("oak_woods_tileset");
	tson::Tile *tile = tileset->getTile(1);

	//For tile layers, you can get the tiles presented as a 2D map by calling getTileData()
	//Using x and y positions in tile units.
	if (layer->getType() == tson::LayerType::TileLayer) {
	  //When the map is of a fixed size, you can get the tiles like this
	  if (!map->isInfinite()) {
		tileData = layer->getTileData();

		for (auto t : tileData) {
		  Vector2 pos = {static_cast<float>(get<0>(t.first) * 24 * 3), static_cast<float>(get<1>(t.first) * 24 * 3)};
		  auto drawingRect = t.second->getDrawingRect();
		  Rectangle collisionRect = {
			  static_cast<float>(pos.x),
			  static_cast<float>(pos.y),
			  static_cast<float>(drawingRect.width * 3 * scale),
			  static_cast<float>(drawingRect.height * 3 * scale)
		  };

		  Terrain terrain = Terrain(pos, collisionRect, true);
		  terrains.push_back(terrain);
		}

		//Unsafe way to get a tile
		tson::Tile *invalidTile = tileData[{0, 4}]; // x:0,  y:4  - There is no tile here, so this will be nullptr.
		// Be careful with this, as it expands the map with an ID of {0,4} pointing
		// to a nullptr...

		//Individual tiles should be retrieved by calling the safe version:
		tson::Tile *safeInvalid = layer->getTileData(0, 5); //Another non-existent tile, but with safety check.
		//Will not expand the map with a nullptr

		tson::Tile
			*tile1 = layer->getTileData(4, 4);       //x:4,  y:4  - Points to tile with ID 1 (Tiled internal ID: 0)
		tson::Tile
			*tile2 = layer->getTileData(5, 4);       //x:5,  y:4  - Points to tile with ID 3 (Tiled internal ID: 2)
		tson::Tile
			*tile3 = layer->getTileData(8, 14);      //x:8,  y:14 - Points to tile with ID 2 (Tiled internal ID: 1)
		tson::Tile
			*tile4 = layer->getTileData(17, 5);      //x:17, y:5  - Points to tile with ID 5 (Tiled internal ID: 4)


		//New in v1.2.0
		//You can now get tiles with positions and drawing rect via tson::TileObject
		//Drawing rects are also accessible through tson::Tile.
		tson::TileObject *tileobj1 = layer->getTileObject(0, 5);
		tson::Tile *tileobj1Data = layer->getTileData(0, 5);

		tson::Vector2f position = tileobj1->getPosition();
		tson::Rect drawingRect = tileobj1->getDrawingRect();

		//You can of course also loop through every tile!
		for (const auto &[id, tile] : tileData) {
		  //Must check for nullptr, due to how we got the first invalid tile (pos: 0, 4)
		  //Would be unnecessary otherwise.
		  if (tile != nullptr)
			int tileId = tile->getId(); //A bit verbose, as this is the same as id from the key, but you get the idea.
		}
	  }
	}

	//If an object supports properties, you can easily get a property value by calling get<T>() or the property itself with getProp()
	int myInt = layer->get<int>("my_int");
	float myFloat = layer->get<float>("my_float");
	bool myBool = layer->get<bool>("my_bool");
	std::string myString = layer->get<std::string>("my_string");
	tson::Colori myColor = layer->get<tson::Colori>("my_color");

	fs::path file = layer->get<fs::path>("my_file");

	tson::Property *prop = layer->getProp("my_property");
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
