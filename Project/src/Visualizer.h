#pragma once
#include "config.h"
#include "BST.h"
#include "AVL.h"
#include "Button.h"

class Visualizer
{
private:
	sf::Font font;
	sf::RenderWindow window;
	sf::Vector2f oldPos;
	sf::View view;
	bool moving;
	float zoom;


	//AVL
	int get_height(Node* node);
	int get_balance_factor(Node* node);
	Node* smallest_node(Node* node);
	void update(Node* node);
	Node* balance(Tree* tree, Node* node);
	Node* insert_f(Tree* tree, Node* node, int data);
	Node* remove_f(Tree* tree, Node* node, int data);
	void draw_left_rotation(Tree* tree, Node* parent, Node* left, Node* right);
	void draw_right_rotation(Tree* tree, Node* parent, Node* left, Node* right);
	Node* left_rotation(Tree* tree, Node*& parent_node);
	Node* right_rotation(Tree* tree, Node*& parent_node);

public:
	Visualizer();
	Tree* button_loop();
	void main_loop(Tree *tree);
	void get_input(Tree *tree);
	void update_connections(Tree* tree);
	void draw_line(sf::Vector2f from, sf::Vector2f to);
	void draw_line(Node *from, Node *to);
	void draw_moving_node(Tree *tree, Node* from, Node* to);
	void draw_node(Node *node, sf::Color color);
	void draw_tree(Tree *tree);
	void draw_top_left(Tree* tree, Node* left, Node* right, std::string symbol, std::string instruction);
	void find_minimum(Tree *tree);
	void find_maximum(Tree *tree);
	bool find(Tree *tree, int data, bool write = true);
	void add_node(Tree* tree, int data);
	bool remove_node(Tree* tree, int data);
};