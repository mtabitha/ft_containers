#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP

namespace ft {

template <typename Iter>
struct iterator_traits
{
    typedef typename Iter::difference_type      difference_type;
    typedef typename Iter::value_type           value_type;
    typedef typename Iter::pointer              pointer;
    typedef typename Iter::reference            reference;
    typedef typename Iter::iterator_category    iterator_category;
};

template <bool B, typename T, typename U>
struct conditional
{
    typedef U type;
};

template <typename T, typename U>
struct conditional<true, T, U>
{
    typedef T type;
};

template <typename T>
struct is_const
{
    static const bool value = false;
};

template <typename T>
struct is_const<const T>
{
    static const bool value = true;  
};



}

#endif