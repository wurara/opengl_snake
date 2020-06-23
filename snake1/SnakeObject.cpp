#include "SnakeObject.h"
#include "ResourceManager.h"


//蛇的构造函数
SnakeObject::SnakeObject(int unitSize) {
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
}
//蛇移动函数，游戏时循环调用
void SnakeObject::move()
{
	//获得蛇的所有身体
	std::vector<GameObject>::iterator iter = snake.begin();
	//蛇移动
	for (; iter != snake.end(); iter++) {
		if (iter->direction == UP) {
			iter->position.y -= 1;
		}
		else if (iter->direction == DOWN) {
			iter->position.y += 1;
		}
		else if (iter->direction == RIGHT) {
			iter->position.x += 1;
		}
		else if (iter->direction == LEFT) {
			iter->position.x -= 1;
		}
		//若是专项数为0则不需要转向
		if (iter->changPointCount != 0) {
			//计算下一个转向点在转向点数组中的序号
			int changePointPostition = changPoints.size() - iter->changPointCount;
			//将当前蛇身与转向点的位置进行对比，相同则开始转向操做
			if (iter->position == glm::vec2(changPoints[changePointPostition].x, changPoints[changePointPostition].y)) {
				//转向数-1
				iter->changPointCount--;
				//改变蛇方向
				iter->direction = changPoints[changePointPostition].z;
				//改变纹理方向
				if (iter->direction == UP) {
					iter->rotation = 0;
				}
				else if (iter->direction == DOWN) {
					iter->rotation = PI;
				}
				else if (iter->direction == LEFT) {
					iter->rotation = PI * 3 / 2;
				}
				else if (iter->direction == RIGHT) {
					iter->rotation = PI / 2;
				}
				if (iter == snake.end()-1) {
					changPoints.erase(changPoints.begin());
				}
			}
		}
	}
}
//蛇绘制函数
void SnakeObject::Draw(SpriteRenderer& spriteRender)
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
void SnakeObject::changeDirection(Direction direction) {
	//改变蛇头的朝向并留下转折点，并将蛇身的转向数+1
	if (direction == UP) {
		snake[0].direction = direction;
		changPoints.push_back(glm::vec3(snake[0].position, direction));
		//蛇头纹理旋转
		snake[0].rotation = 2 * PI;
		snakeChangePointPlus();
	}
	else if (direction == DOWN) {
		snake[0].direction = direction;
		changPoints.push_back(glm::vec3(snake[0].position, direction));
		snake[0].rotation = PI;
		snakeChangePointPlus();
	}
	else if (direction == RIGHT) {
		snake[0].direction = direction;
		changPoints.push_back(glm::vec3(snake[0].position, direction));
		snake[0].rotation = PI / 2;
		snakeChangePointPlus();
	}
	else if (direction == LEFT) {
		snake[0].direction = direction;
		changPoints.push_back(glm::vec3(snake[0].position, direction));
		snake[0].rotation = PI * 3 / 2;
		snakeChangePointPlus();
	}
}

void SnakeObject::snakeChangePointPlus()
{
	for (int i = 1; i < snake.size();i++) {
		snake[i].changPointCount++;
	}
}

