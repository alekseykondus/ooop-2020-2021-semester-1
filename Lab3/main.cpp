#include <SFML/Graphics.hpp>
//#include <iostream>
#include <fstream>
#include <time.h>
#include "start_game.h"

using namespace sf;

bool file_check()
{
	std::ifstream file1;
	int a;
	file1.open("best_result.txt");
	if (!file1.is_open())
		return 0;
	int line;
	file1 >> line;
	file1.close();

	std::ofstream file2;
	file2.open("best_result.txt");
	if (!file2.is_open())
		return 0;
	if (line < 0)
		file2 << 0;
	else
		file2 << line;
	file2.close();
	return 1;
}

int main()
{
	if (!file_check)
		perror("Error");

	RenderWindow window(VideoMode(800, 600), "Game!", sf::Style::Close | sf::Style::Titlebar);
	srand(time(0));
	start_game(window);

	return 0;
}