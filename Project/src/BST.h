#pragma once
#include "Tree.h"
//TODO: maybe there'll be no need for the BST tree, keep it just in case

class BST : public Tree
{
private:
    Node* add_node(Node* node, int data);
    Node* remove_node(Node* node, int data);

public:
    Node* add(int data);
    Node* remove(int data);

    friend class Visualizer;
};