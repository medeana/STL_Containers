#ifndef 	TREE_HPP
# define 	TREE_HPP

# include <memory>
# include <functional>
# include <algorithm>
# include "../Vector/iterator_traits.hpp"
# include "pair.hpp"
# include "node.hpp"
# include "bidirectional_iterator.hpp"

namespace ft
{
	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class rbtree
	{
		public :

			typedef T											value_type;
			typedef Node<value_type>							node;
			typedef Compare										compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::template rebind<node>::other node__allocator;
			typedef size_t										size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef tree_iter<node *, pointer>			iterator;
			typedef tree_iter<node *, const_pointer>	const_iterator;
			typedef reverse_iter<iterator>				reverse_iterator;
			typedef reverse_iter<const_iterator>		const_reverse_iterator;

			explicit rbtree() : __compare(), __alloc(), __size(0), __root(NULL) { __createNilNode();}

			explicit rbtree(const compare & comp, const allocator_type & alloc) : __compare(comp),
				__alloc(alloc), __size(0), __root(NULL) { __createNilNode();}

			rbtree(const rbtree &other) : __compare(other.__compare), __alloc(other.__alloc),
					__size(other.__size), __root(NULL), __nil(NULL) {
				__createNilNode();
				__clone(this->__root, NULL, other.__root);
				if (__root)
				{
					this->__nil->__left = this->__root;
					this->__root->__parent = this->__nil;
				}
			}

			rbtree &operator=(const rbtree &other)
			{
				node *tmp = NULL;

				if (this != &other)
				{
					__clone(tmp, NULL, other.__root);
					clear();
					__root = tmp;
					if (__root)
					{
						this->__nil->__left = this->__root;
						this->__root->__parent = this->__nil;
					}
					__size = other.__size;
					__alloc = other.__alloc;
					__compare = other.__compare;
				}
				return *this;
			}

			~rbtree() {
				clear();
				__cleanNilNode();
			}

		protected :

			compare				__compare;
			node__allocator 	__alloc;
			size_type 			__size;
			node				*__root;
			node 				*__nil;
		
		public : 

			void clear()
			{
				__clear(this->__root);
				__root = NULL;
			}

			iterator begin()
			{
				iterator it;

				if (!__root)
					it = this->__nil;
				else
					it = this->__findMin(__root);
				return it;
			}

			const_iterator begin() const
			{
				const_iterator it;
				
				if (!__root)
					it = this->__nil;
				else
					it = this->__findMin(__root);
				return it;
			}

			iterator end(){ iterator it(__nil); return it;}

			const_iterator end() const { const_iterator it(__nil); return it;}

			reverse_iterator rbegin() { return reverse_iterator(this->end());}

			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end());}

			reverse_iterator rend() { return reverse_iterator(this->begin());}

			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin());}

			bool empty() const
			{
				return __size == 0;
			}

			size_type size() const
			{
				return __size;
			}

			size_type max_size() const
			{
				return __alloc.max_size();
			}

			void swap(rbtree & rhs)
			{
				std::swap(__compare, rhs.__compare);
				std::swap(__alloc, rhs.__alloc);
				std::swap(__size, rhs.__size);
				std::swap(__root, rhs.__root);
				std::swap(__nil, rhs.__nil);
			}

			ft::pair<iterator, bool> insert(const value_type & x)
			{
				ft::pair<node *, bool> res = this->__insert_system(x, this->__root);
				return ft::make_pair(iterator(res.first), res.second);
			}

			iterator insert(iterator hint, const value_type& x)
			{
				iterator 				tmp(hint);
				ft::pair<node *, bool> 	res;

				if (hint.base() && hint != this->end() 
					&& this->__compare(*hint, x) && this->__compare(x, *(tmp++)))
				{
					res = this->__insert_system(x, hint.base());
					return iterator(res.first);
				}
				else
					res = this->__insert_system(x, __root);
				return iterator(res.first);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
				{
					insert(*first);
				}
			}

			void erase(iterator pos)
			{
				erase(*pos);
			}

			size_type erase(const T & value)
			{
				node *toErase = __findNode(value);

				if (toErase)
				{
					__erase(toErase);
					return 1;
				}
				return 0;
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			ft::pair<iterator, iterator> equal_range(const T & key)
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const T & key) const
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			iterator lower_bound(const T & key)
			{
				node *tmp = this->__root;
				node *res = this->__nil;

				while (tmp)
				{
					if (__compare(tmp->_value, key))
						tmp = tmp->__right;
					else
					{
						res = tmp;
						tmp = tmp->__left;
					}
				}
				return iterator(res);
			}

			const_iterator lower_bound(const T & key) const
			{
				node *tmp = this->__root;
				node *res = this->__nil;

				while (tmp)
				{
					if (__compare(tmp->_value, key))
						tmp = tmp->__right;
					else
					{
						res = tmp;
						tmp = tmp->__left;
					}
				}
				return const_iterator(res);
			}

			iterator upper_bound(const T & key)
			{
				node *tmp = this->__root;
				node *res = this->__nil;

				while (tmp)
				{
					if (__compare(key, tmp->_value))
					{
						res = tmp;
						tmp = tmp->__left;
					}
					else
						tmp = tmp->__right;
				}
				return iterator(res);
			}

			const_iterator upper_bound(const T & key) const
			{
				node *tmp = this->__root;
				node *res = this->__nil;

				while (tmp)
				{
					if (__compare(key, tmp->_value))
					{
						res = tmp;
						tmp = tmp->__left;
					}
					else
						tmp = tmp->__right;
				}
				return const_iterator(res);
			}

			iterator find(const value_type & key)
			{
				node * tmp = __findNode(key);
			
				if (tmp)
					return iterator(__findNode(key));
				return iterator(this->end());
			}

			const_iterator find(const value_type & key) const
			{
				node * tmp = __findNode(key);
			
				if (tmp)
					return const_iterator(__findNode(key));
				return const_iterator(this->end());
			}

		protected :

			void __clear(node *curr)
			{
				if (curr == NULL)
					return ;
				__clear(curr->__left);
				__clear(curr->__right);
				__remove_node(curr);
			}

			void __cleanNilNode(void)
			{
				if (this->__nil)
				{
					__alloc.destroy(this->__nil);
					__alloc.deallocate(this->__nil, 1);
				}
			}

			void __createNilNode(void)
			{
				this->__nil = __alloc.allocate(1);
				this->__nil->__is_red = false;
			}

			void __clone(node *&curr, node *parent, node *other)
			{
				if (!other)
					return ;
				curr = __createNode(other->_value);
				curr->__parent = parent;
				curr->__is_red = other->__is_red;
				__clone(curr->__right, curr, other->__right);
				__clone(curr->__left, curr, other->__left);
			}

			node *__findNode(const value_type & value) const 
			{
				node *tmp = __root;

				while (tmp)
				{
					if (__compare(tmp->_value, value))
						tmp = tmp->__right;
					else if (__compare(value, tmp->_value))
						tmp = tmp->__left;
					else
					{
						return tmp;
					}
				}
				return NULL;
			}

			node *__createNode(const value_type & value)
			{
				node *newNode = __alloc.allocate(1);
				__alloc.construct(newNode, value);
				return (newNode);
			}
			
			ft::pair<node *, bool> __insert_system(	const value_type & value, node *subtreeRoot)
			{
				if (__root == NULL)
				{
					__root = this->__createNode(value);
					__root->__is_red = false;
					__size++;
					this->__nil->__left = this->__root;
					this->__root->__parent = this->__nil;
					return ft::make_pair(this->__root, true);
				}
				
				this->__nil->__left = NULL;
				this->__root->__parent = NULL;

				node *a = subtreeRoot;
				node *b = NULL;
				node *newNode = this->__createNode(value);
				__size++;
				while (a)
				{
					b = a;
					if (__compare(newNode->_value, a->_value))
						a = a->__left;
					else if (__compare(a->_value, newNode->_value))
						a = a->__right;
					else
					{
						__remove_node(newNode);
						this->__nil->__left = this->__root;
						this->__root->__parent = this->__nil;
						return ft::make_pair(a, false);
					}
				}
				newNode->__parent = b;
				if (!b)
					subtreeRoot = newNode;
				else if (__compare(newNode->_value, b->_value))
					b->__left = newNode;
				else 
					b->__right = newNode;
				__tree_insert_fixup(newNode);
				this->__nil->__left = this->__root;
				this->__root->__parent = this->__nil;
				return ft::make_pair(newNode, true);
			}

			void __tree_insert_fixup(node *elem)
			{
				node *uncle = NULL;

				while (elem->__parent && elem->__parent->__is_red)
				{
					if (elem->__parent == elem->__parent->__parent->__left)
					{
						uncle = elem->__parent->__parent->__right;
						if (uncle && uncle->__is_red)
						{
							elem->__parent->__is_red = false;
							uncle->__is_red = false;
							elem->__parent->__parent->__is_red = true;
							elem = elem->__parent->__parent;
						}
						else
						{
							if (elem == elem->__parent->__right)
							{
								elem = elem->__parent;
								this->___leftRotate(elem);
							}
							elem->__parent->__is_red = false;
							elem->__parent->__parent->__is_red = true;
							this->___rightRotate(elem->__parent->__parent);
						}
					}
					else
					{
						uncle = elem->__parent->__parent->__left;
						if (uncle && uncle->__is_red)
						{											
							elem->__parent->__is_red = false;
							uncle->__is_red = false;
							elem->__parent->__parent->__is_red = true;
							elem = elem->__parent->__parent;
						}
						else
						{
							if (elem == elem->__parent->__left)
							{
								elem = elem->__parent;
								this->___rightRotate(elem);
							}
							elem->__parent->__is_red = false;
							elem->__parent->__parent->__is_red = true;
							this->___leftRotate(elem->__parent->__parent);
						}
					}
				}
				this->__root->__is_red = false;
			}

			void __erase(node *elem)
			{
				node *tmp;
				node *tmpTwo;
				bool trueColor = elem->__is_red;
				tmp = elem;
				
				if (!elem->__left)
				{
					tmpTwo = elem->__right;
					__transplant(elem, elem->__right);
					__remove_node(elem);
				}
				else if (!elem->__right)
				{
					tmpTwo = elem->__left;
					__transplant(elem, elem->__left);
					__remove_node(elem);
				}
				else
				{
					tmp = __findMin(elem->__right);
					trueColor = tmp->__is_red;
					tmpTwo = tmp->__right;
					if (tmp->__parent && tmp->__parent != elem)
					{
						__transplant(tmp, tmp->__right);
						tmp->__right = elem->__right;
						tmp->__right->__parent = tmp;
					}
					__transplant(elem, tmp);
					tmp->__left = elem->__left;
					tmp->__left->__parent = tmp;
					tmp->__is_red = elem->__is_red;
					__remove_node(elem);
				}
				if (trueColor == false && tmpTwo)
					__tree_erase_fixup(tmpTwo);
				if (this->__root)
				{
					this->__nil->__left = this->__root;
					this->__root->__parent = this->__nil;
				}
			}

			void __transplant(node *toDel, node *toReplace)
			{
				if (toDel->__parent == this->__nil)
					this->__root = toReplace;
				else if (toDel == toDel->__parent->__left)
					toDel->__parent->__left = toReplace;
				else
					toDel->__parent->__right = toReplace;
				if (toReplace)
					toReplace->__parent = toDel->__parent;
			}

			void __remove_node(node * elem)
			{
				this->__alloc.destroy(elem);
				this->__alloc.deallocate(elem, 1);
				this->__size--;
			}

			void __tree_erase_fixup(node *elem)
			{
				node *sibling = NULL;
				while (elem != this->__root && !elem->__is_red)
				{
					if (elem && elem == elem->__parent->__left)	
					{
						sibling = elem->__parent->__right;
						if (sibling && sibling->__is_red)
						{
							sibling->__is_red = false;
							elem->__parent->__is_red = true;
							___leftRotate(elem->__parent);
							sibling = elem->__parent->__right;
						}
						if (sibling && sibling->__left && sibling->__right && 
							!sibling->__left->__is_red && !sibling->__right->__is_red)
						{
							sibling->__is_red = true;
							elem = elem->__parent;
						}	
						else
						{
							if (sibling && sibling->__right && !sibling->__right->__is_red)
							{
								sibling->__left->__is_red = false;
								sibling->__is_red = true;
								___rightRotate(sibling);
								sibling = elem->__parent->__right;
							}
							if (sibling)
								sibling->__is_red = elem->__parent->__is_red;
							elem->__parent->__is_red = false;
							if (sibling && sibling->__right)
								sibling->__right->__is_red = false;
							___leftRotate(elem->__parent);
							elem = this->__root;
						}
					}
					else if (elem == elem->__parent->__right)
					{
						sibling = elem->__parent->__left;
						if (sibling && sibling->__is_red)
						{
							sibling->__is_red = false;
							elem->__parent->__is_red = true;
							___rightRotate(elem->__parent);
							sibling = elem->__parent->__left;
						}
						if (sibling && sibling->__left && sibling->__right && 
							!sibling->__left->__is_red && !sibling->__right->__is_red)
						{
							sibling->__is_red = true;
							elem = elem->__parent;
							sibling = elem->__parent->__left;
						}
						else
						{
							if (sibling && sibling->__left && !sibling->__left->__is_red)
							{
								sibling->__right->__is_red = false;
								sibling->__is_red = true;
								___leftRotate(sibling);
								sibling = elem->__parent->__left;
							}
							if (sibling)
								sibling->__is_red = elem->__parent->__is_red;
							elem->__parent->__is_red = false;
							if (sibling && sibling->__left)
							{
								sibling->__left->__is_red = false;
							}
							___rightRotate(elem->__parent);
							elem = this->__root;
						}
					}
				}	
				elem->__is_red = false;
			}


			void ___leftRotate(node *a)
			{
				node *b;

				b = a->__right;
				a->__right = b->__left;
				if (b->__left)
					b->__left->__parent = a;
				b->__parent = a->__parent;
				if (a == __root)
					__root = b;
				else if (a == a->__parent->__left)
					a->__parent->__left = b;
				else 
					a->__parent->__right = b;
				b->__left = a;
				a->__parent = b;
			}

			void ___rightRotate(node *a)
			{
				node *b;

				b = a->__left;
				a->__left = b->__right;
				if (b->__right)
					b->__right->__parent = a;
				b->__parent = a->__parent;
				if (a == __root)
					__root = b;
				else if (a == a->__parent->__right)
					a->__parent->__right = b;
				else
					a->__parent->__left = b;
				b->__right = a;
				a->__parent = b;
			}


			node *__findMin(node *elem) const
			{
				node *min = elem;

				while (min && min->__left && min->__left != __nil)
					min = min->__left;
				return min;
			}

			node *__findMax(node *elem) const
			{
				node *max = elem;
				while (max && max->__right && max->__right != __nil)
					max = max->__right;
				return max;
			}

			void __visualize(int tabs, node *root)
			{
				std::string color = root->__is_red == false ? "\x1b[30;4m" : "\x1b[31;1m" ;
				for (int i = 0; i < tabs; i++)
					std::cout << '\t';
				std::cout << color << root->_value << "\x1b[30m" << std::endl;
				if (root->__left)
					__visualize(tabs - 1, root->__left);
				if (root->__right)
					__visualize(tabs + 1, root->__right);
			}
	};
}

#endif