#ifndef MAP_HPP
# define MAP_HPP

#include <functional>

#include "../utility/pair.hpp"
#include "../utility/make_pair.hpp"
#include "../type_traits/type_traits.hpp"


namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> >>
	class map
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair<const key_type,mapped_type> value_type;

			typedef Compare key_compare;
			//value_compare

			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			//iterator
			//const_iterator
			//reverse_iterator
			//const_reverse_iterator

			//typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		explicit	map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors and constructors End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};
}

#endif