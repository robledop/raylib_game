#include "raylib.h"

class GroundGrass {
  Texture2D texture;
  Rectangle middleRect = {24 * 3, 0, 24 * 3, 24 * 3};
  Rectangle leftRect = {0, 0, 24 * 3, 24 * 3};
  Rectangle rightRect = {24 * 3 * 4, 0, 24 * 3, 24 * 3};
  int size;

 public:
  GroundGrass(int size) {
	this->size = size;

	texture = LoadTexture(ASSETS_PATH"oak_woods_tileset.png");
	texture.width *= 3;
	texture.height *= 3;
  }

  void Draw(int x, int y) {
	for (int i = 0; i < size; i++) {
	  if (i == 0) {
		DrawTextureRec(texture, leftRect, {x + i * 24.0f * 3, (float)y}, WHITE);
	  } else if (i == size - 1) {
		DrawTextureRec(texture, rightRect, {x + i * 24.0f * 3, (float)y}, WHITE);
	  } else {
		DrawTextureRec(texture, middleRect, {x + i * 24.0f * 3, (float)y}, WHITE);
	  }
	}
  }
};