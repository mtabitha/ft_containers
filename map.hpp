#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <algorithm>

# include "BidirectionalIterator.hpp"
# include "ReverseIterator.hpp"
# include "IteratorTraits.hpp"
# include "utils.hpp"
# include "pair.hpp"
# include "node.hpp"

namespace ft{

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<node <pair<const Key, T> > > > 
class map
{
public:
    typedef Key                                                                             key_type;
    typedef T                                                                               mapped_type;
    typedef pair<const Key, T>                                                              value_type;
    typedef size_t                                                                          size_type;
    typedef ptrdiff_t                                                                       difference_type;
    typedef Compare                                                                         key_compare;
    typedef Allocator                                                                       allocator_type;
    typedef value_type&                                                                     reference;
    typedef const value_type&                                                               const_reference;
    typedef value_type*					                                                    pointer;
    typedef const value_type*			                                                    const_pointer;
    typedef BidirectionalIterator<value_type, pointer, reference>              iterator;
    typedef BidirectionalIterator<value_type, const_pointer, const_reference>  const_iterator;
    typedef ReverseBIterator<iterator>                                                      reverse_iterator;
    typedef ReverseBIterator<const_iterator>                                                const_reverse_iterator;
    typedef node<value_type>                                                                node_type;

    class value_compare 
    {  
		friend class map;
	protected:
		Compare comp;
		explicit value_compare (Compare c) : comp(c) {} 
	public:
		bool operator() (const value_type& x, const value_type& y) const {
			return comp(x.first, y.first);
		}
	};
private:
    node_type*          _head;
    node_type*          _first;
    node_type*          _last;

    allocator_type      _alloc;
    key_compare         _comp;
    size_type           _sz;
public:
    map() : _head(nullptr), _first(nullptr), _last(nullptr), _alloc(std::allocator<value_type>()), _comp(key_compare()), _sz(0)
    { init_map(); }

    explicit map( const Compare& comp, const Allocator& alloc = Allocator()) : _head(nullptr), _first(nullptr), _last(nullptr), _comp(comp), _alloc(alloc), _sz(0)
    { init_map(); }

