#include "menu.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

void Menu::GuiWindowFloating(Vector2 *position,
							 Vector2 *size,
							 Vector2 content_size,
							 const char *title) {
#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

#if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
#define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
#endif

  if (showMenu) {
	*showMenu = !GuiWindowBox({position->x, position->y, size->x, size->y}, title);
	DrawContent(*position);
  }
}
void Menu::DrawContent(Vector2 position) {
  restartGameButtonPosition = {
	  .x = position.x + 20,
	  .y = position.y + 50,
	  .width = 200,
	  .height = 25
  };
  bool restartGameButton = GuiButton(restartGameButtonPosition, "Restart game");
  if (restartGameButton) {
	StartGame();
  }

  fullScreenButtonPosition = {
	  .x =position.x + 20,
	  .y = position.y + 50 + 28,
	  .width= 200,
	  .height= 25
  };

  bool fullScreenButton = GuiButton(fullScreenButtonPosition, "Toggle fullscreen");
  if (fullScreenButton) {
	*toggleFullscreen = true;
  }

  showCollisionBoxesButtonPosition = {
	  .x =position.x + 20,
	  .y = position.y + 50 + 28 * 2,
	  .width =25,
	  .height = 25
  };

  GuiCheckBox(showCollisionBoxesButtonPosition,
			  "Show collision boxes",
			  showCollisionBoxes);

  showFPSButtonPosition = {
	  .x = position.x + 20,
	  .y = position.y + 50 + 28 * 3,
	  .width= 25,
	  .height = 25
  };

  GuiCheckBox(showFPSButtonPosition,
			  "Show FPS",
			  showFPS);

  showDebugInfoButtonPosition = {
	  .x = position.x + 20,
	  .y = position.y + 50 + 28 * 4,
	  .width = 25,
	  .height = 25
  };

  GuiCheckBox(showDebugInfoButtonPosition,
			  "Show debug info",
			  showDebugInfo);

  exitButtonPosition = {
	  .x = position.x + 20,
	  .y = position.y + 300,
	  .width = 100,
	  .height = 25
  };

  bool exitButton = GuiButton(exitButtonPosition, "Quit");
  if (exitButton) {
	Quit();
  }

  if (GetMouseDelta().y > 0.f) {
	menuButtonSelected = -1;
  }

  if (IsKeyPressed(KEY_DOWN) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
	menuButtonSelected++;
  }

  if (IsKeyPressed(KEY_UP) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
	menuButtonSelected--;
  }

  if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
	switch (menuButtonSelected) {
	  case 1: StartGame();
		break;
	  case 2: *toggleFullscreen = true;
		break;
	  case 3: *showCollisionBoxes = !*showCollisionBoxes;
		break;
	  case 4: *showFPS = !*showFPS;
		break;
	  case 5: *showDebugInfo = !*showDebugInfo;
		break;
	  case 6: Quit();
		break;
	}
  }

  switch (menuButtonSelected) {
	case 1:
	  SetMousePosition(restartGameButtonPosition.x + restartGameButtonPosition.width - 1,
					   restartGameButtonPosition.y + restartGameButtonPosition.height - 1);
	  break;
	case 2:
	  SetMousePosition(fullScreenButtonPosition.x + fullScreenButtonPosition.width - 1,
					   fullScreenButtonPosition.y + fullScreenButtonPosition.height - 1);
	  break;
	case 3:
	  SetMousePosition(showCollisionBoxesButtonPosition.x + showCollisionBoxesButtonPosition.width - 1,
					   showCollisionBoxesButtonPosition.y + showCollisionBoxesButtonPosition.height - 1);
	  break;
	case 4:
	  SetMousePosition(showFPSButtonPosition.x + showFPSButtonPosition.width - 1,
					   showFPSButtonPosition.y + showFPSButtonPosition.height - 1);
	  break;
	case 5:
	  SetMousePosition(showDebugInfoButtonPosition.x + showDebugInfoButtonPosition.width - 1,
					   showDebugInfoButtonPosition.y + showDebugInfoButtonPosition.height - 1);
	  break;
	case 6:
	  SetMousePosition(exitButtonPosition.x + exitButtonPosition.width - 1,
					   exitButtonPosition.y + exitButtonPosition.height - 1);
	  break;
	case 7: menuButtonSelected = 1;
	  break;
	case 0: menuButtonSelected = 6;
	  break;
  }
}

void Menu::StartGame() {
  *showMenu = false;
  game->Start();
}

void Menu::Quit() {
  *shouldClose = true;
}
