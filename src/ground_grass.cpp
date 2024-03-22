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

  bool CheckTopCollision(Rectangle hitbox, float playerSpeed) {
	return (hitbox.x < (x + middleRect.width) && hitbox.x + hitbox.width > x)
		&& hitbox.y + hitbox.height <= y + playerSpeed * GetFrameTime()
		&& hitbox.y + hitbox.height >= y - 10 - playerSpeed * GetFrameTime();
  }

  bool CheckSideCollision(Rectangle hitbox, float playerSpeed) {
	return hitbox.y < y + middleRect.height && hitbox.y + hitbox.height > y
		&& ((hitbox.x + hitbox.width <= x + playerSpeed * GetFrameTime()
			&& hitbox.x + hitbox.width >= x - 10 - playerSpeed * GetFrameTime())
			|| (hitbox.x >= x + middleRect.width - playerSpeed * GetFrameTime()
				&& hitbox.x <= x + middleRect.width + 10 + playerSpeed * GetFrameTime()));
  }

  void Draw() {
	texture.width = width * scale * 3;
	texture.height = width * scale * 3;

	DrawTextureRec(texture, middleRect, {(float)x, (float)y}, WHITE);
	
#ifdef GUIDES
	DrawRectangle(x, y, 10, 10, RED);
#endif
  }
};