    template< class InputIterator >
    map( InputIterator first, typename ft::enable_if< std::__is_input_iterator< InputIterator >::value,InputIterator >::type last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
    : _alloc(alloc),_comp(comp),  _sz(0)
    { init_map(); insert(first, last); }

    map( const map& other )
    { init_map(); insert(other.begin(), other.end()); }

    map& operator= (const map& x) {
			if (this != &x) {
				clear();
				_alloc = x._alloc;
				_comp = x._comp;
				insert(x.begin(), x.end());
			}
			return (*this);
		}

    ~map()
    {
        clear();
        _alloc.destroy(_first);
        _alloc.deallocate(_first, 1);
        _alloc.destroy(_last);
        _alloc.deallocate(_last, 1);
    }

    void clear()
    {
        if (!empty())
            clear(_head);
        _first->parent = _last;
        _last->parent = _first;
    }

    pair<iterator, bool> insert( const value_type& value )
    {
        if (!_sz)
            return (ft::make_pair(iterator(insert_head(value)), true));
        node_type*  n = _head;
        while (n)
        {
            if (value_comp()(value, n->data))
            {
                if (n->left && n->left != _first)
                    n = n->left;
                else 
                    return (ft::make_pair(iterator(insert_left(n, value)), true));
            }
            else if (value_comp()(n->data, value))
            {
                if (n->right && n->right != _last)
                    n = n->right;
                else
                    return (ft::make_pair(iterator(insert_right(n, value)), true));
            }
            else
                return (ft::make_pair(iterator(n), false));
        }
        return (ft::make_pair(iterator(), false));
    }
    iterator insert( iterator hint, const value_type& value )
    {
        (void)hint;
        return (insert(value).first);
    }
    template< class InputIterator >
    void insert( InputIterator first, typename ft::enable_if< std::__is_input_iterator< InputIterator >::value,InputIterator >::type last )
    {
        for( ; first != last; ++first)
            insert(*first);
    }

    iterator find( const Key& key )
    {
        iterator it = begin();
        for(iterator end_it = end(); it != end_it; ++it)
            if (it->first == key)
                break ;
        return (it);
    }

    const_iterator find( const Key& key ) const
    {
        const_iterator it = begin();
        for(const_iterator end_it = end(); it != end_it; ++it)
            if (it->first == key)
                break ;
        return (it);
    }

    T& at (const Key& key)
	{
        iterator it = find(key);
		if (it == end())
			throw std::out_of_range("map::at:  key not found");
		return (it->second);
	}

	const T& at (const Key& key) const
	{
        const_iterator it = find(key);
		if (it == end())
			throw std::out_of_range("map::at:  key not found");
		return (it->second);
	}

    void erase( iterator pos )
    {
        node_type*  n = find_node(pos);
        if (n == _last)
            return ;
        delete_node(n);
        _alloc.destroy(n);
        _alloc.deallocate(n, 1);
        --_sz;
    }

    void erase( iterator first, iterator last )
    {
        if (first == begin() && last == end()) {
            clear();
            return ;
        }

        iterator next = first;
        ++next;
        for(; first != last; ++next )
        {
            erase(first);
            first = next;
        }
    }
    size_type erase( const key_type& key )
    {
        iterator it = find(key);
        if (it == end())
            return 0;
        erase(it);
        return (1);
    }

    mapped_type&    operator [] (const Key& key)
    { return (insert(ft::make_pair(key, mapped_type())).first->second); }

    iterator lower_bound( const Key& key )
    {
        iterator it = begin();
        iterator end_it = end();

        for (; it != end_it; ++it)
            if (!key_comp()(it->first, key))
                break;
        return (it);
    }
    const_iterator lower_bound( const Key& key ) const
    {
        const_iterator it = begin();
        const_iterator end_it = end();

        for (; it != end_it; ++it)
            if (!key_comp()(it->first, key))
                break;
        return (it);
    }

    iterator upper_bound( const Key& key )
    {
        iterator it = begin();

        for (iterator end_it = end(); it != end_it; ++it)
            if (key_comp()( key, it->first))
                break;
        return (it);
    }
    const_iterator upper_bound( const Key& key ) const
    {
        const_iterator it = begin();

        for (const_iterator end_it = end(); it != end_it; ++it)
            if (key_comp()( key, it->first))
                break;
        return (it);
    }

    size_type	count(const key_type& key) const 
    {
        const_iterator  it_e = end();

		for(const_iterator	it = begin() ; it != it_e; ++it)
			if (it->first == key)
				return 1;
		return 0;
	}

    key_compare key_comp() const
    { return key_compare(); }

    value_compare	value_comp() const 
    { return value_compare(this->_comp); }

    pair<iterator,iterator> equal_range( const Key& key )
    { return ft::make_pair(lower_bound(key), upper_bound(key)); }

    pair<const_iterator,const_iterator> equal_range( const Key& key ) const
    { return ft::make_pair(lower_bound(key), upper_bound(key)); }


    bool	empty() const { return (!_sz); }
	size_type	size() const { return (_sz); }
	size_type	max_size() const { return _alloc.max_size(); }

    iterator        begin (void)
	{ return (_first->parent); }
	const_iterator  begin (void) const
	{ return (_first->parent); }
	iterator        end (void)
	{ return (_last); }
	const_iterator  end (void) const
	{ return (_last); }

    reverse_iterator        rbegin (void)
	{ return (iterator(_last)); }
	const_reverse_iterator  rbegin (void) const
	{ return (const_iterator(_last)); }
	reverse_iterator        rend (void)
	{ return (iterator(_first->parent)); }
	const_reverse_iterator  rend (void) const
	{ return (const_iterator(_first->parent)); }

    void swap (map& other)
	{
		ft::swap(_sz, other._sz);
		ft::swap(_alloc, other._alloc);
		ft::swap(_head, other._head);
		ft::swap(_first, other._first);
		ft::swap(_last, other._last);
		ft::swap(_comp, other._comp);
	}
private:
    void    clear(node_type*    n)
    {
        if (!n)
            return;
        clear(n->left);
        clear(n->right);
        if (valid_node(n))
        {
            _alloc.destroy(n);
            _alloc.deallocate(n, 1);
            --_sz;
        }
    }

    node_type*      findSmallest(node_type* n)
    {
        n = n->right;
        while (valid_node(n->left))
            n = n->left;
        return (n);
    }

    void            transplant(node_type* n, node_type* other_n)
    {
        bool c_tmp = n->red;
        n->red = other_n->red;
        other_n->red = c_tmp;

        node_type* tmp = n->parent;
        n->parent = other_n->parent;
        other_n->parent = tmp;
        if (!other_n->parent)
            _head = other_n;
        else if (n == other_n->parent->left) 
			other_n->parent->left = other_n;
		else 
			other_n->parent->right = other_n;
        if (other_n == n->parent->left)
            n->parent->left = n;
        else 
			n->parent->right = n;

        tmp = n->left;
        n->left = other_n->left;
        other_n->left = tmp;
        
        tmp = n->right;
        n->right = other_n->right;
        other_n->right = tmp;

        if (n->left)
            n->left->parent = n;
        if (n->right)
            n->right->parent = n;

        if (other_n->left)
            other_n->left->parent = other_n;
        if (other_n->right)
            other_n->right->parent = other_n;

    }

    node_type *sibling(node_type *n)
    {
    	if (n == n->parent->left)
    		return n->parent->right;
    	else
    		return n->parent->left;
    }

    void delete_case6(node_type *n)
    {
    	node_type *s = sibling(n);

    	s->red = n->parent->red;
        n->parent->red = false;

    	if (n == n->parent->left) {
            s->right->red = false;
    		left_rot(n->parent);
    	} else {
    		s->left->red = false;
    		right_rot(n->parent);
    	}
    }

    void delete_case5(node_type *n)
    {
    	node_type *s = sibling(n);

    	if  (!s->red) // (!s->red && !n->parent->red) 
        { 
    		if ((n == n->parent->left) &&
    		    (!valid_node(s->right) || !s->right->red) &&
    		    (s->left->red)) 
            { 
    			s->red = true;
    			s->left->red = false;
    			right_rot(s);
    		} 
            else if ((n == n->parent->right) &&
    		           (!valid_node(s->left) || !s->left->red) &&
    		           (s->right->red)) 
            {
    			s->red = false;
    			s->right->red = true;
    			left_rot(s);
    		}
    	}
    	delete_case6(n);
    }

    void delete_case4(node_type *n)
    {
    	node_type *s = sibling(n);

    	if (n->parent->red && !s->red && 
            (!valid_node(s->left) || !s->left->red) && 
            (!valid_node(s->right) || !s->right->red) ) 
        {
    		s->red = true;
    		n->parent->red = false;
    	} 
        else
    		delete_case5(n);
    }

    void delete_case3(node_type *n)
    {
    	node_type *s = sibling(n);

    	if (!n->parent->red && !s->red && (!valid_node(s->left) || !s->left->red) && 
            (!valid_node(s->right) || !s->right->red)) 
        {
    		s->red = true;
    		delete_case1(n->parent);
    	} 
        else
    		delete_case4(n);
    }

    void delete_case2(node_type *n)
    {
    	node_type *s = sibling(n);

    	if (s->red) {
    		n->parent->red = true;
    		s->red = false;
    		if (n == n->parent->left)
    			left_rot(n->parent);
    		else
    			right_rot(n->parent);
    	} 
    	delete_case3(n);
    }

    void delete_case1( node_type *n)
    {
    	if (n->parent)
    		delete_case2(n);
    }

    void            bind_first_node(node_type* n)
    {
        if (valid_node(n->left))
            n = n->left;
        _first->parent = n;
        n->left = _first;
    }
    void            bind_last_node(node_type* n)
    {
        if (valid_node(n->right))
            n = n->right;
        _last->parent = n;
        n->right = _last;
    }

    void            deleteRoot(node_type* child)
    {
        if (_sz == 1)
        {
            _head = nullptr;
            _first->parent = _last;
            _last->parent = _first;
        }
        else if (valid_node(child))
        {
            _head = child;
            child->parent = nullptr;
            child->red = false;

            _first->parent =  child;
            child->left = _first;
            _last->parent =  child;
            child->right = _last;
        }
    }

    node_type*      ret_child(node_type* n)
    {
        if (n == _first->parent)
            return (n->right);
        if (n == _last->parent)
            return (n->left);
        if (n->left)
            return n->left;
        if (n->right)
            return n->right;
        return (nullptr);
    }
    
    void 
    replace_node(node_type* n, node_type* child) 
    {
        if (child)
            child->parent = n->parent;
        if (n == n->parent->left) 
            n->parent->left = child;
        else
            n->parent->right = child;

    }

    void            deleteOneChild(node_type*   n)
    {
        node_type*  child = ret_child(n);
        if (n == _head)   {
            deleteRoot(child);
            return ;
        }

        if (!n->red)
        {
            if (valid_node(child) && child->red)
                child->red = false;
            else
                delete_case1(n);
        }

        replace_node(n, child);
        if (n == _first->parent)
            bind_first_node(n->parent);
        else if (n == _last->parent)
            bind_last_node(n->parent); 
    }

    void            delete_node(node_type*  n)
    {
        if (n->right && n->left && n->right != _last && n->left != _first)
        {
            node_type* other_n = findSmallest(n);
            transplant(n, other_n);
        }
        deleteOneChild(n);
    }

    node_type*      find_node(iterator pos)
    {
        node_type* n(_head);

        while (valid_node(n))
        {
            if (value_comp()(*pos, n->data))
                n = n->left;
            else if (value_comp()(n->data, *pos))
                n = n->right;
            else
                return n;
        }
        return _last;
    }

    bool            valid_node(node_type* n)
    {
        return (n && n != _first && n != _last);
    }

    node_type*      swap_col(node_type* head)
    {
        head->red           = true;
        head->left->red     = false;
        head->right->red    = false;
        return (head);
    }

    void            left_rot(node_type* x)
    {
        node_type*  y   = x->right;
        x->right        = y->left;
        y->parent       = x->parent;
        y->left         = x;
        x->parent       = y;
        if (x->right)
            x->right->parent = x;      
        if (!y->parent)
            _head = y;
        else if (y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }

    void            right_rot(node_type* x)
    {
        node_type*  y   = x->left;
        x->left         = y->right;
        y->parent       = x->parent;
        y->right        = x;
        x->parent       = y;
        if (x->left)
            x->left->parent = x;      
        if (!y->parent)
            _head = y;
        else if (y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }

    void            balancing(node_type* new_node)
    {
		
        while(new_node != _head && new_node->red && new_node->parent->red)
        {
            node_type*  parent  = new_node->parent;
            node_type*  ded     = parent->parent;
            if (parent == ded->left)
            {
                node_type*  uncle = ded->right;
                if (valid_node(uncle) && uncle->red)
                    new_node = swap_col(ded);
                else if (new_node == parent->right)
                {
                    left_rot(parent);
                    new_node = parent;
                }
                else
                {
                    right_rot(ded);
                    ded->red = true;
                    parent->red = false;
                }
            }
            else if (parent == ded->right)
            {
                node_type*  uncle = ded->left;
                if (valid_node(uncle) && uncle->red)
                    new_node = swap_col(ded);
                else if (new_node == parent->left)
                {
                    right_rot(parent);
                    new_node = parent;
                }
                else
                {
                    left_rot(ded);
                    ded->red = true;
                    parent->red = false;
                }
            }
        }
        _head->red = false;
    }

    node_type*      insert_left(node_type* n, const value_type& value)
    {
        node_type* new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(value));
        new_node->parent = n;
        new_node->left = n->left;
        n->left ? n->left->parent = new_node : 0;
        n->left = new_node;
        ++_sz;
        balancing(new_node);
        return new_node;
    }

    node_type*      insert_right(node_type* n, const value_type& value)
    {
        node_type* new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(value));
        new_node->parent    = n;
        new_node->right     = n->right;
        n->right ? n->right->parent = new_node : 0;
        n->right = new_node;
        ++_sz;
        balancing(new_node);
        return new_node;
    }

    node_type*      insert_head(const value_type& value)
    {
        _head = _alloc.allocate(1);
        _alloc.construct(_head, node_type(value, false));
        _first->parent  = _last->parent = _head;
        _head->left     = _first;
        _head->right    = _last;
        ++_sz;
        return _head;
    }

    void    init_map(void)
    {
        _first  = _alloc.allocate(1);
        _last   = _alloc.allocate(1);
        _alloc.construct(_first, node_type());
        _alloc.construct(_last, node_type());
        _first->parent  = _last;
        _last->parent   = _first;
        _last->fict = _first->fict = true;
    }
    


};
template< class Key, class T, class Compare, class Allocator > 
bool operator< (const map<Key, T,Compare, Allocator >& v1, const map<Key, T,Compare, Allocator > & v2) 
{
	return ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
}

template< class Key, class T, class Compare, class Allocator > 
bool operator==(const map<Key, T,Compare, Allocator >& v1, const map<Key, T,Compare, Allocator > & v2) 
{
	return ft::equal(v1.begin(), v1.end(), v2.begin(), v2.end());
}

template< class Key, class T, class Compare, class Allocator > 
bool operator!=(const map<Key, T,Compare, Allocator >& v1, const map<Key, T,Compare, Allocator > & v2) 
{
	return !operator==(v1, v2);
}

template< class Key, class T, class Compare, class Allocator > 
bool operator<=(const map<Key, T,Compare, Allocator >& v1, const map<Key, T,Compare, Allocator > & v2) 
{
	return (!operator<(v2, v1));
}

template< class Key, class T, class Compare, class Allocator > 
bool operator> (const map<Key, T,Compare, Allocator >& v1, const map<Key, T,Compare, Allocator > & v2) 
{
	return operator<(v2, v1);
}

template< class Key, class T, class Compare, class Allocator > 
bool operator>=(const map<Key, T,Compare, Allocator >& v1, const map<Key, T,Compare, Allocator > & v2) 
{
	return (!operator<(v1, v2));
}

template< class Key, class T, class Compare, class Allocator > 
void swap(map<Key, T,Compare, Allocator >& x, map<Key, T,Compare, Allocator > & y) 
{
	x.swap(y);
}

}

#endif