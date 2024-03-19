#include "raylib.h"
extern float scale;

class GroundGrass {
  Texture2D texture;
  Rectangle middleRect = {24 * 3, 0, 24 * 3, 24 * 3};
  Rectangle leftRect = {0, 0, 24 * 3, 24 * 3};
  Rectangle rightRect = {24 * 3 * 4, 0, 24 * 3, 24 * 3};
  int size;
  float width;
  float height;

 public:
  GroundGrass(int size) {
	this->size = size;

	texture = LoadTexture(ASSETS_PATH"oak_woods_tileset.png");
	width = texture.width;
	height = texture.height;
  }

  void Draw(int x, int y) {
	texture.width = width * scale * 3;
	texture.height = width * scale * 3;
	
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