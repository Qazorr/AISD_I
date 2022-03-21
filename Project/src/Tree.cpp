#include "Tree.h"

void Tree::traverse_inorder(Node* node)
{
    if (!node)
        return;
    traverse_inorder(node->left);
    std::cout << node->mData << " ";
    traverse_inorder(node->right);
}

void Tree::traverse_preorder(Node* node)
{
    if (!node)
        return;
    std::cout << node->mData << " ";
    traverse_preorder(node->left);
    traverse_preorder(node->right);
}

void Tree::traverse_postorder(Node* node)
{
    if (!node)
        return;
    traverse_postorder(node->left);
    traverse_postorder(node->right);
    height_update(node);
    std::cout << node->mData << " ";
}

int Tree::get_height(Node* node)
{
    return node ? node->mHeight : 0;
}

void Tree::height_update(Node* node)
{
    if (node)
        node->mHeight = std::max(get_height(node->left), get_height(node->right)) + 1;
}

Node* Tree::smallest_node(Node* node)
{
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

void Tree::display_inorder()
{
    this->traverse_inorder(this->root);
}

void Tree::display_preorder()
{
    this->traverse_preorder(this->root);
}

void Tree::display_postorder()
{
    this->traverse_postorder(this->root);
}

void Tree::update_node_position(Node* parent, Node* child)
{
    //child->mHeight = parent->mHeight + 1;
    child->move_x = parent->move_x / MOVE_RATIO;
    child->position.x = parent->position.x;
    child->position.y = parent->position.y + MOVE_Y;
    if (parent->left == child) child->update_pos();
    else child->update_pos(false);
}

int Tree::smallest()
{
    Node* node = this->root;
    while (node && node->left)
        node = node->left;
    return node ? node->mData : -1;
}

int Tree::largest()
{
    Node* node = this->root;
    while (node && node->right)
        node = node->right;
    return node ? node->mData : -1;
}

Node* Tree::search_node(Node* node, int data)
{
    if (node == nullptr) return node;
    if (node->mData == data) {
        return node;
    }
    else if (node->mData < data) {
        return search_node(node->right, data);
    }
    else {
        return search_node(node->left, data);
    }
}

Node* Tree::search(int data)
{
    return search_node(this->root, data);
}