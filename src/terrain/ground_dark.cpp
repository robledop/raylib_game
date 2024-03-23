#include "block.cpp"

class GroundDark : public Block {
 public:
  GroundDark(Vector2 pos, const Texture2D* tex, bool blocking = true) : Block(pos, tex, blocking) {
	sourceRect =  {24 * 1, 24 * 1, 24, 24};
  }
};