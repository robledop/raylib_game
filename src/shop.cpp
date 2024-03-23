#include "raylib.h"
#include "animation.cpp"

extern float scale;

class Shop {
 private:
  Vector2 position;
  Animation animation{
	  ASSETS_PATH"decorations/shop_anim.png",
	  6,
	  1.0f / 12.0f
  };

 public:
  Shop(Vector2 pos) {
	position = {pos.x, pos.y - animation.GetTextureHeight() + 24 * 3 * scale};
  }

  void Draw() {
	animation.Animate(position, true);
  }
};