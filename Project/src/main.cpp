#include "Visualizer.h"
#include "AVL.h"
#include "BST.h"

int main()
{
	Visualizer v;
	Tree* tree = v.button_loop();
	v.main_loop(tree);
}