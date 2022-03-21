#include <iostream>

template <typename T>
struct Node {
    T mData;
    int mHeight;
    Node<T> *left, *right;

    Node() : mData{}, mHeight{}, left{}, right{} {}
    Node(T data, int height) : mData{data}, mHeight{height}, left{}, right{} {}
};

template <typename T>
class AVL {
    private:
        Node<T> *root = nullptr;

        inline int get_height(Node<T> *node) { return node ? node->mHeight : 0; }
        inline int get_balance_factor(Node<T> *node) { return node != nullptr ? get_height(node->left) - get_height(node->right) : -1; }

        //* update wysokosci dla poddrzewa       
        void update(Node<T>* node)
        {
            if(node)
                node->mHeight = std::max(get_height(node->left), get_height(node->right)) + 1;
        }

        //* funkcja balansujaca drzewo
        Node<T>* balance(Node<T>* node)
        {
            if(!node) return node;
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

        //* znajdz najmniejszy node od danego node'a
        Node<T>* smallest_node(Node<T>* node)
        {
            while (node && node->left) {
                node = node->left;
            }
            return node;
        }

        //* dodanie node'a do drzewa
        Node<T>* insert_f(Node<T>* node, int data)
        {
            if(node == nullptr)
                return new Node<T>(data, 1);

            if (data < node->mData)
                node->left = insert_f(node->left, data);
            else if (data > node->mData)
                node->right = insert_f(node->right, data);
            else
                return node;

            return balance(node);
        }

        //* usuniecie node'a z drzewa
        Node<T>* remove_f(Node<T> *node, int data)
        {
            if(!node)
                return nullptr;
            
            if(data < node->mData)
                node->left = remove_f(node->left, data);
            else if(data > node->mData)
                node->right = remove_f(node->right, data);
            else {
                if(node->left && node->right) {
                    Node<T>* temp = smallest_node(node->right);
                    node->mData = temp->mData;
                    node->right = remove_f(node->right, node->mData);
                }
                else {
                    Node<T>* temp = node;
                    if(!node->left)
                        node = node->right;
                    else if(!node->right)
                        node = node->left;
                    delete temp;
                }
            }

            return balance(node);
        }

        //* znalezienie node'a w drzewie
        Node<T>* find_f(Node<T> *node, int data)
        {
            if(node == nullptr) return node;
            if(node->mData == data) {
                return node;
            } else if(node->mData < data) {
                return find_f(node->right, data);
            } else {
                return find_f(node->left, data);
            }
        }

        //-------------rotations------------------

        Node<T>* single_left_rotation(Node<T>* &parent_node)
        {
            Node<T>* temp = parent_node->left;
            parent_node->left = temp->right;
            temp->right = parent_node;
            update(parent_node);
            update(temp);
            return temp;
        }

        Node<T>* single_right_rotation(Node<T>* &parent_node)
        {
            Node<T>* temp = parent_node->right;
            parent_node->right = temp->left;
            temp->left = parent_node;
            update(parent_node);
            update(temp);
            return temp;
        }

        //--------------------------

        void traverse_inorder(Node<T>* node)
        {
            if (!node)
                return;
            traverse_inorder(node->left);
            std::cout << node->mData << " ";
            traverse_inorder(node->right);
        }

        void traverse_preorder(Node<T>* node)
        {
            if (!node)
                return;
            std::cout << node->mData << " ";
            traverse_preorder(node->left);
            traverse_preorder(node->right);
        }

        void traverse_postorder(Node<T>* node)
        {
            if (!node)
                return;
            traverse_postorder(node->left);
            traverse_postorder(node->right);
            std::cout << node->mData << " ";
        }

    public:

        ~AVL()
        {
            while(root)
                remove(root->mData);
        }

        T min()
        {
            Node<T>* curr = root;
            while(curr && curr->left)
                curr = curr->left;
            return curr->mData;
        }

        T max()
        {
            Node<T>* curr = root;
            while(curr && curr->right)
                curr = curr->right;
            return curr->mData;
        }

        inline void display_inorder() { this->traverse_inorder(this->root); }
        inline void display_preorder() { this->traverse_preorder(this->root); }
        inline void display_postorder() { this->traverse_postorder(this->root); }
        inline void insert(T data) { root = insert_f(root, data); }
        inline void remove(T data) { root = remove_f(root, data); }
        inline Node<T>* find(T data) { return find_f(this->root, data); }
};