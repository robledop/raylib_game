#include "config.h"
#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "game.h"
#include "include/raygui.h"

float scale;
int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  scale = MIN((float)GetScreenWidth() / SCREEN_WIDTH,
			  (float)GetScreenHeight() / SCREEN_HEIGHT);

  const RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  SetTextureFilter(target.texture,
				   TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use
  Game game{};

  // Uncomment to disable ESC for exiting the game
  // SetExitKey(0);

  while (!WindowShouldClose()) {
	// Update virtual mouse (clamped mouse value behind game screen)
	const Vector2 mouse = GetMousePosition();
	Vector2 virtualMouse = {0};
	virtualMouse.x =
		(mouse.x - (static_cast<float>(GetScreenWidth()) - (SCREEN_WIDTH * scale))) / scale;
	virtualMouse.y =
		(mouse.y - (static_cast<float>(GetScreenHeight()) - (SCREEN_HEIGHT * scale))) / scale;
	virtualMouse = Vector2Clamp(
		virtualMouse, {0, 0},
		{static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)});

	// Apply the same transformation as the virtual mouse to the real mouse
	// (i.e. to work with raygui)
	// SetMouseOffset(-(GetScreenWidth() - (gameScreenWidth*scale))*0.5f,
	// -(GetScreenHeight() - (gameScreenHeight*scale))*0.5f);
	// SetMouseScale(1/scale, 1/scale);

	if (IsKeyPressed(KEY_ENTER) &&
		(IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
	  ToggleFullscreen();
	}

	// Draw everything in the render texture, note this will not be rendered on
	// screen, yet
	BeginTextureMode(target);
	ClearBackground(BLACK);

	game.Draw();

#ifdef BG_LOG
	DrawText(TextFormat("bg3X RED: %f", bg3X), 10, 10, 50, WHITE);
	DrawText(TextFormat("bg3X_2 BLUE: %f", bg3X + background3.width * 6), 10,
			 60, 50, WHITE);
	DrawText(TextFormat("background3.width * 6: %d", background3.width * 6), 10,
			 110, 50, WHITE);
	DrawText(TextFormat("background3.width: %d", background3.width), 10, 160,
			 50, WHITE);
#endif

#ifdef FPS
	DrawFPS(SCREEN_WIDTH - 100, 10);
#endif

	//	DrawText(TextFormat("Default Mouse: [%i , %i]",
	//static_cast<int>(mouse.x), static_cast<int>(mouse.y)), 			 350, 			 25, 			 20,
	//			 GREEN);
	//	DrawText(TextFormat("Virtual Mouse: [%i , %i]",
	//static_cast<int>(virtualMouse.x), static_cast<int>(virtualMouse.y)), 			 350,
	//			 55,
	//			 20,
	//			 YELLOW);

	EndTextureMode();

	BeginDrawing();
	ClearBackground(BLACK);

	// Draw render texture to screen, properly scaled
	const Rectangle source = {0.0f, 0.0f,
							  static_cast<float>(target.texture.width),
							  static_cast<float>(-target.texture.height)};
	const Rectangle dest = {(static_cast<float>(GetScreenWidth()) -
		(static_cast<float>(SCREEN_WIDTH) * scale)) *
		0.5f,
							(static_cast<float>(GetScreenHeight()) -
								(static_cast<float>(SCREEN_HEIGHT) * scale)) *
								0.5f,
							static_cast<float>(SCREEN_WIDTH) * scale,
							static_cast<float>(SCREEN_HEIGHT) * scale};

	DrawTexturePro(target.texture, source, dest, {0, 0}, 0.0f, WHITE);
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
