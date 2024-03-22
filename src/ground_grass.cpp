#include "raylib.h"
extern float scale;

class GroundGrass {
  Texture2D texture;
  Rectangle middleRect = {24 * 3, 0, 24 * 3, 24 * 3};
  float width;
  float height;

 public:
  float x;
  float y;
  GroundGrass(float x, float y) {
	this->x = x;
	this->y = y;

	texture = LoadTexture(ASSETS_PATH"oak_woods_tileset.png");
	width = texture.width;
	height = texture.height;
  }

  bool CheckCollision(Rectangle hitbox, float playerSpeed) {

	bool collision = (hitbox.x <= (x + width) && hitbox.x + hitbox.width >= x)
		&& hitbox.y + hitbox.height <= y + playerSpeed * GetFrameTime()
		&& hitbox.y + hitbox.height >= y - playerSpeed * GetFrameTime();
	if (collision) {
	  return true;
	}
	return false;

//	return (px < (x - center + characterWidth) && (px + center ) > x) &&
//		(py + ph - 40 < y && py + ph + 5  > y);
  }

  void Draw() {
	texture.width = width * scale * 3;
	texture.height = width * scale * 3;

	DrawTextureRec(texture, middleRect, {(float)x, (float)y}, WHITE);
	DrawRectangle(x, y, 10, 10, RED);
//	DrawRectangleRec({x, y, middleRect.width, middleRect.height}, GREEN);
  }
};