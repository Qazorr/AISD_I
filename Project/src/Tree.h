#pragma once
#include "config.h"
//TODO: fix the coliding of the nodes

struct Node {
    int mData = 0;
    int mHeight = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    sf::Vector2f position;
    float move_x = ROOT_MOVE_X;

    Node() = default;
    Node(int data, float x, float y) : mData(data)
    {
        sf::Vector2f temp(x, y);
        position = temp;
    }
    Node(int data, int h, float move, float x, float y)
    {
        this->mData = data;
        this->mHeight = h;
        this->move_x = move;
        sf::Vector2f temp(x, y);
        this->position = temp;
    }

    void update_pos(bool left = true)
    {
        if (left) {
            this->position.x -= (this->move_x);
        }
        else {
            this->position.x += (this->move_x);
        }
        //this->position.y += mHeight * MOVE;
    }
};

class Tree {
private:
    void traverse_inorder(Node* node);
    void traverse_preorder(Node* node);
    void traverse_postorder(Node* node);
    Node* search_node(Node* node, int data);

public:
    Node* root = nullptr;
    int get_height(Node* node);
    void height_update(Node* node);
    virtual Node* add(int data) = 0;
	virtual Node* remove(int data) = 0;
    void update_node_position(Node* parent, Node* child);
    int smallest();
    int largest();
    void display_inorder();
    void display_preorder();
    void display_postorder();
    Node* search(int data);
    Node* smallest_node(Node* node);

    friend class Visualizer;
};