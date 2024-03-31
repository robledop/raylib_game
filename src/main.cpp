#include "config.h"
#include "raylib.h"
#include "raymath.h"
#include "menu.h"

static Vector2 window_size = {400, 400};
static Vector2 window_position = {SCREEN_WIDTH / 2 - (400 / 2), SCREEN_HEIGHT / 2 - (400 / 2)};
static bool showMenu{};
static bool toggleFullscreen{};
static bool showFPS{true};
bool showDebugInfo{false};
bool showCollisionBoxes{};

float scale;
Game *game;
Menu *menu;

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  scale = MIN((float)GetScreenWidth() / SCREEN_WIDTH,
			  (float)GetScreenHeight() / SCREEN_HEIGHT);

  const RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  SetTextureFilter(target.texture,
				   TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use

  // Uncomment to disable ESC for exiting the game
  SetExitKey(0);

  game = new Game{&showDebugInfo};
  menu = new Menu{game, &showMenu, &toggleFullscreen, &showCollisionBoxes, &showFPS, &showDebugInfo};

  while (!WindowShouldClose()) {
	if ((IsKeyPressed(KEY_ENTER) &&
		(IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) || toggleFullscreen) {
	  ToggleFullscreen();
	  toggleFullscreen = false;
	}

	if (IsKeyPressed(KEY_ESCAPE) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_LEFT)) {
	  showMenu = !showMenu;
	}

	// Draw everything in the render texture, note this will not be rendered on
	// screen, yet
	BeginTextureMode(target);
	ClearBackground(BLACK);

	game->Draw();

	if (showFPS){
	  DrawFPS(SCREEN_WIDTH - 100, 10);
	}

	EndTextureMode();

	BeginDrawing();

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
	ClearBackground(BLACK);

	if (showMenu) {
	  menu->GuiWindowFloating(&window_position,
							  &window_size,
							  {140, 320},
							  "Options");
	}
	EndDrawing();
  }

  CloseWindow();

  return 0;
}

