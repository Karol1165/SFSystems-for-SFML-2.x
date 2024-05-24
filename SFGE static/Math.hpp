#pragma once
#ifndef MATH_H_
#define MATH_H_
#include<SFML/Graphics.hpp>
#include "definitions.h"


namespace SFGF {

	[[nodiscard]]
	double Angle_Between_Points(sf::Vector2f a, sf::Vector2f b);

}

#endif // !MATH_H_


