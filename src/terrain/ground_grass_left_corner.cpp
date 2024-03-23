#include "raylib.h"
#include "block.cpp"

extern float scale;

class GroundGrassLeftCorner : public Block {
 public:
  GroundGrassLeftCorner(Vector2 pos, const Texture2D* tex) : Block(pos, tex) {
	sourceRect =  {0, 0, 24, 24};
  }
};