#ifndef RAYLIB_GAME_SRC_MENU_H_
#define RAYLIB_GAME_SRC_MENU_H_
#include "raylib.h"
#include "game.h"

class Menu {
  bool *showMenu;
  bool *toggleFullscreen;
  bool *showCollisionBoxes;
  bool *showFPS;
  bool *showDebugInfo;
  Game *game;
  
  int menuButtonSelected = -1;
  Rectangle fullScreenButtonPosition;
  Rectangle restartGameButtonPosition;
  Rectangle showCollisionBoxesButtonPosition;
  Rectangle showFPSButtonPosition;
  Rectangle showDebugInfoButtonPosition;
  Rectangle exitButtonPosition;

  void StartGame();

 public:
  Menu(Game *game, bool *showMenu, bool *toggleFullScreen, bool *showCollisionBoxes, bool *showFPS, bool* showDebugInfo) : showMenu{
	  showMenu},
																									  toggleFullscreen{
																										  toggleFullScreen},
																									  showCollisionBoxes{
																										  showCollisionBoxes},
																									  showFPS{showFPS},
																									  showDebugInfo{showDebugInfo},
																									  game(game) {};
  void GuiWindowFloating(Vector2 *position,
						 Vector2 *size,
						 Vector2 content_size,
						 const char *title);

  void DrawContent(Vector2 position);
};

#endif
