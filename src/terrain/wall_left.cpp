#include "block.cpp"

extern float scale;

class WallLeft : public Block {
 public:
  WallLeft(Vector2 pos, const Texture2D *tex) : Block(pos, tex) {
	sourceRect = {0, 24 * 1, 24, 24};
  }
};