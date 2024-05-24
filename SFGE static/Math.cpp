#include "pch.h"
#include "Math.hpp"

namespace SFGF {

	double Angle_Between_Points(sf::Vector2f a, sf::Vector2f b) {
		double A, B, C;
		A = a.x - b.x;
		B = a.y - b.y;
		C = std::pow(A * A + B * B, 0.5);
		return std::asin(A / C) * 180 / M_PI;
	}

}