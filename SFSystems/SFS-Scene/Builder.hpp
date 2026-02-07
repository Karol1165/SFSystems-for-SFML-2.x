#pragma once
#ifndef SCENEINITIALIZER_HPP_
#define SCENEINITIALIZER_HPP_

#include "framework.h"

namespace SFS {

	template <typename Target>
	class Builder {
	public:
		explicit Builder(Target* target) {
			this->target = target;
		}
		virtual ~Builder() = default;
	protected:
		Target* target;
	};

	template <typename Target>
	class SceneInitializer : public Builder<Target> {
	public:

		explicit SceneInitializer(Target* target) : Builder<Target>(target) {}

		virtual ~SceneInitializer() = default;

		// Executed before building this specific scene
		virtual void LoadSceneResources() = 0;

		// Executed when the scene is being constructed
		virtual void BuildScene() = 0;

		// Executed when the scene becomes active (enters update loop)
		virtual void StartScene() = 0;

		// Executed when the scene is being paused (exits update loop)
		virtual void PauseScene() = 0;

		// Executed when the scene is being destroyed
		virtual void UnloadScene() = 0;

		// Executed when the scene is being destroyed
		virtual void UnloadSceneResources() = 0;

	};
}

#endif
