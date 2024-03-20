#include "raylib.h"
extern float scale;

class GroundGrass {
  Texture2D texture;
  Rectangle middleRect = {24 * 3, 0, 24 * 3, 24 * 3};
  float width;
  float height;

 public:
  int x;
  int y;
  GroundGrass(int x, int y) {
	this->x = x;
	this->y = y;

	texture = LoadTexture(ASSETS_PATH"oak_woods_tileset.png");
	width = texture.width;
	height = texture.height;
  }

  /// 
  /// \param px - player x
  /// \param py - player y 
  /// \param pw - player width 
  /// \param ph - player height 
  /// \return 
  bool CheckCollision(int px, int py, int pw, int ph) {
	float center = pw / 2;
	float characterWidth = pw / 8;
	return (px < (x - center + characterWidth + 10) && (px + center + 10) > x) &&
		(py + ph - 40 < y && py + ph + 5  > y);
  }

  void Draw() {
	texture.width = width * scale * 3;
	texture.height = width * scale * 3;

	DrawTextureRec(texture, middleRect, {(float)x, (float)y}, WHITE);
	DrawRectangle(x, y, 10, 10, RED);
  }
};