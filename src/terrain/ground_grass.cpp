#include "raylib.h"
#include "block.cpp"

extern float scale;

class GroundGrass : public Block {
 public:
  GroundGrass(Vector2 pos, const Texture2D* tex) : Block(pos, tex) {
	sourceRect =  {24 * 2 , 0, 24, 24};
  }
};