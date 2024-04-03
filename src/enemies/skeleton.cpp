#include "skeleton.h"
#include "reactor.h"

#define WALK_SPEED 3

// TODO: Change the way assets are loaded so that they are NOT separately loaded for each instance of the class.
Skeleton::Skeleton(Vector2 pos,
				   Rectangle collRect,
				   const unique_ptr<Player> &p,
				   const unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies,
				   const unique_ptr<Reactor<Vector2>> &reactor)
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
		1.0f / 24.0f,
		5.f
	}, hitAnimation{
		"assets/enemies/skeleton/Skeleton Hit.png",
		8,
		1.0f / 24.0f,
		5.f
	}, walkAnimation{
		"assets/enemies/skeleton/Skeleton Walk.png",
		13,
		1.0f / (12.f * WALK_SPEED),
		5.f
	}, deathAnimation{
		"assets/enemies/skeleton/Skeleton Dead.png",
		15,
		1.0f / 12.0f,
		5.f
	}, deathReactor{reactor},
	  attacking{false},
	  health{50},
	  dealDamage{true},
	  hit{false},
	  facingRight{true},
	  sameYPosAsPlayer{false},
	  delay{0},
	  currentY{pos.y - 25},
	  currentX{pos.x} {

  this->player->reactor.AddEventListener(ATTACK, [this](int data) {
	Damage(data);
  });
}

void Skeleton::Draw() {
  if (IsDead() && !deathAnimationPlayed) {
	deathAnimationPlayed = deathAnimation.Animate(position, facingRight);
	return;
  } else if (IsDead()) {
	deathAnimation.DrawLastFrame(position);
	return;
  }

  if (showCollisionBoxes) {
	DrawRectangleLinesEx(this->collisionRect, 2, CYAN);
	DrawRectangleLinesEx(weaponHitbox, 2, SEAGREEN);
  }

  facingRight = player->position.x + collisionRect.width > currentX;

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

  HandleCombat();

  // Draw a health bar at the top of the skeleton
  DrawRectangle(static_cast
					<int>(collisionRect.x - 10),
				static_cast <int>(collisionRect.y - 20),
				health * 2,
				5,
				RED);
}

void Skeleton::HandleCombat() {
  if (hit) {
	delay = 0;

	bool completed = hitAnimation.Animate(position, facingRight);
	hit = !completed;
	if (completed) attackAnimation.Reset();
  } else if (
	  !attacking &&
		  sameYPosAsPlayer &&
		  facingRight
		  && ((player->position.x + player->GetWidth()) - (position.x + collisionRect.width)) < 900
		  && ((player->position.x + player->GetWidth()) - (position.x + collisionRect.width)) > 20) {
	bool sideCollision = false;
	for (auto &terrain : *terrainCollisionBodies) {
	  auto [sideColl, xPos] = terrain->CheckSideCollision(collisionRect, 1);
	  if (sideColl) {
		sideCollision = true;
		break;
	  }
	}
	bool topCollision = false;
	for (auto &terrain : *terrainCollisionBodies) {
	  auto [topCol, yPos] = terrain->CheckTopCollision({
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
	  currentX += WALK_SPEED;
	}

	position.y = currentY;
	position.x = currentX;
	walkAnimation.Animate(position, facingRight);
  } else if (
	  !attacking &&
		  sameYPosAsPlayer &&
		  !facingRight
		  && abs(player->hitbox.x - currentX) < 900
		  && abs(player->hitbox.x - currentX) >= 10) {
	bool sideCollision = false;
	for (auto &terrain : *terrainCollisionBodies) {
	  auto [sideColl, _] = terrain->CheckSideCollision(collisionRect, 1);
	  if (sideColl) {
		sideCollision = true;
		break;
	  }
	}
	bool topCollision = false;
	for (auto &terrain : *terrainCollisionBodies) {
	  auto [topCol, yPos] = terrain->CheckTopCollision({
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
	  currentX -= WALK_SPEED;
	}

	position.y = currentY;
	position.x = currentX;
	walkAnimation.Animate(position, facingRight);
  } else if (
	  attacking ||
		  (sameYPosAsPlayer &&
			  (!staggered || delay++ >= 10) &&
			  (!facingRight && (abs(player->hitbox.x - currentX) <= 10)
				  || (facingRight
					  && ((player->position.x + player->GetWidth()) - (position.x + collisionRect.width)) <= 20)))) {
	if (!staggered) delay = 0;
	// Wait a few frames before attacking when staggered.
	// The attack animation is 18 frames long, and it runs 1/12 of 60 frames (5 times per second).
	if (delay > 10 + attackAnimation.numberOfFrames * 5) {
	  delay = 0;
	  staggered = false;
	}
	Attack();
  } else {
	position.y = currentY;
	position.x = currentX;
	idleAnimation.Animate(position, facingRight);
	attackAnimation.Reset();
  }
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
	// Set this to true to enable staggering
	staggered = false;
	health -= damage;
	hitAnimation.Reset();
  }
  if (health <= 0 && !droppedLoot) {
	deathReactor->DispatchEvent(ENEMY_DEATH, {this->collisionRect.x, this->collisionRect.y});
	droppedLoot = true;
  }
}

void Skeleton::Attack() {
  attacking = !attackAnimation.Animate(position, facingRight);

  if (attackAnimation.frame >= attackAnimation.numberOfFrames - 1) {
	dealDamage = true;
  } else if (attackAnimation.frame > 8.f) {
	if (dealDamage) {
	  dealDamage = false;
	  player->onBeingHit(10, weaponHitbox);
	}
  }
}
