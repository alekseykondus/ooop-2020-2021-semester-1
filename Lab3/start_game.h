#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "handling_keyboard_events.h"
#include "EndGame.h"
using namespace sf;
void menu(RenderWindow& window, size_t result);
void start_game(RenderWindow& window)
{
	Texture pTexture0, pTexture1, pTexture2, pTexture3, pTexture4, pTexture5, pTexture6, capTexture, backgroundTexture;

	pTexture0.loadFromFile("C:\\dev\\lab3\\images\\p0.png");
	pTexture1.loadFromFile("C:\\dev\\lab3\\images\\p1.png");
	pTexture2.loadFromFile("C:\\dev\\lab3\\images\\p2.png");
	pTexture3.loadFromFile("C:\\dev\\lab3\\images\\p3.png");
	pTexture4.loadFromFile("C:\\dev\\lab3\\images\\p4.png");
	pTexture5.loadFromFile("C:\\dev\\lab3\\images\\p5.png");
	pTexture6.loadFromFile("C:\\dev\\lab3\\images\\p6.png");
	capTexture.loadFromFile("C:\\dev\\lab3\\images\\shapka.png");
	backgroundTexture.loadFromFile("C:\\dev\\lab3\\images\\fon.png");


	std::vector<Sprite> presents;
	presents.push_back(Sprite(pTexture0));
	presents.push_back(Sprite(pTexture1));
	presents.push_back(Sprite(pTexture2));
	presents.push_back(Sprite(pTexture3));
	presents.push_back(Sprite(pTexture4));
	presents.push_back(Sprite(pTexture5));
	presents.push_back(Sprite(pTexture6));

	Sprite cap(capTexture), background(backgroundTexture);

	std::vector<Sprite> p;

	Font font;
	font.loadFromFile("C:\\dev\\lab3\\fonts\\19919.ttf");
	Text text("", font, 50);
	text.setFillColor(Color::White);
	std::string string;

	int SpawnTime = 15, level = 1, Score = 0, Health_Points = 3;
	cap.setPosition(400, window.getSize().y - cap.getGlobalBounds().height); //можно будет исправить 400

	bool end_game = 0;

	SoundBuffer buffer1;
	buffer1.loadFromFile("C:\\dev\\lab3\\music\\jg-032316-sfx-8-bit-bounce-sound.ogg");
	Sound sound1;
	sound1.setBuffer(buffer1);

	SoundBuffer buffer2;
	buffer2.loadFromFile("C:\\dev\\lab3\\music\\0961f580f9e00da.ogg");
	Sound sound2;
	sound2.setBuffer(buffer2);

	while (window.isOpen())
	{
		window.clear(); //очистка окна
		window.draw(background); //отрисовка фона

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // Пользователь нажал на «крестик» 
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) // Пользователь нажал на «Esc» 
				window.close();
		}

		if (!end_game)
		{
			handling_keyboard_events(window, cap);

			for (size_t i = 0; i < p.size(); i++)
			{
				p[i].move(0.f, level / 10.f);
				//p[i].move(0.f, 10.f);

				if (p[i].getPosition().y+10 > window.getSize().y)
				{
					p.erase(p.begin() + i);
					Health_Points--;
					if (Health_Points) 
						sound1.play();
				}
				if (Health_Points == 0)
				{
					end_game = 1;
					sound2.play();
				}
			}

			if (SpawnTime < 1500 / sqrt(level * 2))
				//if (SpawnTime < 15 / sqrt(level * 2))
				SpawnTime++;

			if (SpawnTime >= 1500 / sqrt(level * 2))
				//if (SpawnTime >= 15 / sqrt(level * 2))
			{
				int i = rand() % 7;
				presents[i].setPosition(rand() % int(window.getSize().x - presents[i].getGlobalBounds().height), 0);
				p.push_back(presents[i]);
				SpawnTime = 0;
			}

			for (size_t i = 0; i < p.size(); i++)
			{
				if (cap.getGlobalBounds().intersects(p[i].getGlobalBounds()))
				{
					Score++;
					p.erase(p.begin() + i);
				}
			}
			level = Score / 10 + 1;
		}
		else
		{
			EndGame(window, Score, cap, p); //конец игры
			menu(window, Score);
		}

		string = std::to_string(Score);
		text.setString("Score:" + string);
		text.setPosition(window.getPosition().x, window.getPosition().y - 240);
		window.draw(text);		//отобажение очков

		string = std::to_string(level);
		text.setString("Level:" + string);
		text.setPosition(window.getPosition().x, window.getPosition().y - 180);
		window.draw(text);		//отобажение уровня

		string = std::to_string(Health_Points);
		text.setString("HP:" + string);
		text.setPosition(window.getPosition().x, window.getPosition().y - 120);
		window.draw(text);		//отобажение здоровья


		window.draw(cap);
		for (size_t i = 0; i < p.size(); i++)
			window.draw(p[i]);

		// Отрисовка окна	
		window.display();
	}
}
void menu(RenderWindow& window, size_t result)
{
	window.clear();

	int best_result;
	std::ifstream file1;
	file1.open("best_result.txt");
	file1 >> best_result;
	file1.close();

	Texture NewGameTexture1, menuTexture2, menuTexture3, Background1, Background2;

	Background1.loadFromFile("C:\\dev\\lab3\\images\\fon.png");

	Sprite BackGr1(Background1), BackGr2(Background2);

	String string;

	Font font;
	font.loadFromFile("C:\\dev\\lab3\\fonts\\20170.ttf");
	Text text_new_game("", font, 71);
	text_new_game.setString("NEW GAME");
	text_new_game.setPosition(window.getPosition().x - 365, window.getPosition().y + 10);

	Text text_quit("", font, 71);
	text_quit.setString("QUIT");
	text_quit.setPosition(window.getPosition().x - 235, window.getPosition().y + 100);

	Text text_result("", font, 71);
	string = std::to_string(result);
	text_result.setString("Your result: " + string);
	text_result.setPosition(window.getPosition().x - 300, window.getPosition().y - 85);

	Text text_best_result("", font, 71);
	string = std::to_string(best_result);
	text_best_result.setString("Best result: " + string);
	text_best_result.setPosition(window.getPosition().x - 300, window.getPosition().y - 150);

	//////////////////////////////МЕНЮ///////////////////
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // Пользователь нажал на «крестик» 
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) // Пользователь нажал на «Esc» 
				window.close();
		}

		text_new_game.setFillColor(Color::White);
		text_quit.setFillColor(Color::White);

		if (IntRect(window.getPosition().x - 365, window.getPosition().y + 10, 450, 80).contains(Mouse::getPosition(window))) { text_new_game.setFillColor(Color::Red); }
		if (IntRect(window.getPosition().x - 235, window.getPosition().y + 100, 175, 80).contains(Mouse::getPosition(window))) { text_quit.setFillColor(Color::Red); }

		if (Mouse::isButtonPressed(Mouse::Left) && IntRect(window.getPosition().x - 235, window.getPosition().y + 100, 175, 80).contains(Mouse::getPosition(window))) //Пользователь нажал на QUIT
			window.close();
		if (Mouse::isButtonPressed(Mouse::Left) && IntRect(window.getPosition().x - 365, window.getPosition().y + 10, 450, 80).contains(Mouse::getPosition(window))) //Пользователь нажал на NEW GAME
			start_game(window);

		window.draw(BackGr1);
		window.draw(text_new_game);
		window.draw(text_quit);
		window.draw(text_result);
		window.draw(text_best_result);

		window.display();
	}
}
