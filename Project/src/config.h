#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//TODO: tweak the sizes of nodes and also try to get the constants out of the code if possible

//window
constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 720;

//colors
namespace LIGHT_THEME {
	const auto BG_COLOR = sf::Color(200, 200, 200);
	const auto TEXT_COLOR = sf::Color::Black;
	const auto OUTLINE_COLOR = sf::Color::Black;
	const auto STD_NODE_COLOR = sf::Color::Blue;
	const auto CONSIDERED_NODE_COLOR = sf::Color(110, 0, 110);
	const auto HIGHLIGHTED_NODE_COLOR = sf::Color::Cyan;
	const auto RUNNING_NODE_COLOR = sf::Color::Yellow;
	const auto TOP_LEFT_COLOR = sf::Color::Red;
	const auto MESSAGE_COLOR = sf::Color(0,110,0);
}

namespace DARK_THEME {
	const auto BG_COLOR = sf::Color::Black;
	const auto TEXT_COLOR = sf::Color::White;
	const auto OUTLINE_COLOR = sf::Color::White;
	const auto STD_NODE_COLOR = sf::Color(0, 90, 90);
	const auto CONSIDERED_NODE_COLOR = sf::Color(110, 0, 110);
	const auto HIGHLIGHTED_NODE_COLOR = sf::Color(0, 0, 110);
	const auto RUNNING_NODE_COLOR = sf::Color(160, 160, 0);
	const auto TOP_LEFT_COLOR = sf::Color::Red;
	const auto MESSAGE_COLOR = sf::Color::Green;
}

//node size
constexpr auto RADIUS = 20.f;
constexpr auto FONT_SIZE = 18;

//moving the node
#define ROOT_MOVE_X WIDTH/2.f
constexpr auto OUTLINE_THICKNESS = 4.0f;
constexpr auto MOVE = 10.f;
constexpr auto MOVE_RATIO = 2.f;
constexpr auto MOVE_Y = 100.f;
constexpr auto STEPS = 15;
constexpr auto ROTATION_STEPS = 30;
constexpr auto ROTATION_SLEEP = 30000;