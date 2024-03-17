#include "raylib.h"
#include "config.h"
#include "player.cpp"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);
  Rectangle buildings[10] = {0};

  for (auto &building : buildings) {
	building.x = GetRandomValue(-1000, 2000);
	building.y = GROUND_LEVEL - 500;
	building.width = GetRandomValue(50, 200);
	building.height = 500;
  }

  auto player = Player();
  
  Camera2D camera = {0};
  camera.target = player.position;
  camera.offset = player.position;
  camera.rotation = 0.0f;

  camera.zoom = 1.0f;
  auto groundColor = GREEN;
  while (!WindowShouldClose()) {
	// Camera target follows player
	camera.target = {player.position.x, GROUND_LEVEL - player.GetHeight()};

	if (IsKeyDown(KEY_RIGHT)) {
	  player.direction = RIGHT;
	  player.lastDirection = RIGHT;
	} else if (IsKeyDown(KEY_LEFT)) {
	  player.direction = LEFT;
	  player.lastDirection = LEFT;
	} else { player.direction = STOP; }

	BeginDrawing();
	{
	  ClearBackground(BLUE);

	  BeginMode2D(camera);
	  {
		for (auto building : buildings) {
		  DrawRectangleRec(building, DARKBLUE);
		}

		player.draw();
	  }
	  EndMode2D();

	  DrawRectangle(0, GROUND_LEVEL, SCREEN_WIDTH, SCREEN_HEIGHT / 4, groundColor);
	}
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
