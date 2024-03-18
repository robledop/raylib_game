#include "raylib.h"
#include "config.h"
#include "player.cpp"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#include "ground_grass.cpp"

int groundLevel;
int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);
  groundLevel = GetScreenHeight() - 100;

  Texture2D background1 = LoadTexture(ASSETS_PATH"background_layer_1.png");
  Texture2D background2 = LoadTexture(ASSETS_PATH"background_layer_2.png");
  Texture2D background3 = LoadTexture(ASSETS_PATH"background_layer_3.png");

  GroundGrass groundGrass{1000, -1000, groundLevel};

  float bg1X{};
  float bg2X{};
  float bg3X{};

  auto player = Player{};

  Camera2D camera = {0};
//  camera.target = player.position;
  camera.target = {player.position.x, (float)groundLevel - 530};
  camera.offset = {GetScreenWidth() / 2.0f - player.GetWidth() / 2, GetScreenHeight() / 2.0f};

  camera.zoom = 1.0f;
  auto groundColor = GREEN;

  while (!WindowShouldClose()) {
	float deltaTime = GetFrameTime();
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
//	camera.target = player.position;
	camera.target = {player.position.x, (float)groundLevel - 530};
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
	  bg3X -= 5;

	  if (bg1X <= -background1.width * 6) bg1X = 0;
	  if (bg2X <= -background2.width * 6) bg2X = 0;
	  if (bg3X <= -background3.width * 6) bg3X = 0;
	}

	if (player.direction == LEFT && !player.attacking) {
	  bg1X += 1;
	  bg2X += 2;
	  bg3X += 3;

	  if (bg1X >= 0) bg1X = -background1.width * 6;
	  if (bg2X >= 0) bg2X = -background2.width * 6;
	  if (bg3X >= 0) bg3X = -background3.width * 6;
	}

	Vector2 bg1Pos{bg1X, 0};
	Vector2 bg1Pos_2{bg1X + background1.width * 6, 0};
	Vector2 bg2Pos{bg2X, 0};
	Vector2 bg2Pos_2{bg2X + background2.width * 6, 0};

	Vector2 bg3Pos{bg3X, 0};
	Vector2 bg3Pos_2{bg3X + background3.width * 6, 0};

	BeginDrawing();
	{
	  ClearBackground(BLUE);

	  DrawTextureEx(background1, bg1Pos, 0.0f, 6.0f, WHITE);
	  DrawTextureEx(background1, bg1Pos_2, 0.0f, 6.0f, WHITE);
	  DrawTextureEx(background2, bg2Pos, 0.0f, 6.0f, WHITE);
	  DrawTextureEx(background2, bg2Pos_2, 0.0f, 6.0f, WHITE);
	  DrawTextureEx(background3, bg3Pos, 0.0f, 6.0f, WHITE);
	  DrawTextureEx(background3, bg3Pos_2, 0.0f, 6.0f, WHITE);

	  BeginMode2D(camera);
	  {
		player.draw();
//		DrawCircle(0, groundLevel - 500, 100, RED);
		groundGrass.Draw();
	  }
	  EndMode2D();

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
