#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft{

template <typename Key, typename T>
struct pair
{
    typedef Key     first_type;
    typedef T       second_type;

    Key     first;
    T       second;

    pair() : first(0)
    {}

    pair( const Key& x, const T& y) : first(x), second(y)
    {}

    template< class U1, class U2 >
    pair( const pair<U1, U2>& p ) : first(p.first), second(p.second)
    {}

    template<class U, class V>
	pair(const std::pair<U, V>& p) : first(p.first), second(p.second)
    {}

    pair& operator = (const pair &x)
    {
        if (this != &x)
        {
            first = x.first;
            second = x.second;
        }
        return (*this);
    }
};

template< class _Key, class _T >
pair<_Key,_T> make_pair( _Key t, _T u )
{
    return (pair<_Key,_T>(t, u));
}

template< class _Key, class _T >
bool operator==( const pair<_Key,_T>& lhs, const pair<_Key,_T>& rhs )
{
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template< class _Key, class _T >
bool operator!=( const pair<_Key,_T>& lhs, const pair<_Key,_T>& rhs )
{
    return !(lhs == rhs);
}

template< class _Key, class _T >
bool operator<( const pair<_Key,_T>& lhs, const pair<_Key,_T>& rhs )
{
    return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));
}

template< class _Key, class _T >
bool operator<=( const pair<_Key,_T>& lhs, const pair<_Key,_T>& rhs )
{
    return !(lhs > rhs);
}

template< class _Key, class _T >
bool operator>( const pair<_Key,_T>& lhs, const pair<_Key,_T>& rhs )
{
    return (rhs.first < lhs.first);
}

template< class _Key, class _T >
bool operator>=( const pair<_Key,_T>& lhs, const pair<_Key,_T>& rhs )
{
    return !(lhs < rhs);
}

}

#endif