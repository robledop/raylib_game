#include "raylib.h"
#include "config.h"
#include "player.cpp"

int groundLevel;
int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  groundLevel = GetScreenHeight() - 100;
  Rectangle buildings[10] = {0};

  for (auto &building : buildings) {
	building.x = GetRandomValue(-1000, 2000);
	building.y = groundLevel - 500;
	building.width = GetRandomValue(50, 200);
	building.height = 500;
  }

  auto player = Player{};

  Camera2D camera = {0};
  camera.target = player.position;
  camera.offset = {GetScreenWidth() / 2.0f - player.GetWidth() / 2, GetScreenHeight() / 2.0f};

  camera.zoom = 1.0f;
  auto groundColor = GREEN;

  while (!WindowShouldClose()) {
	groundLevel = GetScreenHeight() - 100;
	if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
	  if (IsWindowFullscreen()) {
		SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	  } else {
		SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
	  }

	  ToggleFullscreen();
	}

	// Camera target follows player
	camera.target = player.position;
	camera.offset = {GetScreenWidth() / 2.0f - player.GetWidth() / 2, GetScreenHeight() - 600.0f};

	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
	  player.direction = RIGHT;
	  player.lastDirection = RIGHT;
	} else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
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
		DrawRectangle(-1000, GetScreenHeight() - 100, 5000, 400, groundColor);
		DrawCircle(0, groundLevel - 500, 100, RED);
	  }
	  EndMode2D();


	  // Stats
	  DrawText(TextFormat("Player x: %f", player.position.x), 10, 10, 50, WHITE);
	  DrawText(TextFormat("Player y: %f", player.position.y), 10, 60, 50, WHITE);
	  DrawText(TextFormat("Ground level: %d", groundLevel), 10, 100, 50, WHITE);
	  DrawText(TextFormat("Screen height: %d", GetScreenHeight()), 10, 150, 50, WHITE);
	  DrawText(TextFormat("Screen width: %d", GetScreenWidth()), 10, 200, 50, WHITE);
	  DrawText(TextFormat("Player height: %f", player.GetHeight()), 10, 250, 50, WHITE);
	  DrawText(TextFormat("Player width: %f", player.GetWidth()), 10, 300, 50, WHITE);
	  DrawText(TextFormat("Camera x: %f", camera.target.x), 10, 350, 50, WHITE);
	  DrawText(TextFormat("Camera y: %f", camera.target.y), 10, 400, 50, WHITE);
	  DrawText(TextFormat("Camera offset x: %f", camera.offset.x), 10, 450, 50, WHITE);
	  DrawText(TextFormat("Camera offset y: %f", camera.offset.y), 10, 500, 50, WHITE);

	  // Guide lines
	  DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), RED);
	}
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
