#include "block.cpp"

extern float scale;

class WallRight : public Block {
 public:
  WallRight(Vector2 pos, const Texture2D* tex) : Block(pos, tex) {
	sourceRect =  {24 * 3, 24 * 2, 24, 24};
  }
};
