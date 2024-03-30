#include "skeleton.h"

Skeleton::Skeleton(Vector2 pos, Rectangle collRect, Player *p) : CollisionBody{pos, collRect, true},
																 player{p} {
  currentY = pos.y - 25;
  currentX = pos.x;
}

void Skeleton::Draw() {
  if (IsDead()) {
	return;
  }

#ifdef SHOW_COLLISION_BOXES
  DrawRectangleLinesEx(this->collisionRect, 2, CYAN);
  DrawRectangleLinesEx(weaponHitbox, 2, SEAGREEN);
#endif

  sameYPosAsPlayer = abs(player->position.y - position.y) < 350;

  facingRight = player->position.x + collisionRect.width > currentX;

  if (facingRight) {
	collisionRect =
		{currentX + idleAnimation.GetTextureWidth() / 3 - 20,
		 currentY + 55,
		 idleAnimation.GetTextureWidth() / 3,
		 idleAnimation.GetTextureHeight() - 55};
  } else {
	collisionRect =
		{currentX - 30 + idleAnimation.GetTextureWidth() / 2,
		 currentY + 55,
		 idleAnimation.GetTextureWidth() / 3,
		 idleAnimation.GetTextureHeight() - 55};
  }

  if (facingRight) {
	weaponHitbox = {collisionRect.x + collisionRect.width, collisionRect.y, 90, collisionRect.height};
  } else {
	weaponHitbox = {collisionRect.x - 90, collisionRect.y, 90, collisionRect.height};
  }

  if (hit) {
	attackAnimation.Reset();
	delay = 0;

	bool completed = hitAnimation.Animate(position, facingRight);
	hit = !completed;
  } else if (
	  sameYPosAsPlayer &&
		  facingRight
		  && ((player->position.x + player->GetWidth()) - (position.x + collisionRect.width)) < 900
		  && ((player->position.x + player->GetWidth()) - (position.x + collisionRect.width)) > -20) {
	currentX += 1;

	position.y = currentY;
	position.x = currentX;
	walkAnimation.Animate(position, facingRight);
  } else if (
	  sameYPosAsPlayer &&
		  !facingRight
		  && abs(player->hitbox.x - currentX) < 900
		  && abs(player->hitbox.x - currentX) > 10) {
	currentX -= 1;

	position.y = currentY;
	position.x = currentX;
	walkAnimation.Animate(position, facingRight);
  } else if (
	  sameYPosAsPlayer &&
		  delay++ >= 60 &&
		  (!facingRight && (abs(player->hitbox.x - currentX) <= 10)
			  || (facingRight
				  && ((player->position.x + player->GetWidth()) - (position.x + collisionRect.width)) <= -20))) {
	// Wait a second before attacking.
	// The attack animation is 18 frames long, and it runs 1/12 of 60 frames (5 times per second).
	if (delay > 60 + attackAnimation.numberOfFrames * 5) {
	  delay = 0;
	}

	Attack();
  } else {
	position.y = currentY;
	position.x = currentX;
	idleAnimation.Animate(position, facingRight);
	attackAnimation.Reset();
  }

// Draw a health bar at the top of the skeleton
  DrawRectangle(static_cast
					<int>(currentX)
					+ 10, static_cast
					<int>(currentY)
					- 10, health, 10, RED);
}

void Skeleton::Init() {
  this->player->reactor.AddEventListener(ATTACK, [this](int data) {
	Damage(data);
  });
}

Rectangle Skeleton::GetHitbox() const {
  return collisionRect;
}

int Skeleton::GetHealth() const {
  return health;
}

bool Skeleton::IsDead() const {
  return health <= 0;
}

void Skeleton::Damage(int damage) {
  if (CheckCollisionRecs(player->weaponHitbox, collisionRect)) {
	hit = true;
	health -= damage;
	hitAnimation.Reset();
  }
}

void Skeleton::Attack() {
  attackAnimation.Animate(position, facingRight);

  if (attackAnimation.frame >= attackAnimation.numberOfFrames - 1) {
	dealDamage = true;
  } else if (attackAnimation.frame > 6.f) {
	if (dealDamage) {
	  dealDamage = false;
	  player->onBeingHit(1, weaponHitbox);
	}
  }
}

