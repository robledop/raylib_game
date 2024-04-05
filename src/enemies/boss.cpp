#include "boss.h"
Boss::Boss(raylib::Vector2 pos,
		   raylib::Rectangle collisionRect,
		   const unique_ptr<Player> &player,
		   unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies,
		   const unique_ptr<Reactor<raylib::Vector2>> &reactor)
	: CollisionBody{pos, collisionRect, true},
	  player{player},
	  terrainCollisionBodies{terrainCollisionBodies},
	  reactor{reactor},
	  idleAnimation{
		  "assets/bosses/boss1/Idle.png",
		  2,
		  1.0f / 12.0f,
		  5.f,
		  4,
		  0,
		  3
	  },
	  runAnimation{
		  "assets/bosses/boss1/Run.png",
		  2,
		  1.0f / 12.0f,
		  5.f,
		  4,
		  0,
		  3
	  },
	  attack1Animation{
		  "assets/bosses/boss1/Attacks.png",
		  8,
		  1.0f / 10.0f,
		  5.f,
		  5,
		  0,
		  0
	  },
	  attack2Animation{
		  "assets/bosses/boss1/Attacks.png",
		  8,
		  1.0f / 10.0f,
		  5.f,
		  5,
		  1,
		  1
	  },
	  attack3Animation{
		  "assets/bosses/boss1/Attacks.png",
		  8,
		  1.0f / 10.0f,
		  5.f,
		  5,
		  2,
		  2
	  },
	  attackFromAirAnimation{
		  "assets/bosses/boss1/attack_from_air.png",
		  2,
		  1.0f / 10.0f,
		  5.f,
		  4,
		  0,
		  3
	  },
	  hurtAnimation{
		  "assets/bosses/boss1/Hurt.png",
		  2,
		  1.0f / 12.0f,
		  5.f,
		  2,
		  0,
		  1
	  },
	  healthAnimation{
		  "assets/bosses/boss1/Health.png",
		  2,
		  1.0f / 8.0f,
		  5.f,
		  4,
		  0,
		  3
	  },
	  prayAnimation{
		  "assets/bosses/boss1/Pray.png",
		  4,
		  1.0f / 8.0f,
		  5.f,
		  3,
		  0,
		  2
	  },
	  deathAnimation{
		  "assets/bosses/boss1/Death.png",
		  2,
		  1.0f / 8.0f,
		  5.f,
		  2,
		  0,
		  1
	  },
	  jumpAnimation{
		  "assets/bosses/boss1/Jump.png",
		  2,
		  1.0f / 8.0f,
		  5.f,
		  4,
		  0,
		  3
	  } {

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
  if (showCollisionBoxes) {
	collisionRect.DrawLines(RED, 2);
  }
  bool facingRight = player->position.x + collisionRect.width / 2 > position.x;
  if (animationCompleted) {
	random = GetRandomValue(0, 10);
	animationCompleted = false;
  }
  switch (random) {
	case 0: animationCompleted = attack1Animation.Animate(position, facingRight);
	  break;
	case 1: animationCompleted = attack2Animation.Animate(position, facingRight);
	  break;
	case 2: animationCompleted = attack3Animation.Animate(position, facingRight);
	  break;
	case 3: animationCompleted = attackFromAirAnimation.Animate(position, facingRight);
	  break;
	case 4: animationCompleted = runAnimation.Animate(position, facingRight);
	  break;
	case 5: animationCompleted = idleAnimation.Animate(position, facingRight);
	  break;
	case 6: animationCompleted = jumpAnimation.Animate(position, facingRight);
	  break;
	case 7: animationCompleted = deathAnimation.Animate(position, facingRight);
	  break;
	case 8: animationCompleted = prayAnimation.Animate(position, facingRight);
	  break;
	case 9: animationCompleted = hurtAnimation.Animate(position, facingRight);
	  break;
	case 10: animationCompleted = healthAnimation.Animate(position, facingRight);
	  break;
  }
}
