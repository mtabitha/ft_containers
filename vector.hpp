#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <algorithm>

# include "RandomIterator.hpp"
# include "ReverseIterator.hpp"
# include "IteratorTraits.hpp"
# include "utils.hpp"


namespace ft {

template <typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
    typedef T                                           		value_type;
    typedef Alloc                                      			allocator_type;
    typedef typename allocator_type::reference          		reference;
    typedef typename allocator_type::pointer            		pointer;
    typedef typename allocator_type::const_reference    		const_reference;
    typedef typename allocator_type::const_pointer      		const_pointer;
    typedef RandomIterator<value_type, false>                 			iterator;
    typedef RandomIterator<value_type const, true>           			const_iterator;
    typedef ReverseRIterator<iterator>                 			reverse_iterator;
    typedef ReverseRIterator<const_iterator>           			const_reverse_iterator;
    typedef typename iterator_traits<iterator>::difference_type difference_type;
    typedef size_t                                      		size_type;
private:
	pointer			_ptr;
	size_type		_sz;
	size_type		_capacity;
	allocator_type	_alloc;

	void	destroy(pointer ptr)
	{
		_alloc.destroy(ptr);
		--_sz;
	}
	void	construct(pointer ptr, const value_type& val)
	{
		_alloc.construct(ptr, val);
		++_sz;
	}
	void	allocate(size_type n)
	{
		_ptr = _alloc.allocate(n);
		_capacity = n;
	}
	void	deallocate(void)
	{
		_alloc.deallocate(_ptr, _capacity);
		_ptr = nullptr;
		_capacity = 0;
	}
public:
	vector (const allocator_type& alloc = allocator_type())
	: _ptr(nullptr), _sz(0), _capacity(0), _alloc(alloc) 
	{}

