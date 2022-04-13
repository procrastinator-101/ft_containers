#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>

#include "vectorIterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:

			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef ft::vectorIterator<pointer> iterator;
			typedef ft::vectorIterator<const_pointer> const_iterator;

			typedef size_t size_type;

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Iterators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		iterator	begin()
		{
			return iterator(_data);
		}

		const_iterator	begin() const
		{
			return const_iterator(_data);
		}

		iterator	end()
		{
			return iterator(_data + _size);
		}

		const_iterator	end() const
		{
			return const_iterator(_data + _size);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Iterators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// General private functions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			size_type	_getNewCapacity(size_type n)
			{
				size_type	doubleCap;

				doubleCap = _capacity * 2;
				if (doubleCap > max_size() || doubleCap < n)
					return n;
				return doubleCap;
			}

			void	_expandData(size_type newCapacity)//might throw
			{
				T	*tmp;
				size_type	i;

				tmp = _allocator.allocate(newCapacity);
				try
				{
					for (i = 0; i < _size; i++)
						_allocator.construct(tmp + i, _data[i]);
				}
				catch (...)
				{
					for (size_type j = 0; j < i; j++)
						_allocator.destroy(tmp + j);
					_allocator.deallocate(tmp, newCapacity);
					throw ;
				}
				_destroyRange(0, _size);
				_allocator.deallocate(_data, _capacity);
				_data = tmp;
				_capacity = newCapacity;
			}

			void	_destroyRange(size_type start, size_type end)
			{
				for (size_type i = start; i < end; i++)
					_allocator.destroy(_data + i);
			}

			template<class U>
			void	_normalSwap(U& a, U& b)
			{
				U	tmp(a);

				a = b;
				b = tmp;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// General private functions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(1), _allocator(alloc)
			{
				_data = _allocator.allocate(_capacity);//might throw
			}

			vector&	operator=(const vector& rop)
			{
				if (this == &rop)
					return *this;
				if (rop._size > _capacity)
				{
					_destroyRange(0, _size);
					_allocator.deallocate(_data, _capacity);
					_capacity = _getNewCapacity(rop._size);
					_data = _allocator.allocate(_capacity);
				}
				//
				for (size_type i = 0; i < rop._size; i++)
					_allocator.construct(&_data[i], rop[i]);
				_size = rop._size;
			}

			~vector()
			{
				_destroyRange(0, _size);
				_allocator.deallocate(_data, _capacity);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors and constructors End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Capacity
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			size_type	size() const
			{
				return _size;
			}

			size_type	max_size() const
			{
				return _allocator.max_size();
			}

			void resize (size_type n, value_type val = value_type())//might throw
			{
				if (n < _size)
				{
					_destroyRange(n, _size);
					_size = n;
				}
				else if (n > _size)
				{
					if (_capacity <= n)
						_expandData(_getNewCapacity(n));
					for (size_type i = _size; i < n; i++)
						_allocator.construct(&_data[i], val);
					_size = n;
				}
			}

			size_type	capacity() const
			{
				return _capacity;
			}

			bool	empty() const
			{
				return !_size;
			}

			void reserve(size_type n)//might throw
			{
				if (n > max_size())
					throw length_error();
				if (_capacity < n)
					_expandData(_getNewCapacity(n));
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Capacity End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Element access
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			reference	operator[] (size_type n)
			{
				return _data[n];
			}

			const_reference	operator[] (size_type n) const
			{
				return _data[n];
			}

			reference at(size_type n)
			{
				if (n >= _size)
					throw out_of_range();
				return _data[n];
			}

			const_reference	at(size_type n) const
			{
				if (n >= _size)
					throw out_of_range();
				return _data[n];
			}

			reference	front()
			{
				return _data[0];
			}

			const_reference front() const
			{
				return _data[0];
			}

			reference	back()
			{
				return _data[_size - 1];
			}

			const_reference back() const
			{
				return _data[_size - 1];
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Element access End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			void	assign(size_type n, const value_type& val)
			{
				_destroyRange(0, _size);
				if (n > _capacity)
				{
					_allocator.deallocate(_data, _capacity);
					_capacity = _getNewCapacity(n);
					_data = _allocator.allocate(_capacity);
				}
				for (size_type i = 0; i < n; i++)
					_allocator.construct(&_data[i], val);
				_size = n;
			}

			void	push_back(const value_type& val)//might throw
			{
				if (_capacity == _size)
					_expandData(_capacity * 2);
				_allocator.construct(&_data[_size++], val);
			}

			void	pop_back()
			{
				_allocator.destroy(&_data[--_size]);
			}

			void	swap(vector& x)
			{
				if (this == &x)
					return ;
				_normalSwap(_data, x._data);
				_normalSwap(_size, x._size);
				_normalSwap(_capacity, x._capacity);
				_normalSwap(_allocator, x._allocator);
			}

			void	clear()
			{
				_destroyRange(0, _size);
				_size = 0;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Allocator
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			allocator_type	get_allocator() const
			{
				return _allocator;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Allocator End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// relational operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			friend bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (&lhs == &rhs)
					return true;
				if (lhs._size != rhs._size)
					return false;
				for (size_type i = 0; i < lhs._size; i++)
				{
					if (lhs._data[i] != rhs._data[i])
						return false;
				}
				return true;
			}
			
			friend bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(lhs == rhs);
			}

			friend bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				for (size_type i = 0; i < lhs._size && i < rhs._size; i++)
				{
					if (lhs._data[i] > rhs._data[i])
						return false;
					else if (lhs._data[i] < rhs._data[i])
						return true;
				}
				return lhs._size < rhs._size;
			}

			friend bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return rhs < lhs;
			}

			friend bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(rhs < lhs);
			}

			friend bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(lhs < rhs);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// relational operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Exception handlers
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			class out_of_range : public std::out_of_range
			{
				public:
					out_of_range() : std::out_of_range("Vector: out of range") {}
			};

			class length_error : public std::length_error
			{
				public:
					length_error() : std::length_error("Vector: length_error") {}
			};
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Exception handlers End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:

			T	*_data;
			size_type	_size;
			size_type	_capacity;
			allocator_type	_allocator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}


#endif