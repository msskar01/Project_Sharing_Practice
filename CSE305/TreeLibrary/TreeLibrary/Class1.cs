using System;

namespace TreeLibrary
{
    struct Node<T>
    {
        T element;// The data in the node 
        public Node left { get; set; } // Left child
        Node right; // Right child 
        Node(T value)//Giving a node a value
        {
            this->element = value;
            this->left = this->right = nullptr;
        }
    };
}
