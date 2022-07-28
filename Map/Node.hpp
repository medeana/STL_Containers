#ifndef NODE_HPP
# define NODE_HPP

template <class T>
struct Node
{
    typedef T 			value_type;
    typedef Node* 		node_pointer;

    Node()
    {}
    explicit Node(const value_type & value, bool is_red = true, node_pointer parent = NULL,
        node_pointer right = NULL, node_pointer left = NULL) : value(value), 
            is_red(is_red), parent(parent), right(right), left(left)
    {}

    Node(const Node & rhs) : value(rhs.value), is_red(rhs.is_red), parent(rhs.parent),
        right(rhs.right), left(rhs.left) {}
    
    Node &operator=(const Node & rhs)
    {
        if (this != &rhs)
        {
            this->value = rhs.value;
            this->is_red = rhs.is_red;
            this->parent = rhs.parent;
            this->right = rhs.right;
            this->left = rhs.left;
        }
        return *this;
    
    }
    ~Node() {}

    value_type 			value;
    bool 				is_red;
    node_pointer 		parent;
    node_pointer 		right;
    node_pointer 		left;
};

#endif