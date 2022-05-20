#ifndef MAP_HPP
# define MAP_HPP

#include <functional>

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"

#include "../utility/pair.hpp"
#include "../utility/make_pair.hpp"
#include "../type_traits/type_traits.hpp"

#include "avl.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> >>
	class map
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions first half
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair<const key_type,mapped_type> value_type;

			typedef Compare key_compare;

			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef size_t size_type;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions first half End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// value_compare definition
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected:
					key_compare	_comparator;

					value_compare() : _comparator()
					{
					}

					value_compare(key_compare comp) : _comparator(comp)
					{
					}

					value_compare(const value_compare& src) : _comparator(src._comparator)
					{
					}

					value_compare	&operator=(const value_compare& rop)
					{
						if (this == &rop)
							return *this;
						_comparator = rop._comparator;
						return *this;
					}

				public:
					bool	operator() (const value_type& x, const value_type& y) const
					{
						return _comparator(x.first, y.first);
					}
			};
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// value_compare definition End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions second half
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			typedef Avl<value_type, value_compare, allocator_type> Bst;

		public:
			typedef typename Bst::iterator iterator;
			typedef typename Bst::const_iterator const_iterator;
			typedef typename Bst::reverse_iterator reverse_iterator;
			typedef typename Bst::const_reverse_iterator const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions second half End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Attributes
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		Bst _data;
		key_compare	_key_comparator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Attributes End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _data(value_compare(comp), alloc), _key_comparator(comp)
			{
			}

			//might throw : strong guarantee
			template <class InputIterator>
			map(InputIterator first, typename ft::enable_if<is_iterator<InputIterator>::value, InputIterator>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _data(value_compare(comp), alloc), _key_comparator(comp)
			{
				while (first != last)
				{
					_data.insert(*first);
					++first;
				}
			}

			//might throw : strong guarantee
			map(const map& src) : _data(src._data), _key_comparator(src._key_comparator)
			{
			}

			~map()
			{
			}

			//might throw : basic guarantee
			map	&operator=(const map& rop)
			{
				if (this == &rop)
					return *this;
				_data = rop._data;
				_key_comparator = rop._key_comparator;
				return *this;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors and constructors End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Iterators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			iterator begin()
			{
				return _data.begin();
			}

			const_iterator begin() const
			{
				return _data.begin();
			}

			iterator end()
			{
				return _data.end();
			}

			const_iterator end() const
			{
				return _data.end();
			}

			reverse_iterator rbegin()
			{
				return _data.rbegin();
			}

			const_reverse_iterator rbegin() const
			{
				return _data.rbegin();
			}

			reverse_iterator rend()
			{
				return _data.rend();
			}

			const_reverse_iterator rend() const
			{
				return _data.rend();
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Iterators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Capacity
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			bool	empty() const
			{
				return !_data.getCount();
			}

			size_type	size() const
			{
				return _data.getCount();
			}

			size_type	max_size() const
			{
				return _data.max_size();
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Capacity
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Element access
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			mapped_type	&operator[](const key_type& k)
			{
				return _data[make_pair(k, mapped_type())];
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Element access End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			pair<iterator,bool>	insert(const value_type& val)
			{
				return _data.insert(val);
			}

			iterator	insert(iterator position, const value_type& val)
			{
				pair<iterator, bool>	ret =  _data.insert(val);

				(void)position;
				return ret.first;
			}

			template <class InputIterator>
			void	insert(InputIterator first, typename ft::enable_if<is_iterator<InputIterator>::value, InputIterator>::type last)
			{
				while (first != last)
				{
					_data.insert(first);
					++first;
				}
			}

			void	erase(iterator position)
			{
				_data.erase(position);
			}

			size_type	erase(const key_type& k)
			{
				return _data.erase(make_pair(k, mapped_type()));
			}

			void	erase(iterator first, iterator last)
			{
				_data.erase(first, last);
			}

			void	clear()
			{
				_data.clear();
			}

			void	swap(map& x)
			{
				_data.swap(x._data);
				std::swap(_key_comparator, x._key_comparator);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Observers
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			key_compare	key_comp() const
			{
				return _key_comparator;
			}

			value_compare	value_comp() const
			{
				return _data.get_value_comparator();
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Observers End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Operations
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			//might throw strong guarantee
			iterator	find(const key_type& k)
			{
				return _data.find(make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			const_iterator	find(const key_type& k) const
			{
				return _data.find(make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			size_type	count(const key_type& k) const
			{
				const_iterator	tmp = _data.find(make_pair(k, mapped_type()));

				return tmp != end();
			}

			//might throw strong guarantee
			iterator	lower_bound(const key_type& k)
			{
				return _data.lower_bound(make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			const_iterator	lower_bound(const key_type& k) const
			{
				return _data.lower_bound(make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			iterator	upper_bound(const key_type& k)
			{
				return _data.upper_bound(make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			const_iterator	upper_bound(const key_type& k) const
			{
				return _data.upper_bound(make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			pair<iterator,iterator>	equal_range(const key_type& k)
			{
				iterator	ret = lower_bound(k);

				if (ret == end())
					return make_pair(ret, ret);
				//k is less than ret's key
				if (_key_comparator(k, ret->first))
					return make_pair(ret, ret);
				return make_pair(ret, ++ret);
			}

			//might throw strong guarantee
			pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
			{
				const_iterator	ret = lower_bound(k);

				if (ret == end())
					return make_pair(ret, ret);
				//k is less than ret's key
				if (_key_comparator(k, ret->first))
					return make_pair(ret, ret);
				return make_pair(ret, ++ret);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Operations End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Allocator
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			allocator_type get_allocator() const
			{
				return _data.get_allocator();
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Allocator
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Relational operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template< class Key, class T, class Compare, class Alloc >
	bool	operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Relational operators End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Swap
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template< class Key, class T, class Compare, class Alloc >
	void	swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Swap End
	/////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif