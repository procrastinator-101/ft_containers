#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstring>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>//

#include "vectorIterator.hpp"
#include "testUtilities/display.hpp"
#include "../type_traits/type_traits.hpp"


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

			typedef ft::vectorIterator<T> iterator;
			typedef ft::vectorIterator<const T> const_iterator;

			typedef size_t size_type;

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
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

			void	_copyElision(pointer src, size_type dstStart, size_type srcStart, size_type srcEnd)
			{
				if (srcEnd > srcStart)
					::memmove(_data + dstStart, src + srcStart, (srcEnd - srcStart) * sizeof(value_type));
			}

			//might throw
			void	_expandData(size_type newCapacity)
			{
				T	*tmp;

				tmp = _allocator.allocate(newCapacity);
				_normalSwap(_data, tmp);
				_copyElision(tmp, 0, 0, _size);
				_allocator.deallocate(tmp, _capacity);
				_capacity = newCapacity;
			}

			//might throw
			void	_allocate(size_type n)
			{
				_data = _allocator.allocate(n);
				_capacity = n;
			}

			void	_deallocate()
			{
				_allocator.deallocate(_data, _capacity);
				_data = 0;
				_capacity = 0;
			}

			//might throw
			//in case of exception, nothing get constructed
			void	_constructRange(size_type start, size_type end, const value_type& val)
			{
				size_type	i;

				try
				{
					for (i = start; i < end; i++)
						_allocator.construct(_data + i, val);
				}
				catch (...)
				{
					_destroyRange(start, i);
					throw ;
				}
				_size = end;
			}

			//might throw
			//in case of exception, nothing get constructed
			void	_constructRange(size_type start, size_type end, pointer src)
			{
				size_type	i;

				try
				{
					for (i = start; i < end; i++)
						_allocator.construct(_data + i, src[i]);
				}
				catch (...)
				{
					_destroyRange(start, i);
					throw ;
				}
				_size = end;
			}

			void	_destroyRange(size_type start, size_type end)
			{
				for (size_type i = start; i < end; i++)
					_allocator.destroy(_data + i);
				_size = start;
			}

			void	_copyRange(size_type start, size_type end, pointer src)
			{
				size_type	i;

				try
				{
					for (i = start; i < end; i++)
						_data[i] = src[i];
				}
				catch (...)
				{
					_size = i;
					throw ;
				}
				_size = end;
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
			//might throw
			explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc)
			{
				_allocate(1);
			}

			//might throw
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc)
			{
				_allocate(n);
				try
				{
					_constructRange(0, n, val);
				}
				catch (...)
				{
					_deallocate();
					throw ;
				}
			}

			//might throw
			vector(const vector& src) : _size(src._size), _capacity(src._capacity), _allocator(src._allocator)
			{
				_allocate(src._capacity);
				try
				{
					_constructRange(0, src._size, src._data);
				}
				catch (...)
				{
					_deallocate();
					throw ;
				}
			}

			//might throw
			//needs SFINAE protection
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc)
			{
				_allocate(1);
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}

			//might throw
			vector&	operator=(const vector& rop)
			{
				if (this == &rop)
					return *this;
				if (rop._size > _capacity)
				{
					_destroyRange(0, _size);
					_deallocate();
					_allocate(_getNewCapacity(rop._size));
				}
				_copyRange(0, std::min(_size, rop._size), rop._data);
				if (_size < rop._size)
					_constructRange(_size, rop._size, rop._data);
				else
					_destroyRange(rop._size, _size);
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
		/// Iterators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
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
			//might throw
			void	assign(size_type n, const value_type& val)
			{
				_destroyRange(0, _size);
				if (n > _capacity)
				{
					_allocator.deallocate(_data, _capacity);
					_allocate(_getNewCapacity(n));
				}
				_constructRange(0, n, val);
			}

			//might throw
			void	push_back(const value_type& val)
			{
				if (_capacity == _size)
					_expandData(_capacity * 2);
				_allocator.construct(_data + _size, val);
				++_size;
			}

			void	pop_back()
			{
				_allocator.destroy(&_data[--_size]);
			}

			//might throw
			iterator	insert(iterator position, const value_type& val)
			{
				pointer		tmp;
				size_type	start;
				size_type	newCapacity;

				start = position - begin();
				if (_capacity == _size)
				{
					newCapacity = _getNewCapacity(_capacity);
					tmp = _allocator.allocate(newCapacity);
					_normalSwap(tmp, _data);
					_normalSwap(newCapacity, _capacity);
					_copyElision(tmp, 0, 0, start);
					try
					{
						_allocator.construct(_data + start, val);
					}
					catch (...)
					{
						_allocator.deallocate(_data, _capacity);
						_data = tmp;
						_capacity = newCapacity;
						throw ;
					}
					_copyElision(tmp, start + 1, start, _size);
					_allocator.deallocate(tmp, newCapacity);
				}
				else
				{
					_copyElision(_data, start + 1, start, _size);
					try
					{
						_allocator.construct(_data + start, val);
					}
					catch (...)
					{
						_copyElision(_data, start, start + 1, _size + 1);
						throw ;
					}
				}
				++_size;
				return iterator(_data + start);
			}

			//might throw
			void	insert(iterator position, size_type n, const value_type& val)
			{
				pointer		tmp;
				size_type	start;
				size_type	oldSize;
				size_type	newCapacity;

				oldSize = _size;
				start = position - begin();
				if (_capacity < _size + n)
				{
					newCapacity = _getNewCapacity(_size + n);
					tmp = _allocator.allocate(newCapacity);
					_normalSwap(tmp, _data);
					_normalSwap(newCapacity, _capacity);
					_copyElision(tmp, 0, 0, start);
					try
					{
						_constructRange(start, start + n, val);
					}
					catch (...)
					{
						_allocator.deallocate(_data, _capacity);
						_data = tmp;
						_capacity = newCapacity;
						throw ;
					}
					_copyElision(tmp, start + n, start, oldSize);
					_allocator.deallocate(tmp, newCapacity);
				}
				else
				{
					_copyElision(_data, start + n, start, oldSize);
					try
					{
						_constructRange(start, start + n, val);
					}
					catch (...)
					{
						_copyElision(_data, start, start + n, oldSize + n);
						throw ;
					}
				}
				_size = oldSize + n;
			}

			//might throw
			//needs SFINAE protection agaist integral types
			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last)
			{
				vector		tmp(first, last);
				pointer		newData;
				size_type	start;
				size_type	newCapacity;

				newData = _data;
				start = position - begin();
				newCapacity = tmp._size + _size;
				if (_capacity < newCapacity)
				{
					newCapacity = _getNewCapacity(newCapacity);
					newData = _allocator.allocate(newCapacity);
					_capacity = newCapacity;
					_normalSwap(_data, newData);
					_copyElision(newData, 0, 0, start);
				}
				_copyElision(newData, start + tmp._size, start, _size);
				_copyElision(tmp._data, start, 0, tmp._size);
				_size += tmp._size;
				tmp._size = 0;
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

			pointer	_data;
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