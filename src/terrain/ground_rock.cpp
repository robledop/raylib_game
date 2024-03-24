#include "raylib.h"
#include "block.cpp"

extern float scale;

class GroundRock : public Block {
 public:
  GroundRock(Vector2 pos, const Texture2D* tex) : Block(pos, tex) {
	sourceRect =  {24 * 7 , 0, 24, 24};
  }
};
