#include "SceneInitailizer.hpp"


namespace SFS {


	template <typename Target>
	void SceneInitializer<Target>::LoadSharedResources() {
		if (!sharedResources.textureManager || !sharedResources.localisatoinManager |
			!sharedResources.shaderManager || !sharedResources.soundManager) {
			if (sharedResources.Load)
				sharedResources.Load(sharedResources);
		}
	}


	template <typename Target>
	void SceneInitializer<Target>::LoadSceneResources() {
		if (!resources.textureManager || !resources.localisatoinManager |
			!resources.shaderManager || !resources.soundManager) {
			if (resources.Load)
				resources.Load(resources);
		}
	}
}