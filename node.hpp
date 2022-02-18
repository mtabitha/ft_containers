#ifndef NODE_HPP
# define NODE_HPP

namespace ft {
template <typename T>
struct  node
{
    node*   parent;
    node*   left;
    node*   right;
    T       data;
    bool    red;
    bool    fict;

    node() : parent(nullptr), left(nullptr), right(nullptr), red(false)
    ,fict(false)
    {}

    node(const T& val, bool red = true, bool fict = false) : parent(nullptr), left(nullptr), right(nullptr), data(val), red(red)
    ,fict(fict)
    {}

    node(const node& other) : parent(other.parent), left(other.left), right(other.right), data(other.data), red(other.red)
    ,fict(other.fict)
    {}

    static void    next(node*& n)
    {
        if (n->fict)
            n = n->parent;
        else if  (n->right)
        {
            n = n->right;
            while (n->left)
                n = n->left;
        }
        else if (n->parent)
        { 
            const node*     tmp = n;
            n = n->parent;
            while (n->left != tmp)
            {
                tmp = n;
                n = n->parent;
            }
        }
    }
    static void    prev(node*& n)
    {
        if (n->fict)
            n = n->parent;
        else if (n->left) 
        {
		    n = n->left;
		    while (n->right)
			    n = n->right;
	    }
	    else if (n->parent)
	    {
            const node*     tmp = n;
            n = n->parent;
            while (n->right != tmp)
            {
                tmp = n;
                n = n->parent;
            }
        }
    }

    bool	operator==(const node& other) 
    { return (this->data == other.data); }
	bool	operator!=(const node& other) 
    { return (this->data != other.data); }
	bool	operator>(const node& other) 
    { return (this->data > other.data);  }
	bool	operator<(const node& other) 
    { return (this->data < other.data);  }
	bool 	operator<=(const node& other) 
    { return (this->data <= other.data); }
    bool 	operator>=(const node& other) 
    { return (this->data >= other.data); }


};

}

#endif