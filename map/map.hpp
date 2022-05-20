#ifndef MAP_HPP
# define MAP_HPP

#include <functional>

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"

#include "../utility/pair.hpp"
#include "../utility/make_pair.hpp"
#include "../type_traits/type_traits.hpp"

#include "node.hpp"

#include "treeIterator.hpp"
#include "../iterator/reverse_iterator.hpp"


namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// forward declarations
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			class Avl;
		public:
			class value_compare;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// forward declarations End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
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
		
		private:
			typedef Avl Bst;


		public:
			typedef typename Bst::iterator iterator;
			typedef typename Bst::const_iterator const_iterator;
			typedef typename Bst::reverse_iterator reverse_iterator;
			typedef typename Bst::const_reverse_iterator const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
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
		private:
			class Avl
			{
				//===========================================================================================
				/// type definitions
				//===========================================================================================
				private:
					typedef ft::Node<value_type> Node;
					typedef typename Node::Traits Traits;
					typedef typename Node::node_pointer node_pointer;
					typedef typename Node::const_node_pointer const_node_pointer;
					typedef typename Node::node_reference node_reference;
					typedef typename Node::const_node_reference const_node_reference;

				public:
					typedef Alloc allocator_type;

				private:
					typedef typename allocator_type::template rebind<Node>::other node_allocator_type;
					typedef typename allocator_type::template rebind<Traits>::other traits_allocator_type;

				public:
					typedef typename Node::value_type value_type;

					typedef typename Node::pointer pointer;
					typedef typename Node::const_pointer const_pointer;
					typedef typename Node::reference reference;
					typedef typename Node::const_reference const_reference;

					typedef typename Node::size_type size_type;

					typedef treeIterator<value_type, ft::Node> iterator;
					typedef ft::reverse_iterator<iterator> reverse_iterator;
					typedef treeIterator<const value_type, ft::Node> const_iterator;
					typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
				//===========================================================================================
				/// type definitions End
				//===========================================================================================
				public:
					void	show() const
					{
						printTree(std::cout, _root, 0, 0);
					}

					node_pointer	getRoot() const
					{
						return _root;
					}
				//===========================================================================================
				/// destructors, constructors, and assignment operators
				//===========================================================================================
				public:

					~Avl()
					{
						clear();
					}

					Avl(const value_compare& compare = value_compare(), const allocator_type& alloc = allocator_type()) : _count(0), _root(0), _last(0), _begin(0), _value_comparator(compare), _allocator(alloc), _nodeAllocator(alloc), traits_allocator(alloc)
					{
					}

					Avl(const Avl& src) : _count(0), _root(0), _last(0), _begin(0), _value_comparator(src._value_comparator), _allocator(src._allocator), _nodeAllocator(src._nodeAllocator), traits_allocator(src.traits_allocator)
					{
						_clone(src);
					}

					Avl	&operator=(const Avl& rop)
					{
						if (this == &rop)
							return *this;
						clear();
						_value_comparator = rop._value_comparator;
						_clone(rop);
						return *this;
					}
				//===========================================================================================
				/// destructors, constructors, and assignment operators End
				//===========================================================================================

				//===========================================================================================
				/// Iterators
				//===========================================================================================
				public:
					iterator	end()
					{
						return iterator(0, &_last, true);
					}
					iterator	begin()
					{
						return iterator(_begin, &_last, false);
					}

					reverse_iterator	rend()
					{
						return reverse_iterator(begin());
					}
					reverse_iterator	rbegin()
					{
						return reverse_iterator(end());
					}

					const_iterator	end() const
					{
						return iterator(0, const_cast<node_pointer *>(&_last), true);
					}
					const_iterator	begin() const
					{
						return iterator(_begin, const_cast<node_pointer *>(&_last), false);
					}

					const_reverse_iterator	rend() const
					{
						return const_reverse_iterator(begin());
					}
					const_reverse_iterator	rbegin() const
					{
						return const_reverse_iterator(end());
					}
				//===========================================================================================
				/// Iterators End
				//===========================================================================================


				//===========================================================================================
				/// Modifiers
				//===========================================================================================
				public:
					void		clear()
					{
						_destorySubtree(_root);
						_count = 0;
						_root = 0;
						_last = 0;
						_begin = 0;
					}

					void		swap(Avl& x)
					{
						_normalSwap(_count, x._count);
						_normalSwap(_root, x._root);
						_normalSwap(_last, x._last);
						_normalSwap(_begin, x._begin);
						_normalSwap(_value_comparator, x._value_comparator);
						_normalSwap(_allocator, x._allocator);
						_normalSwap(_nodeAllocator, x._nodeAllocator);
						_normalSwap(traits_allocator, x.traits_allocator);
					}

					size_type	erase(const value_type& val)
					{
						size_type		ret;
						node_pointer	current;

						ret = 0;
						current = _root;
						while (current)
						{
							//if val is less than the current node' value : erase on the left
							if (_value_comparator(val, current->value))
								current = current->traits.left;
							//if val is grater than the current node' value : erase on the right
							else if (_value_comparator(current->value, val))
								current = current->traits.right;
							//if val is equal to the current node' value : erase the current node
							else
							{
								_delete(current);
								ret = 1;
								break ;
							}
						}
						return ret;
					}

					void		erase(iterator position)
					{
						_delete(position._ptr);
					}

					void		erase(iterator first, iterator last)
					{
						node_pointer	head;
						node_pointer	next;

						head = first._ptr;
						while (head != last._ptr)
						{
							next = head->getInOrderSuccessor();
							_delete(head);
							head = next;
						}
					}

					//might throw : strong guarantee
					ft::pair<iterator,bool>	insert(const value_type& val)
					{
						node_pointer	node;
						node_pointer	current;

						if (!_root)
							node = _putInPosition(val);
						else
						{
							current = _root;
							while (1)
							{
								//if val is less than the current node' value : insert on the left
								if (_value_comparator(val, current->value))
								{
									if (current->traits.left)
										current = current->traits.left;
									else
									{
										node = _putInPosition(current, val, true);
										break ;
									}
								}
								//if val is greater than the current node' value : insert on the right
								else if (_value_comparator(current->value, val))
								{
									if (current->traits.right)
										current = current->traits.right;
									else
									{
										node = _putInPosition(current, val, false);
										break ;
									}
								}
								//if val is equal to the current node' value : just return the current node
								else
									return ft::make_pair(iterator(current, &_last, false), false);
							}
							_retroBalance(current);
						}
						return ft::make_pair(iterator(node, &_last, false), true);
					}
				//===========================================================================================
				/// Modifiers End
				//===========================================================================================


				//===========================================================================================
				/// Operations
				//===========================================================================================
				public:
					iterator	find(const value_type& val)
					{
						node_pointer	node;

						node = _root;
						while (node)
						{
							if (_value_comparator(node->value, val))
								node = node->traits.right;
							else if (_value_comparator(val, node->value))
								node = node->traits.left;
							else
								return iterator(node, &_last, false);
						}
						return end();
					}

					iterator	lower_bound(const value_type& val)
					{
						node_pointer	ret;
						node_pointer	node;

						ret = 0;
						node = _root;
						while (node)
						{
							if (_value_comparator(node->value, val))
								node = node->traits.right;
							else if (_value_comparator(val, node->value))
							{
								ret = node;
								node = node->traits.left;
							}
							else
								return iterator(node, &_last, false);
						}
						if (ret)
							return iterator(ret, &_last, false);
						return end();
					}

					iterator	upper_bound(const value_type& val)
					{
						node_pointer	ret;
						node_pointer	node;

						ret = 0;
						node = _root;
						while (node)
						{
							if (_value_comparator(node->value, val))
								node = node->traits.right;
							else if (_value_comparator(val, node->value))
							{
								ret = node;
								node = node->traits.left;
							}
							else
							{
								ret = node->getInOrderSuccessor();
								break ;
							}
						}
						if (ret)
							return iterator(ret, &_last, false);
						return end();
					}

					const_iterator	find(const value_type& val) const
					{
						node_pointer	node;

						node = _root;
						while (node)
						{
							if (_value_comparator(node->value, val))
								node = node->traits.right;
							else if (_value_comparator(val, node->value))
								node = node->traits.left;
							else
								return iterator(node, const_cast<node_pointer *>(&_last), false);
						}
						return end();
					}

					const_iterator	lower_bound(const value_type& val) const
					{
						node_pointer	ret;
						node_pointer	node;

						ret = 0;
						node = _root;
						while (node)
						{
							if (_value_comparator(node->value, val))
								node = node->traits.right;
							else if (_value_comparator(val, node->value))
							{
								ret = node;
								node = node->traits.left;
							}
							else
								return iterator(node, const_cast<node_pointer *>(&_last), false);
						}
						if (ret)
							return iterator(ret, const_cast<node_pointer *>(&_last), false);
						return end();
					}

					const_iterator	upper_bound(const value_type& val) const
					{
						node_pointer	ret;
						node_pointer	node;

						ret = 0;
						node = _root;
						while (node)
						{
							if (_value_comparator(node->value, val))
								node = node->traits.right;
							else if (_value_comparator(val, node->value))
							{
								ret = node;
								node = node->traits.left;
							}
							else
							{
								ret = node->getInOrderSuccessor();
								break ;
							}
						}
						if (ret)
							return iterator(ret, const_cast<node_pointer *>(&_last), false);
						return end();
					}
				//===========================================================================================
				/// Operations End
				//===========================================================================================


				//===========================================================================================
				/// Element access
				//===========================================================================================
				public:
					//might throw : strong guarantee
					reference	operator[] (const value_type& val)
					{
						node_pointer	node;
						node_pointer	current;

						if (!_root)
							node = _putInPosition(val);
						else
						{
							current = _root;
							while (1)
							{
								//if val is less than the current node' value : insert on the left
								if (_value_comparator(val, current->value))
								{
									if (current->traits.left)
										current = current->traits.left;
									else
									{
										node = _putInPosition(current, val, true);
										break ;
									}
								}
								//if val is greater than the current node' value : insert on the right
								else if (_value_comparator(current->value, val))
								{
									if (current->traits.right)
										current = current->traits.right;
									else
									{
										node = _putInPosition(current, val, false);
										break ;
									}
								}
								//if val is equal to the current node' value : just return the current node' value
								else
									return current->value;
							}
							_retroBalance(current);
						}
						return node->value;
					}
				//===========================================================================================
				/// Element access
				//===========================================================================================


				//===========================================================================================
				/// Getters
				//===========================================================================================
				public:
					size_type	getCount() const
					{
						return _count;
					}
					size_type	max_size() const
					{
						return _nodeAllocator.max_size();
					}
				//===========================================================================================
				/// Getters End
				//===========================================================================================


				//===========================================================================================
				/// Nodes manipulation functions
				//===========================================================================================
				private:
					void	_destroyNode(node_pointer node)
					{
						_allocator.destroy(&(node->value));
						traits_allocator.destroy(&(node->traits));
						_nodeAllocator.deallocate(node, 1);
					}

					//might throw : strong guarantee
					node_pointer	_createNode(const value_type& val)
					{
						node_pointer	node;

						node = _nodeAllocator.allocate(1);
						try
						{
							traits_allocator.construct(&(node->traits), Traits());
						}
						catch (...)
						{
							_nodeAllocator.deallocate(node, 1);
							throw ;
						}
						try
						{
							_allocator.construct(&(node->value), val);
						}
						catch (...)
						{
							traits_allocator.destroy(&(node->traits));
							_nodeAllocator.deallocate(node, 1);
							throw ;
						}
						return node;
					}
				//===========================================================================================
				/// Nodes manipulation functions End
				//===========================================================================================


				//===========================================================================================
				/// Internal modifiers
				//===========================================================================================
				private:
					void	_balance(node_pointer node)
					{
						int balanceFactor;
						int subBalanceFactor;

						balanceFactor = node->getBalanceFactor();
						if (abs(balanceFactor) < 2)
							return ;
						if (balanceFactor < 0)
						{
							subBalanceFactor = node->traits.right->getBalanceFactor();
							if (subBalanceFactor <= 0)
								_rrRotate(node);
							else
								_rlRotate(node);
						}
						else
						{
							subBalanceFactor = node->traits.left->getBalanceFactor();
							if (subBalanceFactor < 0)
								_lrRotate(node);
							else
								_llRotate(node);
						}
					}

					//solates node from the rest of the tree (its parent does not recongnise him anymore 'poor child')
					void	_isolate(node_pointer node)
					{
						if (node->traits.parent)
						{
							if (node->traits.parent->traits.left == node)
								node->traits.parent->traits.left = 0;
							else
								node->traits.parent->traits.right = 0;
						}
						else
							_root = 0;
					}

					//b steals the parent of a
					void	_replace(node_pointer a, node_pointer b)
					{
						if (a == b)
							return ;
						b->traits.parent = a->traits.parent;
						if (a->traits.parent)
						{
							if (a->traits.parent->traits.left == a)
								a->traits.parent->traits.left = b;
							else
								a->traits.parent->traits.right = b;
						}
						else
							_root = b;
					}

					//a swaps position with b
					void	_swap(node_pointer a, node_pointer b)
					{
						if (a->traits.parent == b)
							_swapRelatedNodes(a, b);
						else if (b->traits.parent == a)
							_swapRelatedNodes(b, a);
						else
							_swapUnrelatedNodes(a, b);
					}

					//a swaps position with b : a has no direct relationship with b
					void	_swapUnrelatedNodes(node_pointer a, node_pointer b)
					{
						Traits	tmp;

						tmp = b->traits;
						//b adicates a's parent
						_replace(a, b);
						//children swap
							//give the children of 'a' to the b
						b->traits.left = a->traits.left;
						b->traits.right = a->traits.right;
							//make the new children of b recognise b as their parent
						if (b->traits.left)
							b->traits.left->traits.parent = b;
						if (b->traits.right)
							b->traits.right->traits.parent = b;
							//get the children of b from the custodian and give them to 'a'
						a->traits.left = tmp.left;
						a->traits.right = tmp.right;
							//make the new children of 'a' recognise b as their parent
						if (a->traits.left)
							a->traits.left->traits.parent = a;
						if (a->traits.right)
							a->traits.right->traits.parent = a;
						//the exparent of b adopts a
						a->traits.parent = tmp.parent;
						if (tmp.parent)
						{
							if (tmp.parent->traits.left == b)
								a->traits.parent->traits.left = a;
							else
								a->traits.parent->traits.right = a;
						}
						else
							_root = a;
					}

					//child swaps position with its parent
					void	_swapRelatedNodes(node_pointer child, node_pointer parent)
					{
						Traits	tmp;

						tmp = parent->traits;
						//the child abdicates its parent parents
						_replace(parent, child);
						//parent takes over the child's children
						parent->traits.left = child->traits.left;
						if (parent->traits.left)
							parent->traits.left->traits.parent = parent;
						parent->traits.right = child->traits.right;
						if (parent->traits.right)
							parent->traits.right->traits.parent = parent;
						//child takes over the parent's children
							//child was the left child of parent
						if (tmp.left == child)
						{
							child->traits.left = parent;
							child->traits.right = tmp.right;
							if (child->traits.right)
								child->traits.right->traits.parent = child;
						}
							//child was the right child of parent
						else
						{
							child->traits.right = parent;
							child->traits.left = tmp.left;
							if (child->traits.left)
								child->traits.left->traits.parent = child;
						}
						parent->traits.parent = child;
					}

					void	_delete(node_pointer node)
					{
						node_pointer	parent;
						node_pointer	candidate;

						_updateBoundsDelete(node);
						//the to-delete node has a both childs
						if (node->traits.left && node->traits.right)
						{
							candidate = node->getInOrderSuccessor();
							_swap(node, candidate);
							candidate->updateHeight();
						}
						parent = node->traits.parent;
						//the to-delete node has no children
						if (!node->traits.left && !node->traits.right)
							_isolate(node);
						//the to-delete node has a left child only
						else if (node->traits.left)
							_replace(node, node->traits.left);
						//the to-delete node has a right child only
						else if (node->traits.right)
							_replace(node, node->traits.right);
						//update the height of the upper subtree and balance
						_retroBalance(parent);
						_destroyNode(node);
						--_count;
					}

					void	_retroBalance(node_pointer node)
					{
						while (node)
						{
							node->updateHeight();
							_balance(node);
							node = node->traits.parent;
						}
					}

					void	_destorySubtree(node_pointer root)
					{
						if (!root)
							return;
						_destorySubtree(root->traits.left);
						_destorySubtree(root->traits.right);
						_destroyNode(root);
					}

					//might throw : strong guarantee
					void	_clone(const Avl& src)
					{
						node_pointer	node;

						try
						{
							for (node = src._begin; node; node = node->getInOrderSuccessor())
								insert(node->value);
						}
						catch (...)
						{
							clear();
							throw ;
						}
					}
				//===========================================================================================
				/// Internal modifiers End
				//===========================================================================================


				//===========================================================================================
				/// Rotations
				//===========================================================================================
				private:
					void	_llRotate(node_pointer root)
					{
						node_pointer	newRoot;

						newRoot = root->traits.left;

						//replace the current root with the newRoot
						_replace(root, newRoot);
						
						//make the current root the right child of the newRoot
							//let the right child of the newRoot (current root) embrace its left child
						root->traits.left = newRoot->traits.right;
						if (root->traits.left)
							root->traits.left->traits.parent = root;
							//let the newroot welcome its right child
						root->traits.parent = newRoot;
						newRoot->traits.right = root;

						//update the height of newRoot and its childs
						newRoot->traits.left->updateHeight();
						newRoot->traits.right->updateHeight();
						newRoot->updateHeight();
					}

					void	_rrRotate(node_pointer root)
					{
						node_pointer	newRoot;

						newRoot = root->traits.right;

						//replace the current root with the newRoot
						_replace(root, newRoot);
						
						//make the current root the left child of the newRoot
							//let the left child of the newRoot embrace its right child
						root->traits.right = newRoot->traits.left;
						if (root->traits.right)
							root->traits.right->traits.parent = root;
							//let the newroot welcome its left child
						root->traits.parent = newRoot;
						newRoot->traits.left = root;
						
						//update the height of newRoot and its childs
						newRoot->traits.left->updateHeight();
						newRoot->traits.right->updateHeight();
						newRoot->updateHeight();
					}

					void	_lrRotate(node_pointer root)
					{
						node_pointer	newRoot;

						newRoot = root->traits.left->traits.right;

						//replace the current node with the newRoot
						_replace(root, newRoot);
						
						//adjsut the left child of the newRoot
							//let the left child of the newroot embrace its new right child
						root->traits.left->traits.right = newRoot->traits.left;
						if (newRoot->traits.left)
							newRoot->traits.left->traits.parent = root->traits.left;
							//let the newroot welcome its left child
						newRoot->traits.left = root->traits.left;
						root->traits.left->traits.parent = newRoot;

						//adjust the right child of the newRoot
							//let the right child of the newroot embrace its new left child
						root->traits.left = newRoot->traits.right;
						if (root->traits.left)
							root->traits.left->traits.parent = root;
							//let the newroot welcome its right child
						newRoot->traits.right = root;
						root->traits.parent = newRoot;

						//update the height of newRoot and its childs
						newRoot->traits.left->updateHeight();
						newRoot->traits.right->updateHeight();
						newRoot->updateHeight();
					}

					void	_rlRotate(node_pointer root)
					{
						node_pointer	newRoot;

						newRoot = root->traits.right->traits.left;

						//replace the current node with the newRoot
						_replace(root, newRoot);
						
						//adjsut the right child of the newRoot
							//let the right child of the newroot embrace its new left child
						root->traits.right->traits.left = newRoot->traits.right;
						if (newRoot->traits.right)
							newRoot->traits.right->traits.parent = root->traits.right;
							//let the newroot welcome its right child
						newRoot->traits.right = root->traits.right;
						root->traits.right->traits.parent = newRoot;

						//adjsut the left child of the newRoot
							//let the left child of the newroot embrace its new right child
						root->traits.right = newRoot->traits.left;
						if (root->traits.right)
							root->traits.right->traits.parent = root;
							//let the newroot welcome its left child
						newRoot->traits.left = root;
						root->traits.parent = newRoot;

						//update the height of newRoot and its childs
						newRoot->traits.left->updateHeight();
						newRoot->traits.right->updateHeight();
						newRoot->updateHeight();
					}
				//===========================================================================================
				/// Rotations End
				//===========================================================================================


				//===========================================================================================
				/// auxiliaries
				//===========================================================================================
				private:
					void	_updateBoundsInsert(node_pointer node)
					{
						node_pointer	tmp;

						if (node == _begin)
						{
							tmp = node->getInOrderPredeccessor();
							if (tmp)
								_begin = tmp;
						}
						if (node == _last)
						{
							tmp = node->getInOrderSuccessor();
							if (tmp)
								_last = tmp;
						}
					}

					void	_updateBoundsDelete(node_pointer node)
					{
						if (node == _begin)
							_begin = node->getInOrderSuccessor();
						if (node == _last)
							_last = node->getInOrderPredeccessor();
					}

					node_pointer	_putInPosition(const value_type& val)
					{
						node_pointer	node;

						node = _createNode(val);
						_root = node;
						_last = node;
						_begin = node;
						++_count;
						return node;
					}

					node_pointer	_putInPosition(node_pointer node, const value_type& val)
					{
						node->value = val;
						return node;
					}

					node_pointer	_putInPosition(node_pointer parent, const value_type& val, bool isLeft)
					{
						node_pointer	node;

						node = _createNode(val);
						if (isLeft)
						{
							parent->traits.left = node;
							node->traits.parent = parent;
						}
						else
						{
							parent->traits.right = node;
							node->traits.parent = parent;
						}
						_updateBoundsInsert(parent);
						++_count;
						return node;
					}
				//===========================================================================================
				/// auxiliaries
				//===========================================================================================

				//===========================================================================================
				/// Allocator
				//===========================================================================================
				public:
					allocator_type	get_allocator() const
					{
						return _nodeAllocator;
					}
				//===========================================================================================
				/// Allocator End
				//===========================================================================================


				//===========================================================================================
				/// Observers
				//===========================================================================================
				public:
					value_compare	get_value_comparator() const
					{
						return _value_comparator;
					}
				//===========================================================================================
				/// Observers End
				//===========================================================================================


				//===========================================================================================
				/// General private functions
				//===========================================================================================
				private:
					template<class U>
					void	_normalSwap(U& a, U& b)
					{
						U	tmp(a);

						a = b;
						b = tmp;
					}
				//===========================================================================================
				/// General private functions End
				//===========================================================================================


				//===========================================================================================
				/// private data members
				//===========================================================================================
				private:
					size_type		_count;
					node_pointer	_root;
					node_pointer	_last;
					node_pointer	_begin;
					value_compare	_value_comparator;
					allocator_type	_allocator;
					node_allocator_type	_nodeAllocator;
					traits_allocator_type	traits_allocator;
				//===========================================================================================
				/// private data members End
				//===========================================================================================
			};

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
				value_type	&ret = _data[ft::make_pair(k, mapped_type())];
				return ret.second;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Element access End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			ft::pair<iterator,bool>	insert(const value_type& val)
			{
				return _data.insert(val);
			}

			iterator	insert(iterator position, const value_type& val)
			{
				ft::pair<iterator, bool>	ret =  _data.insert(val);

				(void)position;
				return ret.first;
			}

			template <class InputIterator>
			void	insert(InputIterator first, typename ft::enable_if<is_iterator<InputIterator>::value, InputIterator>::type last)
			{
				while (first != last)
				{
					_data.insert(*first);
					++first;
				}
			}

			void	erase(iterator position)
			{
				_data.erase(position);
			}

			size_type	erase(const key_type& k)
			{
				return _data.erase(ft::make_pair(k, mapped_type()));
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
				return _data.find(ft::make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			const_iterator	find(const key_type& k) const
			{
				return _data.find(ft::make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			size_type	count(const key_type& k) const
			{
				const_iterator	tmp = _data.find(ft::make_pair(k, mapped_type()));

				return tmp != end();
			}

			//might throw strong guarantee
			iterator	lower_bound(const key_type& k)
			{
				return _data.lower_bound(ft::make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			const_iterator	lower_bound(const key_type& k) const
			{
				return _data.lower_bound(ft::make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			iterator	upper_bound(const key_type& k)
			{
				return _data.upper_bound(ft::make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			const_iterator	upper_bound(const key_type& k) const
			{
				return _data.upper_bound(ft::make_pair(k, mapped_type()));
			}

			//might throw strong guarantee
			ft::pair<iterator,iterator>	equal_range(const key_type& k)
			{
				iterator	ret = lower_bound(k);

				if (ret == end())
					return ft::make_pair(ret, ret);
				//k is less than ret's key
				if (_key_comparator(k, ret->first))
					return ft::make_pair(ret, ret);
				return ft::make_pair(ret, ++ret);
			}

			//might throw strong guarantee
			ft::pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
			{
				const_iterator	ret = lower_bound(k);

				if (ret == end())
					return ft::make_pair(ret, ret);
				//k is less than ret's key
				if (_key_comparator(k, ret->first))
					return ft::make_pair(ret, ret);
				return ft::make_pair(ret, ++ret);
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
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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