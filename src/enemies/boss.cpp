#include "boss.h"
Boss::Boss(Vector2 pos,
		   Rectangle collisionRect,
		   Player *player,
		   vector<CollisionBody> *terrainCollisionBodies,
		   Reactor<Vector2> *reactor) : CollisionBody{pos, collisionRect, true},
										player{player},
										terrainCollisionBodies{terrainCollisionBodies},
										reactor{reactor},
										idleAnimation{
  											"assets/bosses/boss1/Idle.png",
											2,
											1.0f / 12.0f,
											5.f,
											4
}{

}
int Boss::GetHealth() const {
  return 0;
}
bool Boss::IsDead() const {
  return false;
}
void Boss::Attack() {

}
void Boss::Damage(int damage) {

}
void Boss::Draw() {
  if (showCollisionBoxes){
	DrawRectangleLinesEx(this->collisionRect, 2, RED);
  }
  idleAnimation.Animate(position, true);
}
