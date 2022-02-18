#ifndef RANDOMITERATOR_HPP
# define RANDOMITERATOR_HPP

# include <iterator>
# include "IteratorTraits.hpp"

template<typename T, typename Alloc> class vector;

namespace ft {
template <typename T, bool IsConst>
class RandomIterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    typedef size_t                              size_type;
	typedef ptrdiff_t                           difference_type;
	typedef T                                   value_type;
	typedef T*                                  pointer;
	typedef T&                                  reference;
	typedef const T*                            const_pointer;
	typedef const T&                            const_reference;
	typedef std::random_access_iterator_tag     iterator_category;
private:
    typename conditional<IsConst, const T*, T*>::type _ptr;
public:
    RandomIterator(pointer ptr = nullptr) : _ptr(ptr)
    {}

    template <typename _T>
    RandomIterator(const RandomIterator<_T, is_const<_T>::value>& it) : _ptr(&*it)
    {}

    ~RandomIterator() 
    {}

    RandomIterator& operator = (const RandomIterator& it)
    {
        if (_ptr != it._ptr)
            _ptr = it._ptr;
        return (*this);
    }
    
    RandomIterator& operator = (const pointer ptr)
    {
        _ptr = ptr;
        return (*this);
    }

    typename conditional<IsConst, const_reference, reference>::type operator [] (const difference_type& i)
    {
        return (_ptr[i]);
    }
    const value_type& operator [] (const difference_type& i) const
    {
        return (_ptr[i]);
    }

    typename conditional<IsConst, const_reference, reference>::type operator * (void)
    {
        return (*_ptr);
    }

    const value_type& operator * (void) const
    {
        return (*_ptr);
    }

    typename conditional<IsConst, const_pointer, pointer>::type operator-> (void)
    {
        return (_ptr);
    }

    RandomIterator& operator ++ (void)
    {
        ++_ptr;
        return (*this);
    }
    
    RandomIterator& operator -- (void)
    {
        --_ptr;
        return (*this);
    }
    
    RandomIterator operator ++ (int)
    {
        RandomIterator tmp(*this);
        ++_ptr;
        return (tmp);
    }
    
    RandomIterator operator -- (int)
    {
        RandomIterator tmp(*this);
        --_ptr;
        return (tmp);
    }

    RandomIterator operator + (difference_type i) const
    {
        return (_ptr + i);
    }
    
    RandomIterator operator - (difference_type i) const
    {
        return (_ptr - i);
    }

    RandomIterator& operator += (difference_type i)
    {
        _ptr += i;
        return (*this);
    }
    
    RandomIterator& operator -= (difference_type i)
    {
        _ptr -= i;
        return (*this);
    }

    template <typename C, typename Alloc>
    friend class vector;

    template <typename C, typename _C>
    friend bool    operator == (const RandomIterator<C, is_const<C>::value>& first, const RandomIterator<_C, is_const<_C>::value>& second);

    template <typename C, typename _C>
    friend bool    operator < (const RandomIterator<C, is_const<C>::value>& first, const RandomIterator<_C, is_const<_C>::value>& second);

    template <typename C, typename _C>
    friend typename RandomIterator<C, is_const<C>::value>::difference_type operator - (const RandomIterator<C, is_const<C>::value>& it1, const RandomIterator<_C, is_const<_C>::value>& it2);
    
    template <typename C, typename _C>
    friend typename RandomIterator<C, is_const<C>::value>::difference_type operator + (const RandomIterator<C, is_const<C>::value>& it1, const RandomIterator<_C, is_const<_C>::value>& it2);
};

template <typename T>
RandomIterator<T, is_const<T>::value> operator + (typename RandomIterator<T, is_const<T>::value>::difference_type i, const RandomIterator<T, is_const<T>::value>& it)
{
    return (it + i);
}

template <typename T>
RandomIterator<T, is_const<T>::value> operator - (typename RandomIterator<T, is_const<T>::value>::difference_type i, const RandomIterator<T, is_const<T>::value>& it)
{
    return (it - i);
}

template <typename T, typename _T>
typename RandomIterator<T, is_const<T>::value>::difference_type operator - (const RandomIterator<T, is_const<T>::value>& it1, const RandomIterator<_T, is_const<_T>::value>& it2)
{
    return (it1._ptr - it2._ptr);
}

template <typename T, typename _T>
typename RandomIterator<T, is_const<T>::value>::difference_type operator + (const RandomIterator<T, is_const<T>::value>& it1, const RandomIterator<_T, is_const<_T>::value>& it2)
{
    return (it1._ptr + it2._ptr);
}

template <typename T, typename _T>
bool    operator == (const RandomIterator<T, is_const<T>::value>& first, const RandomIterator<_T, is_const<_T>::value>& second)
{
    return (first._ptr == second._ptr);
}

template <typename T, typename _T>
bool    operator != (const RandomIterator<T, is_const<T>::value>& first, const RandomIterator<_T, is_const<_T>::value>& second)
{
    return !(first == second);
}

template <typename T, typename _T>
bool    operator < (const RandomIterator<T, is_const<T>::value>& first, const RandomIterator<_T, is_const<_T>::value>& second)
{
    return (first._ptr < second._ptr);
}

template <typename T, typename _T>
bool    operator > (const RandomIterator<T, is_const<T>::value>& first, const RandomIterator<_T, is_const<_T>::value>& second)
{
    return (second < first);
}

template <typename T, typename _T>
bool    operator <= (const RandomIterator<T, is_const<T>::value>& first, const RandomIterator<_T, is_const<_T>::value>& second)
{
    return !(first > second);
}

template <typename T, typename _T>
bool    operator >= (const RandomIterator<T, is_const<T>::value>& first, const RandomIterator<_T, is_const<_T>::value>& second)
{
    return !(second > first);
}

}

#endif