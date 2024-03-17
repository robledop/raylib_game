#include "raylib.h"
#include "config.h"
#include "player.cpp"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);
  Rectangle buildings[10] = {0};

  for (int i = 0; i < 10; i++) {
	buildings[i].x = GetRandomValue(-1000, 2000);
	buildings[i].y = GROUND_LEVEL - 500;
	buildings[i].width = GetRandomValue(50, 200);
	buildings[i].height = 500;
  }

  auto player = Player();
  player.y = GROUND_LEVEL;
  player.x = 100;

  Camera2D camera = {0};
  camera.target = (Vector2){player.x, player.y};
  camera.offset = (Vector2){SCREEN_WIDTH / 2.0f, GROUND_LEVEL};
  camera.rotation = 0.0f;

  camera.zoom = 1.0f;
  Color groundColor = GREEN;
  while (!WindowShouldClose()) {
	// Camera target follows player
	camera.target = (Vector2){static_cast<float>(player.x), static_cast<float>(player.y)};

	if (IsKeyDown(KEY_RIGHT)) { player.direction = RIGHT; }
	else if (IsKeyDown(KEY_LEFT)) { player.direction = LEFT; }
	else { player.direction = STOP; }

	BeginDrawing();
	ClearBackground(BLUE);

	BeginMode2D(camera);
	  for (auto building : buildings) {
		DrawRectangleRec(building, GRAY);
	  }

	  player.draw();
	EndMode2D();
	
	DrawRectangle(0, GROUND_LEVEL - 60, SCREEN_WIDTH, SCREEN_HEIGHT / 4, groundColor);
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
