#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
void handling_keyboard_events(sf::RenderWindow& window, Sprite& cap)
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) { cap.move(-1 / 2.f, 0.f); }
	if (Keyboard::isKeyPressed(Keyboard::Right)) { cap.move(1 / 2.f, 0.f); }

	if (cap.getPosition().x > window.getSize().x - cap.getGlobalBounds().height)
		cap.setPosition(0, cap.getPosition().y);
	if (cap.getPosition().x < 0)
		cap.setPosition(window.getSize().x - cap.getGlobalBounds().height, cap.getPosition().y);
}
