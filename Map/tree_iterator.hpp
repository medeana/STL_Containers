#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

#include "../Vector/iterator_traits.hpp"
#include "nullptr.hpp"
#include "node.hpp"
#include <iostream>

namespace ft
{
	template<class T>
	class tree_iterator
	{
		public:
			typedef typename ft::Iter<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::Iter<ft::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::Iter<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef ft::node<T>																	node;
			typedef node*																		node_pointer;
			typedef node&																		node_reference;
			typedef	value_type*																	pointer;
			typedef value_type&																	reference;

		public:
			node_pointer	ptr;

		public:
			tree_iterator() : ptr(ft::nullptr_t){}

			explicit tree_iterator(node_pointer ptr) : ptr(ptr) {}

			tree_iterator(const tree_iterator& other) : ptr(other.ptr) {}

			tree_iterator& operator = (const tree_iterator& other)
			{
				if(this->ptr != other.get_ptr())
					this->ptr = other.get_ptr();
				return *this;
			}

			node_pointer get_ptr() const {return this->ptr;}

		private :
			node_pointer minimum(node_pointer n)
			{
				node_pointer aux = n;

				while(aux->left->get_nill() != true)
					aux = aux->left;
				return aux;
			}

			node_pointer maximum(node_pointer n)
			{
				node_pointer aux = n;

				while(aux->right->get_nill() != true)
					aux = aux->right;
				return aux;
			}

		public:
			reference			operator * () const {return (this->ptr->get_data());}
			pointer				operator -> () const {return &(this->ptr->get_data());}

			tree_iterator& operator ++ ()
			{

				if(this->ptr->get_nill() == true)
				{
					this->ptr = this->ptr->left;
					return *this;
				}
				if(this->ptr->right->get_nill() != true)
				{
					this->ptr = minimum(this->ptr->right);
					return *this;
				}

				node_pointer y = this->ptr->prev;
				while(y->get_nill() != true && this->ptr == y->right)
				{
					this->ptr = y;
					y = y->prev;
				}
				this->ptr = y;
				return *this;
			}

			tree_iterator operator ++ (int)
			{
				tree_iterator	tmp = *this;

				this->operator ++ ();
				return tmp;
			}

			tree_iterator& operator -- ()
			{
				if(this->ptr->get_nill() == true)
				{
					this->ptr = this->ptr->right;
					return *this;
				}
				if(this->ptr->left->get_nill() != true)
				{
					this->ptr = maximum(this->ptr->left);
					return *this;
				}

				node_pointer y = this->ptr->prev;
				while(y->get_nill() != true && this->ptr == y->left)
				{
					this->ptr = y;
					y = y->prev;
				}
				this->ptr = y;
				return *this;
			}

			tree_iterator operator -- (int)
			{
				tree_iterator	tmp = *this;

				this->operator -- ();
				return tmp;
			}

			bool	operator == (tree_iterator &b) 
			{
				return this->get_ptr() == b.get_ptr();
			}

			bool	operator != (tree_iterator &b) 
			{
				return this->get_ptr() != b.get_ptr();
			}

			bool	operator == (const tree_iterator &b) const 
			{
				return this->get_ptr() == b.get_ptr();
			}

			bool	operator != (const tree_iterator &b) const 
			{
				return this->get_ptr() != b.get_ptr();
			}
	};
}

#endif
