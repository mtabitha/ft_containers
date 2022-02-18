#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

# include <iterator>
# include "IteratorTraits.hpp"
# include "pair.hpp"
# include "node.hpp"

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >  class map;

namespace ft {
    template < typename T, typename P, typename R>
	class BidirectionalIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		typedef BidirectionalIterator<T, P, R>	                this_type;
        typedef BidirectionalIterator<T, T*, T&>	            iterator;
		typedef BidirectionalIterator<T, const T*, const T&>	const_iterator;
		typedef size_t		                                    size_type;
		typedef ptrdiff_t	                                    difference_type;
		typedef T			                                    value_type;
		typedef P		                                        pointer;
		typedef R	                                            reference;
		typedef node<T>	                                        node_type;
		typedef std::bidirectional_iterator_tag				    iterator_category;

		node_type*	_ptr;
	public:
		BidirectionalIterator(const node_type* element = nullptr) : _ptr(const_cast<node_type*>(element)) 
        {}

		BidirectionalIterator(const iterator& other) : _ptr(const_cast<node_type*>(other._ptr))
        {}

		this_type&	operator=(const const_iterator& other) 
        {
			this->_ptr = other._ptr;
			return *this;
		}

		~BidirectionalIterator() {}

        BidirectionalIterator& operator ++ (void)
        {
            node<T>::next(_ptr);
            return (*this);
        }

        BidirectionalIterator& operator -- (void)
        {
            node<T>::prev(_ptr);
            return (*this);
        }

        BidirectionalIterator operator ++ (int)
        {
            BidirectionalIterator tmp(*this);
            node<T>::next(_ptr);
            return (tmp);
        }

        BidirectionalIterator operator -- (int)
        {
            BidirectionalIterator tmp(*this);
            node<T>::prev(_ptr);
            return (tmp);
        }
		reference	operator*() 
        {
			return this->_ptr->data;
		}
		const reference	operator*() const 
        {
			return this->_ptr->data;
		}
		pointer		operator->() 
        {
			return (&(this->_ptr->data));
		}
		const pointer		operator->() const
        {
			return (&(this->_ptr->data));
		}

		template<typename _T, typename _P, typename _R>
		friend inline bool operator==(const this_type& lhs, const BidirectionalIterator<_T, _P, _R>& rhs) 
		{ return (lhs._ptr == rhs._ptr); }
		template<typename _T, typename _P, typename _R>
		friend inline bool operator!=(const this_type& lhs, const BidirectionalIterator<_T, _P, _R>& rhs) 
		{ return !(lhs == rhs); }
	};
}

#endif