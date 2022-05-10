#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstddef>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>//

// #include "../algorithm/equal.hpp"
// #include "../algorithm/lexicographical_compare.hpp"

#include "vectorIterator.hpp"
#include "testUtilities/display.hpp"//
#include "../type_traits/type_traits.hpp"

# include "../iterator/reverse_iterator.hpp"


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

			typedef vectorIterator<T> iterator;
			typedef vectorIterator<const T> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// General private functions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			template<class U>
			void	_normalSwap(U& a, U& b)
			{
				U	tmp(a);

				a = b;
				b = tmp;
			}

			size_type	_getNewCapacity(size_type n)
			{
				size_type	doubleCap;

				doubleCap = _capacity * 2;
				if (doubleCap > max_size() || doubleCap < n)
					return n;
				return std::max<size_type>(doubleCap, 1);
			}

			//might throw
			void	_allocate(size_type n)
			{
				_data = _allocator.allocate(n);
				_capacity = n;
			}

			void	_deallocate()
			{
				if (!_data)
					return;
				_allocator.deallocate(_data, _capacity);
				_data = 0;
				_capacity = 0;
			}

			void	_deallocateDry(pointer ptr, size_type capacity)
			{
				if (ptr)
					_allocator.deallocate(ptr, capacity);
			}

			//might throw
			void	_expandData(size_type newCapacity)
			{
				pointer	tmp;

				tmp = _allocator.allocate(newCapacity);
				try
				{
					_nconstructDry(tmp, 0, _data, _size);
				}
				catch (...)
				{
					_allocator.deallocate(tmp, newCapacity);
					throw ;
				}
				_normalSwap(_data, tmp);
				_ndestroyDry(tmp, _size);
				_deallocateDry(tmp, _capacity);
				_capacity = newCapacity;
			}

			//might throw
			//in case of exception, nothing get constructed
			void	_nconstructDry(pointer dst, size_type dstStart, pointer src, size_type n)
			{
				size_type	i;

				try
				{
					for (i = 0; i < n; i++)
						_allocator.construct(dst + dstStart + i, src[i]);
				}
				catch (...)
				{
					_ndestroyDry(dst + dstStart, i);
					throw ;
				}
			}

			//might throw
			//in case of exception, nothing get constructed
			void	_nconstructDry(pointer dst, size_type dstStart, const value_type& val, size_type n)
			{
				size_type	i;

				try
				{
					for (i = 0; i < n; i++)
						_allocator.construct(dst + dstStart + i, val);
				}
				catch (...)
				{
					_ndestroyDry(dst + dstStart, i);
					throw ;
				}
			}

			void	_ndestroyDry(pointer ptr, size_type n)
			{
				if (!n)
					return ;
				for (size_type i = n - 1; i >= 0; i--)
				{
					_allocator.destroy(ptr + i);
					if (!i)
						break ;
				}
			}

			//might throw
			//in case of exception, nothing get constructed
			void	_nconstruct(size_type start, pointer src, size_type n)
			{
				size_type	i;

				try
				{
					for (i = 0; i < n; i++)
						_allocator.construct(_data + start + i, src[i]);
				}
				catch (...)
				{
					_destroyRange(start, start + i);
					throw ;
				}
				_size += n;
			}

			//might throw
			//in case of exception, nothing get constructed
			void	_nconstruct(size_type start, const value_type& val, size_type n)
			{
				size_type	i;

				try
				{
					for (i = 0; i < n; i++)
						_allocator.construct(_data + start + i, val);
				}
				catch (...)
				{
					_destroyRange(start, start + i);
					throw ;
				}
				_size += n;
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
						_allocator.construct(_data + i, src[i - start]);
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
				if (!end)
					return ;
				for (size_type i = end - 1; i >= start; i--)
				{
					_allocator.destroy(_data + i);
					_size = i;
					if (!i)
						break ;
				}
			}

			//might throw : basic guarantee
			void	_copyRange(size_type start, size_type end, pointer src)
			{
				for (size_type i = start; i < end; i++)
					_data[i] = src[i - start];
			}

			//might throw : basic guarantee
			void	_ncopy(size_type start, const value_type& val, size_type n)
			{
				for (size_type i = 0; i < n; i++)
					_data[start + i] = val;
			}

			//might throw : basic guarantee
			void	_copyFroward(pointer ptr, size_type start, size_type end, size_type step)
			{
				if (!end)
					return ;
				for (size_type i = end - 1; i >= start; i--)
				{
					ptr[i + step] = ptr[i];
					if (!i)
						break ;
				}
			}

			//might throw : basic guarantee
			void	_copyBackward(pointer ptr, size_type start, size_type end, size_type step)
			{
				for (size_type i = start; i < end; i++)
					ptr[i - step] = ptr[i];
			}
			
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// General private functions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			explicit vector(const allocator_type& alloc = allocator_type()) : _data(0), _size(0), _capacity(0), _allocator(alloc)
			{
			}

			//might throw : strong guarantee
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

			//might throw : strong guarantee
			template <class InputIterator>
			vector(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type()) : _data(0), _size(0), _capacity(0), _allocator(alloc)
			{
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}

			//might throw : strong guarantee
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

			~vector()
			{
				_destroyRange(0, _size);
				_deallocate();
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
					_constructRange(_size, rop._size, rop._data + _size);
				else
					_destroyRange(rop._size, _size);
				return *this;
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

			reverse_iterator	rbegin()
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator	rbegin() const
			{
				return const_reverse_iterator(end());
			}

			reverse_iterator	rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator	rend() const
			{
				return const_reverse_iterator(begin());
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

			//might throw
			void resize (size_type n, value_type val = value_type())
			{
				if (n < _size)
					_destroyRange(n, _size);
				else if (n > _size)
				{
					if (_capacity <= n)
						_expandData(_getNewCapacity(n));
					_constructRange(_size, n, val);
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
					_expandData(_getNewCapacity(_capacity * 2));
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
				newCapacity = _size + 1;
				if (_capacity < newCapacity)
				{
					newCapacity = _getNewCapacity(newCapacity);
					tmp = _allocator.allocate(newCapacity);
					//copy first half
					try
					{
						_nconstructDry(tmp, 0, _data, start);
					}
					catch (...)
					{
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					//insert the element
					try
					{
						_allocator.construct(tmp + start, val);
					}
					catch (...)
					{
						_ndestroyDry(tmp, start);
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					//copy the last half
					try
					{
						_nconstructDry(tmp, start + 1, _data + start, _size - start);
					}
					catch (...)
					{
						_ndestroyDry(tmp, start + 1);
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					_normalSwap(_data, tmp);
					_normalSwap(_capacity, newCapacity);
					_ndestroyDry(tmp, _size);
					_deallocateDry(tmp, newCapacity);
					++_size;
				}
				else
				{
					//if the position is at the end or the vector is empty
					if (start == _size || _size == 0)
					{
						_allocator.construct(_data + start, val);
						_size++;
					}
					else
					{
						_allocator.construct(_data + _size, _data[_size - 1]);
						++_size;
						_copyFroward(_data, start, _size - 2, 1);
						_data[start] = val;
					}
				}
				return iterator(_data + start);
			}

			//might throw
			void	insert(iterator position, size_type n, const value_type& val)
			{
				pointer		tmp;
				size_type	start;
				size_type	oldSize;
				size_type	newCapacity;

				if (!n)
					return ;
				start = position - begin();
				newCapacity = _size + n;
				if (_capacity < newCapacity)
				{
					newCapacity = _getNewCapacity(newCapacity);
					tmp = _allocator.allocate(newCapacity);
					//copy first half
					try
					{
						_nconstructDry(tmp, 0, _data, start);
					}
					catch (...)
					{
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					//insert the elements
					try
					{
						_nconstructDry(tmp, start, val, n);
					}
					catch (...)
					{
						_ndestroyDry(tmp, start);
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					//copy the last half
					try
					{
						_nconstructDry(tmp, start + n, _data + start, _size - start);
					}
					catch (...)
					{
						_ndestroyDry(tmp, start + n);
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					_normalSwap(_data, tmp);
					_normalSwap(_capacity, newCapacity);
					_ndestroyDry(tmp, _size);
					_deallocateDry(tmp, newCapacity);
					_size += n;
				}
				else
				{
					//if the position is at the end or the vector is empty
					if (start == _size || _size == 0)
						_constructRange(start, _size + n, val);
					else
					{
						oldSize = _size;
						if (start + n < _size)
						{
							_constructRange(oldSize, oldSize + n, _data + oldSize - n);
							std::cout << "cons" << std::endl;
							_copyFroward(_data, start, oldSize - n, n);
							std::cout << "forward" << std::endl;
							_ncopy(start, val, n);
							std::cout << "copy" << std::endl;
						}
						else
						{
							_constructRange(oldSize, start + n, val);
							std::cout << "-cons" << std::endl;
							_constructRange(start + n, oldSize + n, _data + start);
							std::cout << "-cons2" << std::endl;
							_ncopy(start, val, oldSize - start);
							std::cout << "copy" << std::endl;
						}
					}
				}
			}

			//might throw
			template <class InputIterator>
			void	insert(iterator position, InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
			{
				vector		src(first, last);
				pointer		tmp;
				size_type	start;
				size_type	newCapacity;

				if (!src._size)
					return ;
				tmp = _data;
				start = position - begin();
				newCapacity = src._size + _size;
				if (_capacity < newCapacity)
				{
					newCapacity = _getNewCapacity(newCapacity);
					tmp = _allocator.allocate(newCapacity);
					//copy first half
					try
					{
						_nconstructDry(tmp, 0, _data, start);
					}
					catch (...)
					{
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					//insert the elements
					try
					{
						_nconstructDry(tmp, start, src._data, src._size);
					}
					catch (...)
					{
						_ndestroyDry(tmp, start);
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					//copy the last half
					try
					{
						_nconstructDry(tmp, start + src._size, _data + start, _size - start);
					}
					catch (...)
					{
						_ndestroyDry(tmp, start + src._size);
						_allocator.deallocate(tmp, newCapacity);
						throw ;
					}
					_normalSwap(_data, tmp);
					_normalSwap(_capacity, newCapacity);
					_ndestroyDry(tmp, _size);
					_deallocateDry(tmp, newCapacity);
					_size += src._size;
				}
				else
				{
					//if the position is at the end or the vector is empty
					if (start == _size || _size == 0)
						_constructRange(start, _size + src._size, src._data);
					else
					{
						if (start + src._size < _size)
						{
							_nconstruct(_size, _data + start + src._size, src._size);
							_copyFroward(_data, start, start + src._size, src._size);
						}
						else
							_nconstruct(start + src._size, _data + start, src._size);
						_copyRange(start, start + src._size, src._data);
					}
				}
			}

			iterator	erase(iterator position)
			{
				size_type	target;

				target = position - begin();
				_copyBackward(_data, target + 1, _size, 1);
				pop_back();
				return iterator(_data + target);
			}

			iterator	erase(iterator first, iterator last)
			{
				size_type	n;
				size_type	end;
				size_type	start;

				start = first - begin();
				end = last - begin();
				n = end - start;
				_copyBackward(_data, start + n, _size, n);
				_destroyRange(_size - n, _size);
				return iterator(_data + start);
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