#include "type_traits.hpp"

template <unsigned n>
struct factorial : ft::integral_constant<int,n * factorial<n-1>::value>
{
};

template <>
struct factorial<0> : ft::integral_constant<int,1>{};

int	getFact()
{
	return factorial<10>::value;
}