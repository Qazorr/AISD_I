#pragma once
#include "Tree.h"

class AVL : public Tree
{
private:
	int get_height(Node* node);
	int get_balance_factor(Node* node);
	void update(Node* node);
	Node* balance(Node* node);
	Node* add_node(Node* node, int data);
	Node* remove_node(Node* node, int data);

	Node* single_left_rotation(Node* &parent_node);
	Node* single_right_rotation(Node* &parent_node);

public:

	Node* add(int data);
	Node* remove(int data);
};