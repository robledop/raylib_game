#ifndef RAYLIB_GAME_SRC_MENU_H_
#define RAYLIB_GAME_SRC_MENU_H_
#include "raylib.h"
#include "game.h"

#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#endif

class Menu {
  bool showMenu{true};
  bool toggleFullscreen{false};
  bool showCollisionBoxes{false};
  Game *game;

  void StartGame();

 public:
  Menu(Game* game) : game(game) {};
  void GuiWindowFloating(Vector2 *position,
						 Vector2 *size,
						 Vector2 content_size,
						 Vector2 *scroll,
						 const char *title);

  void DrawContent(Vector2 position, Vector2 scroll);
};

#endif
