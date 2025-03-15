#pragma once
#ifndef DATA_HPP_
#define DATA_HPP_
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<unordered_map>
#include "framework.h"
#include <memory>


namespace SFS {

	template <typename T>
	using ptr = std::unique_ptr<T>;


	template <typename V, typename T>
	concept isVariantOf = std::is_base_of_v<T, V>;

	template <typename T>
	inline ptr<T>&& make_ptr(T object) {
		return std::make_unique(object);
	}

	template <typename T, isVariantOf<T> O>
	inline O* GetFromPtr(ptr<T>& pointer) {
		return dynamic_cast<O*> (pointer.get());
	}


	struct SFS_C_API textData {
		int characterSize = 14;
		sf::Color fillColor;
		sf::Color outlineColor;
		float outlineThickness = 0.0f;
	};
	SFS_C_API inline void setTextData(const textData& data, sf::Text& object) {
		object.setCharacterSize(data.characterSize);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
	}
	struct SFS_C_API rectangleShapeData {
		sf::Color fillColor;
		sf::Color outlineColor;
		sf::Vector2f size;
		float outlineThickness = 0.0f;
		sf::Texture* texture = nullptr;
	};
	SFS_C_API inline void setRectangleData(const rectangleShapeData& data, sf::RectangleShape& object) {
		object.setSize(data.size);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
		object.setTexture(data.texture);
	}
	struct SFS_C_API circleShapeData {
		sf::Color fillColor;
		sf::Color outlineColor;
		float radius = 10.0f;
		float outlineThickness = 0.0f;
		sf::Texture* texture = nullptr;
	};
	SFS_C_API inline void setCircleData(const circleShapeData& data, sf::CircleShape& object) {
		object.setRadius(data.radius);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
		object.setTexture(data.texture);
	}
	struct SFS_C_API soundData {
		sf::SoundBuffer* buffer;
		float volume = 100.0f;
		float pitch = 1.0f;
		bool loop = false;
	};
	SFS_C_API inline void setSoundData(const soundData& data, sf::Sound& object) {
		if (data.buffer)
			object.setBuffer(*data.buffer);
		object.setVolume(data.volume);
		object.setPitch(data.pitch);
		object.setLoop(data.loop);
	}

	template <typename T>
	class idVector {
	private:
		std::vector<T> objects;
		std::unordered_map<std::string, T*> ids;
	public:

		inline void push_back(const T& object);
		inline void push_back(const std::string& id, const T& object);
		inline void push_back(T&& object);
		inline void push_back(const std::string& id, T&& object);
		inline void erase(std::string id);
		inline void erase(size_t index);

		[[nodiscard]]
		T& get(const size_t& index) const;

		[[nodiscard]]
		T& get(const std::string& id) const;

		[[nodiscard]]
		T& operator[] (const size_t& index) const;

		[[nodiscard]]
		T& operator[] (const std::string& id) const;

		void clear() noexcept { this->objects.clear(); this->ids.clear(); }

		[[nodiscard]] auto begin() noexcept { return this->objects.begin(); }
		[[nodiscard]] auto end() noexcept { return this->objects.end(); }
		[[nodiscard]] auto begin() const noexcept { return this->objects.begin(); }
		[[nodiscard]] auto end() const noexcept { return this->objects.end(); }

		[[nodiscard]] auto rbegin() noexcept { return this->objects.rbegin(); }
		[[nodiscard]] auto rend() noexcept { return this->objects.rend(); }
		[[nodiscard]] auto rbegin() const noexcept { return this->objects.rbegin(); }
		[[nodiscard]] auto rend() const noexcept { return this->objects.rend(); }

	};


}


#include "Data.inl"

#endif 
