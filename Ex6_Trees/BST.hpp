#include <iostream>

template <typename T>
struct Node{
    T mData;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;

    Node() = default;
    Node(T data) : mData(data) {}
};

template <typename T>
class BST
{
    private:
        Node<T> *root = nullptr;

        //znajduje pierwsze wolne pole i dodaje do drzewa
        void insert_f(Node<T> *node, int data)
        {
            if(data < node->mData) {
                if(node->left == nullptr)
                    node->left = new Node<T>(data);
                else
                    insert_f(node->left, data);
            } else if(data > node->mData) {
                if(node->right == nullptr)
                    node->right = new Node<T>(data);
                else
                    insert_f(node->right, data);
            }  else {
                //nic sie nie stanie, w drzewie BST nie przechowuje duplikatów
            }
        }

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

        Node<T>* remove_f(Node<T>* node, int data)
        {
            if(node == nullptr)
                return nullptr;
            
            //lewa czesc drzewa
            if(data < node->mData) {
                node->left = remove_f(node->left, data);
            }
            //prawa czesc drzewa
            else if(data > node->mData) {
                node->right = remove_f(node->right, data);
            }
            //znalezlismy node z value == data
            else {
                //base case -> node nie ma zadnego dziecka wiec mozemy ustawic go na nullptr
                if(!node->left && !node->right) {
                    return nullptr;
                }
                //ma prawego potomka, nie ma lewego 
                else if(!node->left) {
                    Node<T> *temp = node->right;
                    delete node;
                    return temp;
                } else if(!node->right) {
                    Node<T> *temp = node->left;
                    delete node;
                    return temp;
                }

                Node<T> *temp = smallest(node->right);

                node->mData = temp->mData;

                node->right = remove_f(node->right, temp->mData);
            }
            return node;
        }

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

        Node<T>* smallest(Node<T>* node)
        {
            while(node && node->left)
                node = node->left;
            return node;
        }

        Node<T>* largest(Node<T>* node)
        {
            while(node && node->right)
                node = node->right;
            return node;
        }

    public:    

        ~BST()
        {
            while(root)
                remove(root->mData);
        }

        T min()
        {
            if(!root)
                throw std::out_of_range("The tree is empty");
            Node<T>* curr = root;
            while(curr && curr->left)
                curr = curr->left;
            return curr->mData;
        }

        T max()
        {
            if(!root)
                throw std::out_of_range("The tree is empty");
            Node<T>* curr = root;
            while(curr && curr->right)
                curr = curr->right;
            return curr->mData;
        }

        inline void display_inorder() { this->traverse_inorder(this->root); }
        inline void display_preorder() { this->traverse_preorder(this->root); }
        inline void display_postorder() { this->traverse_postorder(this->root); }
        void insert(T data)
        {
            if(!this->root)
                root = new Node<T>(data);
            else
                insert_f(this->root, data);
        }
        inline void remove(T data) { root = remove_f(this->root, data); }
        inline Node<T>* find(T data) { return find_f(this->root, data); }
};
