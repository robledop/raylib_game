#include "raylib.h"
#include "config.h"
#include "player.cpp"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#include "level_loader.cpp"

int groundLevel;
float scale;
int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);
  auto loader = LevelLoader{ASSETS_PATH"levels/level1.txt"};
  groundLevel = -1000;
  scale = min((float)GetScreenWidth() / SCREEN_WIDTH, (float)GetScreenHeight() / SCREEN_HEIGHT);

  Texture2D background1 = LoadTexture(ASSETS_PATH"background_layer_1.png");
  Texture2D background2 = LoadTexture(ASSETS_PATH"background_layer_2.png");
  Texture2D background3 = LoadTexture(ASSETS_PATH"background_layer_3.png");

  float bg1X{};
  float bg2X{};
  float bg3X{};

  auto player = Player{};

  Camera2D camera = {0};

  camera.zoom = 1.0f;

  player.position.y = 685;
  while (!WindowShouldClose()) {
	if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
	  if (IsWindowFullscreen()) {
		SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		scale = min((float)GetScreenWidth() / SCREEN_WIDTH, (float)GetScreenHeight() / SCREEN_HEIGHT);
	  } else {
		SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
		scale = min((float)GetScreenWidth() / SCREEN_WIDTH, (float)GetScreenHeight() / SCREEN_HEIGHT);
	  }

	  ToggleFullscreen();
	}

	camera.target = {player.position.x , player.position.y - 100};
	camera.offset = {GetScreenWidth() / 2.0f - player.GetWidth() / 2, GetScreenHeight() - 600.0f};

	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
	  player.direction = RIGHT;
	  player.lastDirection = RIGHT;
	} else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
	  player.direction = LEFT;
	  player.lastDirection = LEFT;
	} else { player.direction = STOP; }

	if (player.direction == RIGHT && !player.attacking) {
	  bg1X -= 1;
	  bg2X -= 2;
	  bg3X -= 3;

	  if (bg1X <= -background1.width * scale * BG_SCALE) bg1X = 0;
	  if (bg2X <= -background2.width * scale * BG_SCALE) bg2X = 0;
	  if (bg3X <= -background3.width * scale * BG_SCALE) bg3X = 0;
	}

	if (player.direction == LEFT && !player.attacking) {
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

	BeginDrawing();
	{
	  ClearBackground(BLUE);

	  DrawTextureEx(background1, bg1Pos, 0.0f, scale * BG_SCALE, WHITE);
	  DrawTextureEx(background1, bg1Pos_2, 0.0f, scale * BG_SCALE, WHITE);
	  DrawTextureEx(background2, bg2Pos, 0.0f, scale * BG_SCALE, WHITE);
	  DrawTextureEx(background2, bg2Pos_2, 0.0f, scale * BG_SCALE, WHITE);
	  DrawTextureEx(background3, bg3Pos, 0.0f, scale * BG_SCALE, WHITE);
	  DrawTextureEx(background3, bg3Pos_2, 0.0f, scale * BG_SCALE, WHITE);

	  BeginMode2D(camera);
	  {
		loader.DrawLevel();
		player.draw();
	  }
	  EndMode2D();

	  if (loader.CheckCollision(player.position.x, player.position.y, player.GetWidth(), player.GetHeight())) {
		player.onGround = true;
	  } else {
		player.onGround = false;
	  }

#ifdef BG_LOG
	  DrawText(TextFormat("bg3X RED: %f", bg3X), 10, 10, 50, WHITE);
	  DrawText(TextFormat("bg3X_2 BLUE: %f", bg3X + background3.width * 6), 10, 60, 50, WHITE);
	  DrawText(TextFormat("background3.width * 6: %d", background3.width * 6), 10, 110, 50, WHITE);
	  DrawText(TextFormat("background3.width: %d", background3.width), 10, 160, 50, WHITE);
#endif

#ifdef LOG
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
	  DrawText(TextFormat("On ground: %b", player.onGround), 10, 550, 50, WHITE);

	  // Guide lines
	  DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), RED);
#endif

#ifdef FPS
	  DrawFPS(10, 10);
#endif
	}
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
