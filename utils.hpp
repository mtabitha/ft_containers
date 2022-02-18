#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft{



template <bool B, typename T = void>
struct enable_if
{};

template <typename T>
struct enable_if<true, T>
{
    typedef T   type;
};

template <typename InputIter1, typename InputIter2>
bool    equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
{
    for ( ; first1 != last1; ++first1, ++first2)
        if (*first1 != *first2)
            return (false);
   return (first1 == last1) && (first2 == last2);
}

template <typename InputIter1, typename InputIter2>
bool    lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2)
    {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }   
    return (first1 == last1) && (first2 != last2);
}

template <typename T>
void    swap(T& x, T& y)
{
    T   tmp(x);
    x = y;
    y = tmp;
}

}
#endif