#include <string>
#include <fstream>
#include <vector>
#include "ground_grass.cpp"

using namespace std;

extern float scale;

class LevelLoader {
  vector<string> level;
  vector<GroundGrass> ground;
 public:
  LevelLoader(const string &filename) {
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
	  level.push_back(line);
	}

	LoadLevel();
  }

  void LoadLevel() {
	for (int i = 0; i < level.size(); i++) {
	  string line = level[i];
	  for (int j = 0; j < line.size(); j++) {
		char c = line[j];
		if (c == '#') {
		  auto g = GroundGrass(j * 24 * 3, i * 24 * 3);
		  ground.push_back(g);
		}
	  }
	}
  }

  void DrawLevel() {
	for (auto &g : ground) {
	  g.Draw();
	}
  }

  float CheckCollision(Rectangle hitbox, float playerSpeed) {
	for (auto &g : ground) {
	  if (g.CheckTopCollision(hitbox, playerSpeed)) {
		return g.y;
	  }
	}

	return 0;
  }

  float CheckSideCollision(Rectangle hitbox, float playerSpeed) {
	for (auto &g : ground) {
	  if (g.CheckSideCollision(hitbox, playerSpeed)) {
		return g.x;
	  }
	}
	return 0;
  }

};