	vector (const size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	:_ptr(nullptr), _sz(0), _capacity(0), _alloc(alloc)
	{
		assign(n , val);
	}

    template < class InputIterator >
    vector (typename ft::enable_if< std::__is_input_iterator< InputIterator >::value,InputIterator >::type first, InputIterator last, const allocator_type& alloc = allocator_type())
	:_ptr(nullptr), _sz(0), _capacity(0), _alloc(alloc)
	{
		assign(first, last);
	}

	vector (const vector& x) : _ptr(nullptr), _sz(0), _capacity(0), _alloc(x.get_allocator())
	{
		*this = x;
	}

	~vector()
    {
        clear();
        deallocate();
    }

	vector& operator= (const vector& x)
	{
		assign(x.begin(), x.end());
		return (*this);
	}

	iterator begin (void)
	{
		return (_ptr);
	}

	const_iterator begin (void) const
	{
		return (_ptr);
	}
	iterator end (void)
	{
		return (_ptr + _sz);
	}
	const_iterator end (void) const
	{
		return (_ptr + _sz);
	}
	reverse_iterator rbegin (void)
	{
		return (end());
	}
	const_reverse_iterator rbegin (void) const
	{
		return (end());
	}
	reverse_iterator rend (void)
	{
		if (!_ptr)
			return iterator();
		return (begin());
	}
	const_reverse_iterator rend (void) const
	{
		if (!_ptr)
			return iterator();
		return (begin());
	}

	size_type size() const
	{
		return (_sz);
	}

	size_type max_size() const
	{
		return (std::min((size_type) std::numeric_limits<difference_type>::max(),
						std::numeric_limits<size_type>::max() / sizeof(value_type)));
	}

	void resize (size_type n, value_type val = value_type ())
	{
		if (_sz == n)
			return ;
		if (n > _capacity)
			reserve(n);
		for (size_type i = _sz; _sz < n ; ++i)
			construct(_ptr + i, val);
		for (size_type i = n; _sz > n; ++i)
			destroy(_ptr + i);
	}

	size_type capacity() const
	{
		return (_capacity);
	}

	bool		empty(void) const
	{
		return (!_sz);
	}

	void reserve(size_type new_capacity)
	{
		if (!new_capacity || new_capacity <= _capacity)
			return ;
		
		pointer 	old_ptr = _ptr;
		size_type	old_cap = _capacity;
		allocate(new_capacity);
		for (size_type i = 0; i < _sz; ++i)
		{
			construct(_ptr + i, old_ptr[i]);
			destroy(old_ptr + i);
		}
		_alloc.deallocate(old_ptr, old_cap);
	}

	reference operator [] (difference_type n)
	{
		return (_ptr[n]);
	}

	reference at (size_type n)
	{
		if (n >= _sz)
			throw std::out_of_range("vector");
		return (_ptr[n]);
	}

	const_reference at (size_type n) const
	{
		if (n >= _sz)
			throw std::out_of_range("vector");
		return (_ptr[n]);
	}

	reference front()
	{
		return (*_ptr);
	}

	const_reference front() const
	{
		return (*_ptr);
	}

	reference back()
	{
		return (_ptr[_sz - 1]);
	}

	const_reference back() const
	{
		return (_ptr[_sz - 1]);
	}

	void assign (size_type n, const value_type& val)
	{
		size_type e_index = _sz;

		if (n != _sz)
			resize(n, val);
		iterator i_end(_ptr + e_index);
		iterator n_end(_ptr + _sz);
		iterator it(begin());
		for (iterator stop(n < e_index ? n_end : i_end); it != stop; ++it)
			*it = val;
	}
    template < class InputIterator >
  	void assign (InputIterator first, typename ft::enable_if<std::__is_input_iterator< InputIterator >::value, InputIterator >::type last)
	{
		size_type n = std::distance(first, last);

		if (n > _capacity)
			reserve(n);
		iterator i_end(end());
		iterator it(begin());
		for (; first != last; ++first, ++it)
			if (it < i_end)
				*it = *first;
			else
				construct(&*it, *first);
		for (; it < i_end; ++it)
			destroy(&*it);
	}

	void push_back (const value_type& val)
	{
		insert(end(), 1, val);	
	}

	void pop_back(void)
	{
		erase(--end());
	}

	iterator insert (iterator position, const value_type& val)
	{
		size_type index = position - begin();
		insert(position, 1, val);
		return (_ptr + index);
	}

	void insert (iterator position, size_type n, const value_type& val)
	{
		if (!n)
			return ;
		size_type index = position - begin();
		if (_sz + n > _capacity)
			reserve(_sz + n);
		if (index == _sz)
			for (size_type i = 0; i < n; ++i)
				construct(_ptr + _sz, val);
		else
		{
			reverse_iterator cpy_end(end());
			reverse_iterator cpy_stop(_ptr + index);
			reverse_iterator start(_ptr + _sz + n);
			reverse_iterator itv2(end());
			for (; start != cpy_end; ++start)
				construct(&*start, itv2 != cpy_stop ? *itv2++ : val);
			for (; start != cpy_stop; ++start)
				*start = (itv2 != cpy_stop) ? *itv2++ : val;
		}
	}
    template < class InputIterator >
    void insert (iterator position, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value,InputIterator>::type first, InputIterator last)
	{
		size_type n = std::distance(first, last);
		if (!n)
			return ;
		size_type index = position - begin();
		if (_sz + n > _capacity)
			reserve(_sz + n);
		if (index == _sz)
			for (iterator it(end()); first != last; ++it, ++first)
				construct(&*it, *first);
		else
		{
			reverse_iterator cpy_end(end());
			reverse_iterator cpy_stop(_ptr + index);
			reverse_iterator start(_ptr + _sz + n);
			reverse_iterator itv2(end());
			for (; start != cpy_end; ++start)
				construct(&*start, itv2 != cpy_stop ? *itv2++ : *--last);
			for (; start != cpy_stop; ++start)
				*start = (itv2 != cpy_stop) ? *itv2++ : *--last;
		}
	}

	iterator erase (iterator position)
	{
		iterator				stop(--end());
		iterator 	it(position);
		for ( ; it != stop; it++)
			*it = *(it + 1);
		destroy(&*it);
		return (position);
	}

	iterator erase (iterator first, iterator last)
	{	
		
		iterator 	ret(first);
		iterator 	it(last);
		iterator 	stop(end());


		for ( ; it != stop; first++)
			*first = *it++;
		for ( ; first != stop; first++)
			destroy(&*first);
		return (ret);
	}

	void swap (vector& x)
	{
		ft::swap(_capacity, x._capacity);
		ft::swap(_sz, x._sz);
		ft::swap(_alloc, x._alloc);
		ft::swap(_ptr, x._ptr);
	}

	void		clear(void)
	{
		for (int i = 0; _sz > 0; i++)
			destroy(_ptr + i);
	}

	allocator_type get_allocator() const
	{
		return (allocator_type());
	}
};

template < class T, class Alloc >
bool operator< (const vector<T,Alloc>& v1, const vector<T,Alloc> & v2) 
{
	return ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
}

template < class T, class Alloc >
bool operator==(const vector<T,Alloc>& v1, const vector<T,Alloc> & v2) 
{
	return ft::equal(v1.begin(), v1.end(), v2.begin(), v2.end());
}

template < class T, class Alloc >
bool operator!=(const vector<T,Alloc>& v1, const vector<T,Alloc> & v2) 
{
	return !operator==(v1, v2);
}

template < class T, class Alloc >
bool operator<=(const vector<T,Alloc>& v1, const vector<T,Alloc> & v2) 
{
	return (!operator<(v2, v1));
}

template < class T, class Alloc >
bool operator> (const vector<T,Alloc>& v1, const vector<T,Alloc> & v2) 
{
	return operator<(v2, v1);
}

template < class T, class Alloc >
bool operator>=(const vector<T,Alloc>& v1, const vector<T,Alloc> & v2) 
{
	return (!operator<(v1, v2));
}

template < class T, class Alloc >
void swap(vector<T,Alloc>& x, vector<T,Alloc> & y) 
{
	x.swap(y);
}

}

#endif