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

  bool CheckCollision(int px, int py, int pw, int ph) {
	float center = pw / 2;
	float characterWidth = pw / 8;
	return (px < (x - center + characterWidth + 10) && (px + center + 10) > x) &&
		(py < y && py + ph > y);
  }

  void Draw() {
	texture.width = width * scale * 3;
	texture.height = width * scale * 3;

	DrawTextureRec(texture, middleRect, {(float)x, (float)y}, WHITE);
  }
};