#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

static float ftime = 0;
void timer(int x)
{
	sf::Clock clock;
	while (ftime < x)
		ftime = clock.getElapsedTime().asSeconds();
	ftime = 0;
}
void EndGame(RenderWindow& window, size_t result, Sprite& cap, std::vector<Sprite> p)
{
	int best_result;
	std::ifstream file1;
	file1.open("best_result.txt");
	file1 >> best_result;
	file1.close();

	if (result > best_result)
	{
		best_result = result;
		std::ofstream file2;
		file2.open("best_result.txt");
		file2 << best_result;
		file2.close();
	}

	Texture endgameTexture;
	endgameTexture.loadFromFile("C:\\dev\\lab3\\images\\end_game.png");
	Sprite endgame(endgameTexture);
	endgame.setPosition(window.getPosition().x / 2, window.getPosition().y / 2 + 100);

	window.draw(cap);
	for (size_t i = 0; i < p.size(); i++)
		window.draw(p[i]);

	window.draw(endgame);
	window.display();

	timer(1);// задержка веремени
}
