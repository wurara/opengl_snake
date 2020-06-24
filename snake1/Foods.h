#ifndef FOOD_H
#define FOOD_H

#include "GameObject.h"
#include <vector>

class Foods {
public:
	std::vector<GameObject> foods;
	Foods();
	void draw(SpriteRenderer& renderer);
	void generate(int units, int unitSize);
private:
	bool shouldGenerate(int probability);
};

#endif // !FOOD_H
