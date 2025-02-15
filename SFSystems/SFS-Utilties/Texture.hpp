#pragma once
#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_
#include<SFML/Graphics.hpp>
#include "framework.h"


namespace SFS {
	
	typedef std::vector<sf::Texture> TextureGroup;
	
	class SFS_U_API Animation {
	private:
		TextureGroup frames;
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
			else
				throw new std::out_of_range("index does not exist");
		}

		void setFrames(TextureGroup newFrames) {
			frames = newFrames;
		}


		[[nodiscard]]
		uint16_t getActualFrameIndex() { return this->index; }

		[[nodiscard]]
		sf::Texture getActualFrame() const {
			return frames[index];
		}

		[[nodiscard]]
		TextureGroup getFrames() { return this->frames; }

		void Update(sf::Time deltaTime);


	};

}

#endif
