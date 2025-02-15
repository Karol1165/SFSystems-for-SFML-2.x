#include<UI.hpp>
#include<Scene.hpp>
#include <Data.hpp>
#include "Res.hpp"
#include"SceneInitialization.hpp"

int main() {
	loadStaticResources();
	mainScene.SetInitFunc(mainSceneInitialization);


	sf::RenderWindow w;
	w.create(sf::VideoMode(1080, 720), "testWindow");

	w.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(1080, 720)));

	activeScene.setActiveScene(mainScene, w);

	sf::Event e;

	while (w.isOpen())
	{
		while (w.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) {
				w.close();
			}
			activeScene.getActiveScene()->UpdateUI(e);
		}
		activeScene.getActiveScene()->Update(e);

		w.clear();

		w.draw(activeScene);

		w.display();
	}
	return 0;
}