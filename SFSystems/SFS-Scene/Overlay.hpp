#pragma once
#ifndef PROFILER_HPP_
#define PROFILER_HPP_

#include "framework.h"

namespace SFS {

	class SFS_S_API DebugOverlay : public sf::Drawable {
	public:
		virtual ~DebugOverlay() = default;

		virtual void setData(const PerformanceData& data) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};

}
#endif