#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

namespace ft {

template <typename Iter>
class ReverseRIterator
{
public:
    typedef             Iter                                                                iterator_type;
    typedef typename    iterator_traits<Iter>::pointer                                      pointer;
    typedef typename    iterator_traits<Iter>::reference                                    reference;
    typedef typename    iterator_traits<Iter>::iterator_category                            iterator_category;
    typedef typename    iterator_traits<Iter>::value_type                                   value_type;
    typedef typename    iterator_traits<Iter>::difference_type                              difference_type;    
private:
    iterator_type    _it;
public:
    ReverseRIterator() : _it(iterator_type())
    {}

    ReverseRIterator(iterator_type it) : _it(it)
    {}

    template <typename _T>
    ReverseRIterator(const ReverseRIterator<_T>& rit) : _it(rit.base())
    {}

    iterator_type  base(void) const
    {
        return (_it);
    }

    reference operator* (void)
    {
        return (*(_it - 1));
    }

    reference operator [] (difference_type i)
    {
        return (_it[- i - 1]);
    }

    pointer operator -> (void) 
    {
        return &(operator*());
    }

    const pointer operator -> (void) const
    {
        return &(operator*());
    }

    ReverseRIterator& operator ++ (void)
    {
        --_it;
        return (*this);
    }
    
    ReverseRIterator& operator -- (void)
    {
        ++_it;
        return (*this);
    }
    
    ReverseRIterator operator ++ (int)
    {
        ReverseRIterator tmp(*this);
        --_it;
        return (tmp);
    }
    
    ReverseRIterator operator -- (int)
    {
        ReverseRIterator tmp(*this);
        ++_it;
        return (tmp);
    }
    ReverseRIterator operator + (difference_type n) const
    {
        return (_it - n);
    }   
    ReverseRIterator operator - (difference_type n) const
    {
        return (_it + n);
    }

    ReverseRIterator& operator += (difference_type i)
    {
        _it -= i;
        return (*this);
    }
    
    ReverseRIterator& operator -= (difference_type i)
    {
        _it += i;
        return (*this);
    }
    

};

template <typename T>
ReverseRIterator<T> operator - (typename ReverseRIterator<T>::difference_type i , const ReverseRIterator<T>& rhs)
{
    return (rhs.base() + i);
}
template <typename T>
ReverseRIterator<T> operator + (typename ReverseRIterator<T>::difference_type i , const ReverseRIterator<T>& rhs)
{
    return (rhs.base() - i);
}

template <typename T, typename _T>
typename ReverseRIterator<T>::difference_type operator - (const ReverseRIterator<T> lhs, const ReverseRIterator<_T>& rhs)
{
    return (rhs.base() - lhs.base());
}

template <typename T, typename _T>
typename ReverseRIterator<T>::difference_type operator + (const ReverseRIterator<T> lhs, const ReverseRIterator<_T>& rhs)
{
    return (rhs.base() + lhs.base());
}

template <typename T, typename _T>
bool operator==(const ReverseRIterator<T>& lhs, const ReverseRIterator<_T>& rhs) 
{
	return (lhs.base() == rhs.base());
}
template <typename T, typename _T>
bool operator<(const ReverseRIterator<T>& lhs, const ReverseRIterator<_T>& rhs) 
{
	return (rhs.base() < lhs.base());
}
template <typename T, typename _T>
bool operator!=(const ReverseRIterator<T>& lhs, const ReverseRIterator<_T>& rhs) 
{
	return !(lhs == rhs);
}
template <typename T, typename _T>
bool operator>(const ReverseRIterator<T>& lhs, const ReverseRIterator<_T>& rhs) 
{
	return (rhs < lhs);
}
template <typename T, typename _T>
bool operator<=(const ReverseRIterator<T>& lhs, const ReverseRIterator<_T>& rhs) 
{
	return !(rhs < lhs);
}
template <typename T, typename _T>
bool operator>=(const ReverseRIterator<T>& lhs, const ReverseRIterator<_T>& rhs) 
{
	return !(lhs < rhs);
}
template <typename Iter>
class ReverseBIterator
{
public:
    typedef             Iter                                                                iterator_type;
    typedef typename    iterator_traits<Iter>::pointer                                      pointer;
    typedef typename    iterator_traits<Iter>::reference                                    reference;
    typedef typename    iterator_traits<Iter>::iterator_category                            iterator_category;
    typedef typename    iterator_traits<Iter>::value_type                                   value_type;
    typedef typename    iterator_traits<Iter>::difference_type                              difference_type;    
private:
    iterator_type    _it;
public:
    ReverseBIterator() : _it(iterator_type())
    {}

    ReverseBIterator(iterator_type it) : _it(it)
    {}

    template <typename _T>
    ReverseBIterator(const ReverseBIterator<_T>& rit) : _it(rit.base())
    {}

    iterator_type  base(void) const
    {
        return (_it);
    }

    reference operator* (void)
    {
        iterator_type it = _it;
        return (*--it );
    }
    const reference operator* (void) const
    {
        iterator_type it = _it;
        return (*--it );
    }

    pointer operator -> (void) 
    {
        return &(operator*());
    }

    const pointer operator -> (void) const
    {
        return &(operator*());
    }

    ReverseBIterator& operator ++ (void)
    {
        --_it;
        return (*this);
    }
    
    ReverseBIterator& operator -- (void)
    {
        ++_it;
        return (*this);
    }
    
    ReverseBIterator operator ++ (int)
    {
        ReverseBIterator tmp(*this);
        --_it;
        return (tmp);
    }
    
    ReverseBIterator operator -- (int)
    {
        ReverseBIterator tmp(*this);
        ++_it;
        return (tmp);
    }

};

template <typename T, typename _T>
bool operator==(const ReverseBIterator<T>& lhs, const ReverseBIterator<_T>& rhs) 
{
	return (lhs.base() == rhs.base());
}
template <typename T, typename _T>
bool operator<(const ReverseBIterator<T>& lhs, const ReverseBIterator<_T>& rhs) 
{
	return (rhs.base() < lhs.base());
}
template <typename T, typename _T>
bool operator!=(const ReverseBIterator<T>& lhs, const ReverseBIterator<_T>& rhs) 
{
	return !(lhs == rhs);
}
template <typename T, typename _T>
bool operator>(const ReverseBIterator<T>& lhs, const ReverseBIterator<_T>& rhs) 
{
	return (rhs < lhs);
}
template <typename T, typename _T>
bool operator<=(const ReverseBIterator<T>& lhs, const ReverseBIterator<_T>& rhs) 
{
	return !(rhs < lhs);
}
template <typename T, typename _T>
bool operator>=(const ReverseBIterator<T>& lhs, const ReverseBIterator<_T>& rhs) 
{
	return !(lhs < rhs);
}

}

#endif