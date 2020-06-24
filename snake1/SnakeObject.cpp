#include "SnakeObject.h"
#include "ResourceManager.h"


//蛇的构造函数
SnakeObject::SnakeObject(int unitSize):anglePertime(0.5) {
	this->unitSize = unitSize;
	GameObject* head = new GameObject(glm::vec2(unitSize * 4, unitSize * 5), glm::vec2(unitSize, unitSize), ResourceManager::GetTexture("snakeHead"), glm::vec3(1.0f));
	head->rotation = PI / 2;
	snake.push_back(*head);
	GameObject* body = new GameObject(glm::vec2(unitSize * 3, unitSize * 5), glm::vec2(unitSize, unitSize), ResourceManager::GetTexture("snakeBody"), glm::vec3(1.0f));
	body->rotation = PI / 2;
	snake.push_back(*body);
	GameObject* body2 = new GameObject(glm::vec2(unitSize * 2, unitSize * 5), glm::vec2(unitSize, unitSize), ResourceManager::GetTexture("snakeBody"), glm::vec3(1.0f));
	body2->rotation = PI / 2;
	snake.push_back(*body2);
	GameObject* tail = new GameObject(glm::vec2(unitSize, unitSize * 5), glm::vec2(unitSize, unitSize), ResourceManager::GetTexture("snakeTail"), glm::vec3(1.0f));
	tail->rotation = PI / 2;
	snake.push_back(*tail);
	for (int i = 0; i < this->unitSize * (snake.size()); i++) {
		snakeHeadPositions.push_back(glm::vec3(head->position-glm::vec2(i, 0),head->rotation));
	}
}
//蛇移动函数，游戏时循环调用
void SnakeObject::move(int windowSize)
{
	if (snake[0].position.x  < -unitSize ) {
		snake[0].position.x += (windowSize + unitSize);
	}
	if (snake[0].position.y  < -unitSize) {
		snake[0].position.y += (windowSize + unitSize);
	}
	if (snake[0].position.x > (windowSize)) {
		snake[0].position.x -= (windowSize + unitSize);
	}
	if (snake[0].position.y  > (windowSize)) {
		snake[0].position.y -= (windowSize + unitSize);
	}
	//蛇头移动
	snakeHeadPositions.insert(snakeHeadPositions.begin(),glm::vec3(snake[0].position, snake[0].rotation));
	snake[0].position.x += snake[0].speed * cos(snake[0].rotation - PI / 2);
	snake[0].position.y += snake[0].speed * sin(snake[0].rotation - PI / 2);
	//获得蛇的所有身体
	std::vector<GameObject>::iterator iter = snake.begin();
	iter++;
	glm::vec3 positionTemp;
	//蛇移动
	for (int i = 1; i < snake.size();i++) {
		int snakePositionIndex = this->unitSize * (i)-1;
		snake[i].position = glm::vec2(snakeHeadPositions[snakePositionIndex].x, snakeHeadPositions[snakePositionIndex].y);
		snake[i].rotation = snakeHeadPositions[snakePositionIndex].z;
	}
	snakeHeadPositions.pop_back();
}
//蛇绘制函数
void SnakeObject::draw(SpriteRenderer& spriteRender)
{
	//绘制蛇
	std::vector<GameObject>::iterator iter = snake.end();
	while (iter!= snake.begin())
	{
		iter--;
		spriteRender.DrawSprite(iter->texture, iter->position, iter->size, iter->rotation, iter->color);
	}
}
//蛇转向函数，当键盘输入wasd时进行转向操作
void SnakeObject::changeDirection(Direction direction, GLfloat dt) {
	if (snake[0].rotation > 2 * PI) {
		snake[0].rotation = 0;
	}
	if (snake[0].rotation < 0) {
		snake[0].rotation += 2 * PI;
	}
	//改变蛇头的朝向并留下转折点，并将蛇身的转向数+1
	GLfloat angleChanged = anglePertime * dt*10;
	/*if (snake[0].rotation > PI * 3 / 2) {
		if (direction == UP) {
			snake[0].rotation += angleChanged;
		}
		else if (direction == DOWN) {
			snake[0].rotation -= angleChanged;
		}
		else if (direction == RIGHT) {
			snake[0].rotation += angleChanged;
		}
		else if (direction == LEFT) {
			snake[0].rotation -= angleChanged;
		}
	}
	else if (snake[0].rotation > PI) {
		if (direction == UP) {
			snake[0].rotation += angleChanged;
		}
		else if (direction == DOWN) {
			snake[0].rotation -= angleChanged;
		}
		else if (direction == RIGHT) {
			snake[0].rotation -= angleChanged;
		}
		else if (direction == LEFT) {
			snake[0].rotation += angleChanged;
		}
	}
	else if (snake[0].rotation > PI / 2) {
		if (direction == UP) {
			snake[0].rotation -= angleChanged;
		}
		else if (direction == DOWN) {
			snake[0].rotation += angleChanged;
		}
		else if (direction == RIGHT) {
			snake[0].rotation -= angleChanged;
		}
		else if (direction == LEFT) {
			snake[0].rotation += angleChanged;
		}
	}
	else */
	if (snake[0].rotation >= 0) {
		if (direction == UP ) {
			snake[0].rotation -= angleChanged;
		}
		else if (direction == DOWN) {
			snake[0].rotation += angleChanged;
		}
		else if (direction == RIGHT) {
			snake[0].rotation += angleChanged;
		}
		else if (direction == LEFT) {
			snake[0].rotation -= angleChanged;
		}
	}
}

void SnakeObject::snakeChangePointPlus()
{
	for (int i = 1; i < snake.size();i++) {
		snake[i].changPointCount++;
	}
}

void SnakeObject::grow()
{
	for (int i = 0; i < this->unitSize; i++) {
		snakeHeadPositions.push_back(glm::vec3(snake[0].position, snake[0].rotation));
	}
	GameObject* body = new GameObject(glm::vec2(unitSize * 2, unitSize * 5), glm::vec2(unitSize, unitSize), ResourceManager::GetTexture("snakeBody"), glm::vec3(1.0f));
	body->rotation = PI / 2;
	snake.insert(snake.begin()+1,*body);
}

