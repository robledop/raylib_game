#include "bronze_coin.h"
void BronzeCoin::Draw() {
  if (isCollected) return;
  animation.Animate(position);
}
