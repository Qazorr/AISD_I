#include "AVL.h"

int AVL::get_height(Node* node)
{
	return node ? node->mHeight : 0;
}

int AVL::get_balance_factor(Node* node)
{
	return node != nullptr ? get_height(node->left) - get_height(node->right) : -1;
}

void AVL::update(Node* node)
{
	if (node)
		node->mHeight = std::max(get_height(node->left), get_height(node->right)) + 1;
}

Node* AVL::balance(Node* node)
{
	if (!node) return node;
	update(node);
	if (get_balance_factor(node) == -2) {
		if (get_balance_factor(node->right) > 0) {
			node->right = single_left_rotation(node->right);
		}
		return single_right_rotation(node);
	}
	if (get_balance_factor(node) == 2) {
		if (get_balance_factor(node->left) < 0) {
			node->left = single_right_rotation(node->left);
		}
		return single_left_rotation(node);
	}
	return node;
}

Node* AVL::add_node(Node* node, int data)
{
	if (node == nullptr)
		return new Node(data, 1, 0, 0, 0);

	if (data < node->mData) {
		node->left = add_node(node->left, data);
	}
	else if (data > node->mData) {
		node->right = add_node(node->right, data);
	}
	else
		return node;

	return balance(node);
}

Node* AVL::remove_node(Node* node, int data)
{
	if (!node)
		return nullptr;

	if (data < node->mData)
		node->left = remove_node(node->left, data);
	else if (data > node->mData)
		node->right = remove_node(node->right, data);
	else {
		if (node->left && node->right) {
			Node* temp = smallest_node(node->right);
			node->mData = temp->mData;
			node->right = remove_node(node->right, node->mData);
		}
		else {
			Node* temp = node;
			if (!node->left)
				node = node->right;
			else if (!node->right)
				node = node->left;
			delete temp;
		}
	}

	return balance(node);
}

Node* AVL::single_left_rotation(Node* &parent_node)
{
	Node* temp = parent_node->left;
	parent_node->left = temp->right;
	temp->right = parent_node;
	update(parent_node);
	update(temp);
	return temp;
}

Node* AVL::single_right_rotation(Node* &parent_node)
{
	Node* temp = parent_node->right;
	parent_node->right = temp->left;
	temp->left = parent_node;
	update(parent_node);
	update(temp);
	return temp;
}

Node* AVL::add(int data)
{
	if (root == nullptr) {
		root = new Node(data, 1, ROOT_MOVE_X, WIDTH / 2, 1.5f * RADIUS);
		return root;
	}
	root = add_node(root, data);
	return nullptr;
}

Node* AVL::remove(int data)
{
	root = remove_node(root, data);
	return nullptr;
}