#pragma once
#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_
#include<SFML/Graphics.hpp>

class Animation {
private:
	std::vector<sf::Texture> frames;
	sf::Time frequency;
	sf::Time actualTime;
	uint16_t index;

public:
	Animation() = default;
	~Animation() = default;

	Animation(sf::Time frequency) { this->frequency = frequency; }

	void addFrame(sf::Texture& newFrame) {
		this->frames.push_back(newFrame);
		if (this->frames.size() == 1)
			index = 0;
	}

	void setFrequency(sf::Time newFrequency) { this->frequency = newFrequency; }

	void setActualFrame(uint16_t newIndex) {
		if (newIndex < frames.size())
			this->index = newIndex;
	}

	[[nodiscard]]
	uint16_t getActualFrameIndex() { return this->index; }

	[[nodiscard]]
	sf::Texture getActualFrame() {
		if (index < frames.size())
			return frames[index];
		else
			return sf::Texture();
	}

	void Update(sf::Time deltaTime);


};

#endif
