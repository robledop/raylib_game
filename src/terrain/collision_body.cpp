#include "collision_body.h"
#include "config.h"

CollisionBody::CollisionBody(raylib::Vector2 position,
							 raylib::Rectangle collisionRect,
							 bool blocking)
	: blocking{blocking}, collisionRect{collisionRect}, position{position} {}

std::tuple<bool, float> CollisionBody::CheckTopCollision(
	raylib::Rectangle hitbox,
	float playerSpeed) const {
  if (!this->blocking)
	return std::make_tuple(false, 0);
  return std::make_tuple((hitbox.x < (position.x + collisionRect.width) &&
							 (hitbox.x + hitbox.width) > position.x) &&
							 hitbox.y + hitbox.height <=
								 position.y + playerSpeed * GetFrameTime() &&
							 hitbox.y + hitbox.height >=
								 position.y - 10 - playerSpeed * GetFrameTime(),
						 position.y);
}

std::tuple<bool, float> CollisionBody::CheckSideCollision(
	raylib::Rectangle hitbox,
	float playerSpeed) const {
  if (!blocking)
	return std::make_tuple(false, 0);
  return std::make_tuple(
	  hitbox.y < position.y + (collisionRect.height) &&
		  hitbox.y + hitbox.height > position.y &&
		  ((hitbox.x + hitbox.width <=
			  position.x + 10 + playerSpeed * GetFrameTime() &&
			  hitbox.x + hitbox.width >=
				  position.x - 10 - playerSpeed * GetFrameTime()) ||
			  (hitbox.x >= position.x + (collisionRect.width) - 10 -
				  playerSpeed * GetFrameTime() &&
				  hitbox.x <= position.x + (collisionRect.width) + 10 +
					  playerSpeed * GetFrameTime())),
	  position.x);
}

// TODO: implement this
bool CollisionBody::CheckBottomCollision(raylib::Rectangle hitbox,
										 float playerSpeed) const {
  if (!blocking)
	return false;
  return (hitbox.x < (position.x + (collisionRect.width * 3 * scale)) &&
	  hitbox.x + hitbox.width > position.x) &&
	  hitbox.y >= position.y + (collisionRect.height * 3 * scale) -
		  playerSpeed * GetFrameTime() &&
	  hitbox.y <= position.y + (collisionRect.height * 3 * scale) + 10 +
		  playerSpeed * GetFrameTime();
}

raylib::Rectangle CollisionBody::GetHitbox() const {
  return collisionRect;
}
void CollisionBody::SetPosition(raylib::Vector2 pos) {
  this->position = pos;
}
raylib::Vector2 CollisionBody::GetPosition() {
  return position;
}

void CollisionBody::Update() {
  if (fallSpeed < 5){
	fallSpeed += 150 * GetFrameTime() * GetFrameTime();
  } 
  
  if (bouncing) {
	fallSpeed += -(fallSpeed * bounciness);
	bouncing = false;
  }
  
  position.y += fallSpeed;
  position.x += sidewaysSpeed;
  collisionRect.x = position.x;
  collisionRect.y = position.y;
}
