#include "BST.h"

Node* BST::add_node(Node* node, int data)
{
    if(!node)
        return node;
    //TODO: fix colliding nodes
    if (data < node->mData) {
        if (node->left == nullptr) {
            node->left = new Node(data, 1, node->move_x / MOVE_RATIO, node->position.x, node->position.y + MOVE_Y);
            height_update(node);
            node->left->update_pos();
            return node->left;
        }
        else
            add_node(node->left, data);
    }
    else if (data > node->mData) {
        if (node->right == nullptr) {
            node->right = new Node(data, 1, node->move_x / MOVE_RATIO, node->position.x, node->position.y + MOVE_Y);
            height_update(node);
            node->right->update_pos(false);
            return node->right;
        }
        else {
            height_update(node);
            add_node(node->right, data);
        }
    }
    else {
        return node;
    }
    return nullptr;
}

Node* BST::remove_node(Node* node, int data)
{
    if (node == nullptr)
        return nullptr;

    //lewa czesc drzewa
    if (data < node->mData) {
        node->left = remove_node(node->left, data);
    }
    //prawa czesc drzewa
    else if (data > node->mData) {
        node->right = remove_node(node->right, data);
    }
    //znalezlismy node z value == data
    else {
        //base case -> node nie ma zadnego dziecka wiec mozemy ustawic go na nullptr
        if (!node->left && !node->right) {
            return nullptr;
        }
        //ma prawego potomka, nie ma lewego 
        else if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;

        }
        else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = smallest_node(node->right);
        node->mData = temp->mData;
        node->right = remove_node(node->right, temp->mData);
    }
    return node;
}

Node* BST::add(int data)
{
    if (!this->root) {
        root = new Node(data, WIDTH / 2, 1.5f * RADIUS);
        return root;
    }
    else
        return add_node(this->root, data);
}

Node* BST::remove(int data)
{
    return remove_node(this->root, data);
}