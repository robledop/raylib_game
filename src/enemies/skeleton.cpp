#include "skeleton.h"

Skeleton::Skeleton(Vector2 pos, Rectangle collRect, Player *p, vector<CollisionBody> *terrainCollisionBodies)
	: CollisionBody{pos, collRect, true},
	  player{p},
	  terrainCollisionBodies{terrainCollisionBodies},
	  idleAnimation{
		  "assets/enemies/skeleton/Skeleton Idle.png",
		  11,
		  1.0f / 12.0f,
		  5.f
	  }, attackAnimation{
		"assets/enemies/skeleton/Skeleton Attack.png",
		18,
		1.0f / 12.0f,
		5.f
	}, hitAnimation{
		"assets/enemies/skeleton/Skeleton Hit.png",
		8,
		1.0f / 12.0f,
		5.f
	}, walkAnimation{
		"assets/enemies/skeleton/Skeleton Walk.png",
		13,
		1.0f / 12.0f,
		5.f
	},
	  health{100},
	  dealDamage{true},
	  hit{false},
	  facingRight{true},
	  sameYPosAsPlayer{false},
	  delay{0} ,
	  currentY{pos.y - 25},
	  currentX{pos.x} {
  
  this->player->reactor.AddEventListener(ATTACK, [this](int data) {
	Damage(data);
  });
}

void Skeleton::Draw() {
  if (IsDead()) {
	return;
  }

  if (showCollisionBoxes) {
	DrawRectangleLinesEx(this->collisionRect, 2, CYAN);
	DrawRectangleLinesEx(weaponHitbox, 2, SEAGREEN);
  }

  // Center of player (y coordinate) is less than 200 pixels away from the center of the skeleton
  sameYPosAsPlayer =
	  abs((player->hitbox.y + player->GetHeight() / 2) - (collisionRect.y + collisionRect.height / 2)) < 200;

  facingRight = player->position.x + collisionRect.width > currentX;

  if (facingRight) {
	collisionRect =
		{currentX + idleAnimation.GetTextureWidth() / 2 - 25,
		 currentY + 55,
		 idleAnimation.GetTextureWidth() / 5,
		 idleAnimation.GetTextureHeight() - 57};
  } else {
	collisionRect =
		{currentX - 30 + idleAnimation.GetTextureWidth() / 2,
		 currentY + 55,
		 idleAnimation.GetTextureWidth() / 5,
		 idleAnimation.GetTextureHeight() - 57};
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
	bool sideCollision = false;
	for (auto &terrain : *terrainCollisionBodies) {
	  auto [sideColl, xPos] = terrain.CheckSideCollision(collisionRect, 1);
	  if (sideColl) {
		sideCollision = true;
		break;
	  }
	}
	bool topCollision = false;
	for (auto &terrain : *terrainCollisionBodies) {
	  auto [topCol, yPos] = terrain.CheckTopCollision({
														  collisionRect.x + 24 * 3,
														  collisionRect.y,
														  collisionRect.width,
														  collisionRect.height}, 1);
	  if (topCol) {
		topCollision = true;
		break;
	  }
	}

	if (!sideCollision && topCollision) {
	  currentX += 1;
	}

	position.y = currentY;
	position.x = currentX;
	walkAnimation.Animate(position, facingRight);
  } else if (
	  sameYPosAsPlayer &&
		  !facingRight
		  && abs(player->hitbox.x - currentX) < 900
		  && abs(player->hitbox.x - currentX) > 10) {
	bool sideCollision = false;
	for (auto &terrain : *terrainCollisionBodies) {
	  auto [sideColl, _] = terrain.CheckSideCollision(collisionRect, 1);
	  if (sideColl) {
		sideCollision = true;
		break;
	  }
	}
	bool topCollision = false;
	for (auto &terrain : *terrainCollisionBodies) {
	  auto [topCol, yPos] = terrain.CheckTopCollision({
														  collisionRect.x - 24 * 3,
														  collisionRect.y,
														  collisionRect.width,
														  collisionRect.height}, 1);
	  if (topCol) {
		topCollision = true;
		break;
	  }
	}

	if (!sideCollision && topCollision) {
	  currentX -= 1;
	}

	position.y = currentY;
	position.x = currentX;
	walkAnimation.Animate(position, facingRight);
  } else if (
	  sameYPosAsPlayer &&
		  delay++ >= 30 &&
		  (!facingRight && (abs(player->hitbox.x - currentX) <= 10)
			  || (facingRight
				  && ((player->position.x + player->GetWidth()) - (position.x + collisionRect.width)) <= -20))) {
	// Wait a half a second before attacking.
	// The attack animation is 18 frames long, and it runs 1/12 of 60 frames (5 times per second).
	if (delay > 30 + attackAnimation.numberOfFrames * 5) {
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
					<int>(collisionRect.x - 10),
				static_cast <int>(collisionRect.y - 20),
				health,
				5,
				RED);
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
	  player->onBeingHit(10, weaponHitbox);
	}
  }
}
