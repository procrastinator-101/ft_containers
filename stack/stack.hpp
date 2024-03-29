#ifndef STACK_HPP
# define STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef Container container_type;
			typedef typename container_type::value_type value_type;
			typedef typename container_type::size_type size_type;
		protected:
			container_type	_container;	
		
		public:
			explicit stack(const container_type& ctnr = container_type()) : _container(ctnr)
			{
			}

			bool	empty() const
			{
				return _container.empty();
			}

			size_type	size() const
			{
				return _container.size();
			}

			value_type	&top()
			{
				return _container.back();
			}

			const value_type	&top() const
			{
				return _container.back();
			}

			void	push(const value_type& val)
			{
				_container.push_back(val);
			}

			void	pop()
			{
				_container.pop_back();
			}

			template <class U, class Cntr>
			friend bool	operator==(const stack<U,Cntr>& lhs, const stack<U,Cntr>& rhs)
			{
				return lhs._container == rhs._container;	
			}
			
			template <class U, class Cntr>
			friend bool	operator!=(const stack<U,Cntr>& lhs, const stack<U,Cntr>& rhs)
			{
				return lhs._container != rhs._container;	
			}

			template <class U, class Cntr>
			friend bool	operator<(const stack<U,Cntr>& lhs, const stack<U,Cntr>& rhs)
			{
				return lhs._container < rhs._container;
			}

			template <class U, class Cntr>
			friend bool	operator<=(const stack<U,Cntr>& lhs, const stack<U,Cntr>& rhs)
			{
				return lhs._container <= rhs._container;
			}

			template <class U, class Cntr>
			friend bool	operator>(const stack<U,Cntr>& lhs, const stack<U,Cntr>& rhs)
			{
				return lhs._container > rhs._container;
			}

			template <class U, class Cntr>
			friend bool	operator>=(const stack<U,Cntr>& lhs, const stack<U,Cntr>& rhs)
			{
				return lhs._container >= rhs._container;
			}
	};
}

#endif