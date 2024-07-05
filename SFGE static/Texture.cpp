#include"Texture.hpp"

void Animation::Update(sf::Time deltaTime) {
	actualTime += deltaTime;
	if (actualTime > frequency) {
		if (index + 1 < frames.size()) {
			index++;
		}
		else {
			if (!frames.empty())
				index = 0;
		}
		actualTime = sf::Time::Zero;
	}
}