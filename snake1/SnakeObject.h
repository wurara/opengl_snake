#include "GameObject.h"
#include <vector>

class SnakeObject{
public:
	std::vector<GameObject> snake;
	std::vector<glm::vec3> snakeHeadPositions;
	GLfloat anglePertime;

	int snakeDirection, unitSize;
	SnakeObject(int unitSize);
	void move(int windowSize);
	void draw(SpriteRenderer& spriteRender);
	void changeDirection(Direction direction, GLfloat dt);
	void snakeChangePointPlus();
	void grow();
};
