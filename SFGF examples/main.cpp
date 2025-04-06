#include<UI.hpp>
#include<Scene.hpp>
#include <Data.hpp>
#include "Res.hpp"
#include"SceneInitialization.hpp"
#include"Window.hpp"

int main() {
	window.setInitFunc(MainWindowInitFunc);
	window.run();
	return 0;
}