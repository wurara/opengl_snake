#include "Foods.h"
#include "ResourceManager.h"

Foods::Foods(){

}

void Foods::draw(SpriteRenderer& renderer)
{
	std::vector<GameObject>::iterator iter= foods.begin();
	for (; iter != foods.end();iter++) {
		if (!iter->destroyed) {
			iter->Draw(renderer);
		}
		else {
			foods.erase(iter);
			iter = foods.begin();
		}
	}
}

void Foods::generate(int units,int unitSize)
{
	GameObject* food = new GameObject(glm::vec2((rand()% units)* unitSize,(rand() % units)* unitSize), glm::vec2(unitSize, unitSize), ResourceManager::GetTexture("apple"));
	foods.push_back(*food);
}

bool Foods::shouldGenerate(int probability) {
	int result = rand() % probability;
	return result == 0;
}
