#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(30);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idle_color = idle_color;
	this->hover_color = hover_color;
	this->active_color = active_color;

	this->shape.setFillColor(this->idle_color);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	return (this->buttonState == BTN_ACTIVE);
}

void Button::update(const sf::Vector2f mousePos)
{
	//idle
	this->buttonState = BTN_IDLE;

	//hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;
	}
	//click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_ACTIVE;
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idle_color);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hover_color);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->active_color);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}