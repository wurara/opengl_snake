#include "SnakeObject.h"
#include "ResourceManager.h"


//�ߵĹ��캯��
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
//���ƶ���������Ϸʱѭ������
void SnakeObject::move()
{
	//����ߵ���������
	std::vector<GameObject>::iterator iter = snake.begin();
	//���ƶ�
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
		//����ר����Ϊ0����Ҫת��
		if (iter->changPointCount != 0) {
			//������һ��ת�����ת��������е����
			int changePointPostition = changPoints.size() - iter->changPointCount;
			//����ǰ������ת����λ�ý��жԱȣ���ͬ��ʼת�����
			if (iter->position == glm::vec2(changPoints[changePointPostition].x, changPoints[changePointPostition].y)) {
				//ת����-1
				iter->changPointCount--;
				//�ı��߷���
				iter->direction = changPoints[changePointPostition].z;
				//�ı�������
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
//�߻��ƺ���
void SnakeObject::Draw(SpriteRenderer& spriteRender)
{
	//������
	std::vector<GameObject>::iterator iter = snake.end();
	while (iter!= snake.begin())
	{
		iter--;
		spriteRender.DrawSprite(iter->texture, iter->position, iter->size, iter->rotation, iter->color);
	}
}
//��ת����������������wasdʱ����ת�����
void SnakeObject::changeDirection(Direction direction) {
	//�ı���ͷ�ĳ�������ת�۵㣬���������ת����+1
	if (direction == UP) {
		snake[0].direction = direction;
		changPoints.push_back(glm::vec3(snake[0].position, direction));
		//��ͷ������ת
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

