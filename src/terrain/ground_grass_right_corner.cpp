#include "block.cpp"

extern float scale;

class GroundGrassRightCorner : public Block {
 public:
  GroundGrassRightCorner(Vector2 pos,const Texture2D *tex) : Block(pos, tex) {
	sourceRect = {24 * 3, 0, 24, 24};
  }
};