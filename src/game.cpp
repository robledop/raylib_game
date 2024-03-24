#include "game.h"

void Game::UpdateCamera() {
  camera.target = {player.position.x, GetScreenHeight() - GetScreenHeight() * 0.65f};
  camera.offset = {
	  static_cast<float>(GetScreenWidth()) / 2.0f - (player.GetTextureWidth() / 2),
	  static_cast<float>(GetScreenHeight()) / 2.0f - player.GetTextureHeight() / 2
  };

  camera.target.x = Clamp(player.position.x, minX, maxX);
  camera.target.y = Clamp(player.position.y - player.GetHeight(), minY, maxY);

}

Game::Game() {
  camera.zoom = 1.0f;
  player.position.y = 544;
  player.position.x = 1400;

  camera.offset = {
	  static_cast<float>(GetScreenWidth()) / 2.0f - (player.GetTextureWidth() / 2),
	  static_cast<float>(GetScreenHeight()) / 2.0f - player.GetTextureHeight() / 2
  };
}
void Game::Draw() {
  UpdateCamera();
  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
	player.direction = RIGHT;
	player.lastDirection = RIGHT;
  } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
	player.direction = LEFT;
	player.lastDirection = LEFT;
  } else { player.direction = STOP; }

  if (player.direction == RIGHT && !player.attacking && !player.blocked && !player.isDead
	  && player.position.x<maxX && player.position.x>minX) {
	bg1X -= 1;
	bg2X -= 2;
	bg3X -= 3;

	if (bg1X <= -background1.width * scale * BG_SCALE) bg1X = 0;
	if (bg2X <= -background2.width * scale * BG_SCALE) bg2X = 0;
	if (bg3X <= -background3.width * scale * BG_SCALE) bg3X = 0;
  }

  if (player.direction == LEFT && !player.attacking && !player.blocked && !player.isDead && player.position.x > minX
	  && player.position.x < maxX) {
	bg1X += 1;
	bg2X += 2;
	bg3X += 3;

	if (bg1X >= 0) bg1X = -background1.width * scale * BG_SCALE;
	if (bg2X >= 0) bg2X = -background2.width * scale * BG_SCALE;
	if (bg3X >= 0) bg3X = -background3.width * scale * BG_SCALE;
  }

  Vector2 bg1Pos{bg1X, 0};
  Vector2 bg1Pos_2{bg1X + background1.width * scale * BG_SCALE, 0};
  Vector2 bg2Pos{bg2X, 0};
  Vector2 bg2Pos_2{bg2X + background2.width * scale * BG_SCALE, 0};

  Vector2 bg3Pos{bg3X, 0};
  Vector2 bg3Pos_2{bg3X + background3.width * scale * BG_SCALE, 0};

  DrawTextureEx(background1, bg1Pos, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background1, bg1Pos_2, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background2, bg2Pos, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background2, bg2Pos_2, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background3, bg3Pos, 0.0f, scale * BG_SCALE, WHITE);
  DrawTextureEx(background3, bg3Pos_2, 0.0f, scale * BG_SCALE, WHITE);

  BeginMode2D(camera);
  {
	levelManager.DrawLevel();
	player.draw();

	float collision = levelManager.CheckCollision(player.hitbox, player.upwardsVelocity);
	if (collision == 0) {
	  player.SetOnGround(false);
	} else {
	  player.SetOnGround(true);
	  player.position.y = collision - player.GetTextureHeight();
	  player.upwardsVelocity = 0;
	  player.falling = false;
	}

	float sideCollision = levelManager.CheckSideCollision(player.hitbox, RUN_SPEED + player.upwardsVelocity / 2.0f);
	if (sideCollision > 0) {
	  player.blocked = true;
	  if (sideCollision > player.hitbox.x) {
		player.rightBlocked = true;
		player.leftBlocked = false;
	  } else if (sideCollision < player.hitbox.x + player.GetWidth()) {
		player.leftBlocked = true;
		player.rightBlocked = false;
	  }
	  player.SetXPosition(sideCollision);
	} else {
	  player.blocked = false;
	  player.leftBlocked = false;
	  player.rightBlocked = false;
	}

  }
  EndMode2D();

#ifdef LOG
  // Stats
  DrawText(TextFormat("Player x: %f", player.position.x), 10, 10, 50, WHITE);
  DrawText(TextFormat("Player y: %f", player.position.y), 10, 60, 50, WHITE);
  DrawText(TextFormat("Camera x: %f", camera.target.x), 10, 110, 50, WHITE);
  DrawText(TextFormat("Camera y: %f", camera.target.y), 10, 160, 50, WHITE);
  DrawText(TextFormat("Camera offset x: %f", camera.offset.x), 10, 210, 50, WHITE);
  DrawText(TextFormat("Camera offset y: %f", camera.offset.y), 10, 260, 50, WHITE);

  // Guide lines
//	  DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), RED);
#endif
  if (player.isDead) {
	DrawText("You died!", GetScreenWidth() / 2 - MeasureText("You died!", 50) / 2, GetScreenHeight() / 2, 50, RED);
  }
}