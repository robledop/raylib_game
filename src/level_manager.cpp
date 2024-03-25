//#include "level_manager.h"
//
//LevelManager::LevelManager(const string &filename) {
//  ifstream file(filename);
//  string line;
//  while (getline(file, line)) {
//	level.push_back(line);
//  }
//
//  lampTexture = LoadTexture(ASSETS_PATH"decorations/lamp.png");
//  fenceTexture = LoadTexture(ASSETS_PATH"decorations/fence_1.png");
//  rockTexture1 = LoadTexture(ASSETS_PATH"decorations/rock_1.png");
//  rockTexture2 = LoadTexture(ASSETS_PATH"decorations/rock_2.png");
//  rockTexture3 = LoadTexture(ASSETS_PATH"decorations/rock_3.png");
//  grassTexture1 = LoadTexture(ASSETS_PATH"decorations/grass_1.png");
//  grassTexture2 = LoadTexture(ASSETS_PATH"decorations/grass_2.png");
//  grassTexture3 = LoadTexture(ASSETS_PATH"decorations/grass_3.png");
//
//  tileSet = LoadTexture(ASSETS_PATH"oak_woods_tileset.png");
//  LoadLevel();
//}
//
//void LevelManager::LoadLevel() {
//  for (int i = 0; i < level.size(); i++) {
//	string line = level[i];
//	for (int j = 0; j < line.size(); j++) {
//	  char c = line[j];
//	  switch (c) {
//		case '#': {
//		  if (i > 0 && level[i - 1][j] == '#' && j > 0 && line[j - 1] != '#') {
//			if (line[j - 1] == '.') {
//			  auto g = WallLeft({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet, true);
//			  ground.push_back(g);
//			} else {
//			  auto g = WallLeft({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet);
//			  ground.push_back(g);
//			}
//		  } else if (line[j + 1] != '#' && i > 0 && level[i - 1][j] == '#') {
//			if (line[j + 1] == '.') {
//			  auto g = WallRight({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet, true);
//			  ground.push_back(g);
//			} else {
//			  auto g = WallRight({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet);
//			  ground.push_back(g);
//			}
//		  } else if (j > 0 && line[j - 1] != '#') {
//			if (line[j - 1] == '.') {
//			  auto g = GroundGrassLeftCorner({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet, true);
//			  ground.push_back(g);
//			} else {
//			  auto g = GroundGrassLeftCorner({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet);
//			  ground.push_back(g);
//			}
//		  } else if (line[j + 1] != '#') {
//			if (line[j + 1] == '.') {
//			  auto g = GroundGrassRightCorner({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet, true);
//			  ground.push_back(g);
//			} else {
//			  auto g = GroundGrassRightCorner({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet);
//			  ground.push_back(g);
//			}
//		  } else if (i > 0 && level[i - 1][j] == '#') {
//			auto g = GroundDark({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet);
//			ground.push_back(g);
//		  } else if (i > 0 && (level[i - 1][j] == '.' || level[i - 1][j] == '*')) {
//			auto g = GroundRock({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet);
//			ground.push_back(g);
//		  } else {
//			auto g = GroundGrass({(float)j * 24 * 3, (float)i * 24 * 3}, &tileSet);
//			ground.push_back(g);
//		  }
//		  break;
//		}
//
//		case '.': {
//		  if (level[i - 1][j] == ' ') {
//			auto b =
//				Decoration{{(float)j * 24 * 3, (float)i * 24 * 3},
//						   &tileSet,
//						   {24 * 16, 0, 24, 24}};
//			decorations.push_back(b);
//		  } else {
//			auto b =
//				Decoration{{(float)j * 24 * 3, (float)i * 24 * 3},
//						   &tileSet,
//						   {24 * 15, 24, 24, 24}};
//			decorations.push_back(b);
//		  }
//
//		  break;
//		}
//
//		case '*': {
//		  auto b = Decoration{{(float)j * 24 * 3, (float)i * 24 * 3},
//							  &tileSet,
//							  {(24 * 18) + 10, (24 * 6) - 10, 24, 24}};
//		  decorations.push_back(b);
//
//		  break;
//		}
//
//		case '!': {
//		  auto d = Decoration({(float)j * 24 * 3, ((float)i * 24 * 3) - 26}, &lampTexture);
//		  decorations.push_back(d);
//		  break;
//		}
//
//		case 'F': {
//		  auto d = Decoration({(float)j * 24 * 3, ((float)i * 24 * 3) + 15}, &fenceTexture);
//		  decorations.push_back(d);
//		  break;
//		}
//
//		case 'R': {
//		  auto d = Decoration({(float)j * 24 * 3, ((float)i * 24 * 3) + 40}, &rockTexture1);
//		  decorations.push_back(d);
//		  break;
//		}
//
//		case 'r': {
//		  auto d = Decoration({(float)j * 24 * 3, ((float)i * 24 * 3) + 36}, &rockTexture2);
//		  decorations.push_back(d);
//		  break;
//		}
//
//		case 'T': {
//		  auto d = Decoration({(float)j * 24 * 3, ((float)i * 24 * 3) + 19}, &rockTexture3);
//		  decorations.push_back(d);
//		  break;
//		}
//
//		case 'G': {
//		  auto d = Decoration({(float)j * 24 * 3, ((float)i * 24 * 3) + 63}, &grassTexture1);
//		  decorations.push_back(d);
//		  break;
//		}
//		case 'g': {
//		  auto d = Decoration({(float)j * 24 * 3, ((float)i * 24 * 3) + 57}, &grassTexture2);
//		  decorations.push_back(d);
//		  break;
//		}
//
//		case 't': {
//		  auto d = Decoration({(float)j * 24 * 3, ((float)i * 24 * 3) + 60}, &grassTexture3);
//		  decorations.push_back(d);
//		  break;
//		}
//
//		case 'S': {
//		  auto s = Shop({(float)j * 24 * 3, ((float)i * 24 * 3)});
//		  shops.push_back(s);
//		  break;
//		}
//	  }
//	}
//  }
//}
//
//void LevelManager::DrawLevel() {
//  for (auto &g : ground) {
//	g.Draw();
//  }
//  for (auto &d : decorations) {
//	d.Draw();
//  }
//  for (auto &s : shops) {
//	s.Draw();
//  }
//}
//
//float LevelManager::CheckCollision(Rectangle hitbox, float playerSpeed) {
//  for (auto &g : ground) {
//	if (g.CheckTopCollision(hitbox, playerSpeed)) {
//	  return g.position.y;
//	}
//  }
//
//  return 0;
//}
//
//float LevelManager::CheckSideCollision(Rectangle hitbox, float playerSpeed) {
//  for (auto &g : ground) {
//	if (g.CheckSideCollision(hitbox, playerSpeed)) {
//	  return g.position.x;
//	}
//  }
//  return 0;
//}