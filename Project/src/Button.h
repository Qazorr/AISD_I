#pragma once
#include "config.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idle_color;
	sf::Color hover_color;
	sf::Color active_color;


public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
	~Button();

	const bool isPressed() const;

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};