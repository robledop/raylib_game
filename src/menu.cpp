#include "menu.h"
void Menu::GuiWindowFloating(Vector2 *position,
							 Vector2 *size,
							 Vector2 content_size,
							 Vector2 *scroll,
							 const char *title) {
#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

#if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
#define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
#endif

  int close_title_size_delta_half = (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2;

  // window movement and resize update
  if (GuiButton((Rectangle){position->x + size->x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half,
							position->y + close_title_size_delta_half,
							RAYGUI_WINDOW_CLOSEBUTTON_SIZE,
							RAYGUI_WINDOW_CLOSEBUTTON_SIZE},
				"#120#")) {
	showMenu = false;
  }

  if (showMenu) {
	showMenu = !GuiWindowBox((Rectangle){position->x, position->y, size->x, size->y}, title);
	  Rectangle scissor = {0};
	  GuiScrollPanel((Rectangle){position->x, position->y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, size->x,
								 size->y - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT},
					 NULL,
					 (Rectangle){position->x, position->y, content_size.x, content_size.y},
					 scroll,
					 &scissor);

	  bool require_scissor = size->x < content_size.x || size->y < content_size.y;

	  if (require_scissor) {
		BeginScissorMode(scissor.x, scissor.y, scissor.width, scissor.height);
	  }

	  DrawContent(*position, *scroll);

	  if (require_scissor) {
		EndScissorMode();
	  }

	// draw the resize button/icon
	GuiDrawIcon(71, position->x + size->x - 20, position->y + size->y - 20, 1, WHITE);
  }
}
void Menu::DrawContent(Vector2 position, Vector2 scroll) {
  bool restartGameButton =
	  GuiButton({position.x + 20 + scroll.x, position.y + 50 + scroll.y, 200, 25}, "Restart game");
  if (restartGameButton) {
	StartGame();
  }

  bool fullScreenButton =
	  GuiButton({position.x + 20 + scroll.x, position.y + 100 + scroll.y, 200, 25}, "Toggle fullscreen");
  if (fullScreenButton) {
	toggleFullscreen = true;
  }

  GuiCheckBox({position.x + 20 + scroll.x, position.y + 150 + scroll.y, 25, 25},
			  "Show collision boxes",
			  &showCollisionBoxes);

  bool exitButton = GuiButton({position.x + 20 + scroll.x, position.y + 300 + scroll.y, 100, 25}, "Quit");
  if (exitButton) {
	CloseWindow();
  }
}

void Menu::StartGame() {
  if (game != nullptr) {
	delete game;
  }
  game = new Game{};
}
