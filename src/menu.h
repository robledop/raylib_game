#ifndef RAYLIB_GAME_SRC_MENU_H_
#define RAYLIB_GAME_SRC_MENU_H_
#include "game.h"

class Menu {
  bool *showMenu;
  bool *toggleFullscreen;
  bool *showCollisionBoxes;
  bool *showFPS;
  bool *showDebugInfo;
  bool *shouldClose;
  const unique_ptr<Game> &game;

  int menuButtonSelected = -1;
  raylib::Rectangle fullScreenButtonPosition;
  raylib::Rectangle restartGameButtonPosition;
  raylib::Rectangle showCollisionBoxesButtonPosition;
  raylib::Rectangle showFPSButtonPosition;
  raylib::Rectangle showDebugInfoButtonPosition;
  raylib::Rectangle exitButtonPosition;

  void StartGame();

 public:
  Menu(const unique_ptr<Game> &game,
	   bool *showMenu,
	   bool *toggleFullScreen,
	   bool *showCollisionBoxes,
	   bool *showFPS,
	   bool *showDebugInfo,
	   bool *shouldClose) : showMenu{showMenu},
							toggleFullscreen{toggleFullScreen},
							showCollisionBoxes{showCollisionBoxes},
							showFPS{showFPS},
							showDebugInfo{showDebugInfo},
							shouldClose{shouldClose},
							game(game) {};
  void GuiWindowFloating(Vector2 *position,
						 Vector2 *size,
						 Vector2 content_size,
						 const char *title);

  void DrawContent(Vector2 position);
  void Quit();
};

#endif
