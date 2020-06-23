#include "GameObject.h"
#include <vector>

class SnakeObject:public GameObject {
public:
	std::vector<GameObject> snake;
	std::vector<glm::vec3> changPoints;

	int snakeDirection, unitSize;
	SnakeObject(int unitSize);
	void move();
	void Draw(SpriteRenderer& spriteRender);
	void changeDirection(Direction direction);
	void snakeChangePointPlus();
};
