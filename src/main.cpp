#include "config.h"
#include "menu.h"

bool showCollisionBoxes{};
float scale;

int main() {
  unique_ptr<Game> game;
  unique_ptr<Menu> menu;

  bool showDebugInfo{};
  bool shouldClose{};
  bool showMenu{};
  bool toggleFullscreen{};
  bool showFPS{true};

  raylib::Window window(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  window.SetTargetFPS(60);
  window.SetConfigFlags(FLAG_VSYNC_HINT);

  scale = MIN((float)GetScreenWidth() / SCREEN_WIDTH,
			  (float)GetScreenHeight() / SCREEN_HEIGHT);

  raylib::RenderTexture2D target(SCREEN_WIDTH, SCREEN_HEIGHT);
  target.GetTexture().SetFilter(TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use

  SetExitKey(0);

  game = make_unique<Game>(&showDebugInfo);
  menu = make_unique<Menu>(game,
						   &showMenu,
						   &toggleFullscreen,
						   &showCollisionBoxes,
						   &showFPS,
						   &showDebugInfo,
						   &shouldClose);

  while (!window.ShouldClose() && !shouldClose) {
	if ((IsKeyPressed(KEY_ENTER) &&
		(IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) || toggleFullscreen) {
	  ToggleFullscreen();
	  toggleFullscreen = false;
	}

	if (IsKeyPressed(KEY_ESCAPE) || raylib::Gamepad(0).IsButtonPressed(GAMEPAD_BUTTON_MIDDLE_LEFT)) {
	  showMenu = !showMenu;
	}

	// Draw everything in the render texture, this will not be rendered on screen, yet
	target.BeginMode();
	window.ClearBackground(BLACK);

	if (game != nullptr) {
	  game->Draw();
	}

	if (showFPS) {
	  window.DrawFPS(SCREEN_WIDTH - 100, 10);
	}

	target.EndMode();

	window.BeginDrawing();

	const raylib::Rectangle source = {0.0f, 0.0f,
									  static_cast<float>(target.texture.width),
									  static_cast<float>(-target.texture.height)};
	const raylib::Rectangle dest = {(static_cast<float>(GetScreenWidth()) -
		(static_cast<float>(SCREEN_WIDTH) * scale)) *
		0.5f,
									(static_cast<float>(GetScreenHeight()) -
										(static_cast<float>(SCREEN_HEIGHT) * scale)) *
										0.5f,
									static_cast<float>(SCREEN_WIDTH) * scale,
									static_cast<float>(SCREEN_HEIGHT) * scale};

	target.GetTexture().Draw(source, dest, {0, 0}, 0.0f, WHITE);

	window.ClearBackground(BLACK);

	raylib::Vector2 menu_window_size = {400, 400};
	raylib::Vector2 menu_window_position = {SCREEN_WIDTH / 2 - (400 / 2), SCREEN_HEIGHT / 2 - (400 / 2)};

	if (showMenu) {
	  menu->GuiWindowFloating(&menu_window_position,
							  &menu_window_size,
							  {140, 320},
							  "Options");
	}
	window.EndDrawing();
  }

  game.release();

  return 0;
}

