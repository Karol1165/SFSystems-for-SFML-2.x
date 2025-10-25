#pragma once
#ifndef SCENEINITIALIZER_HPP_
#define SCENEINITIALIZER_HPP_

#include "framework.h"

namespace SFS {
	template <typename Target>
	class SceneInitializer {
	private:

		struct Resources {
			using LoadFunc = void(*)(Resources&);

			sptr<BaseTextrureManager> textureManager;
			sptr<BaseLocalisationManager> localisatoinManager;
			sptr<BaseShaderManager> shaderManager;
			sptr<BaseSoundManager> soundManager;

			LoadFunc Load = nullptr;
		};

		static Resources sharedResources;

		Resources resources;

	protected:

		Target& target;

	public:

		explicit SceneInitializer(Target& target, Resources::LoadFunc sharedLoadFunc, Resources::LoadFunc localLoadFunc) : target(target) {
			sharedResources.Load = sharedLoadFunc;
			resources.Load = localLoadFunc;
		}

		virtual ~SceneInitializer() = default;

		virtual void LoadSharedResources();
		virtual void LoadSceneResources();
		virtual void InitializeScene() = 0;
		virtual void UnloadSceneResources() {}

	};
}

#include "SceneInitializer.inl"

#endif
