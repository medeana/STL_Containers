#ifndef 	BIDIRECTIONAL_ITER_HPP
# define 	BIDIRECTIONAL_ITER_HPP

# include "../Vector/iterator_traits.hpp"

namespace ft
{	
	template <class Iter, class T>
	class tree_iter : public iterator<	typename iterator_traits<Iter>::iterator_category,
										typename iterator_traits<Iter>::value_type,
										typename iterator_traits<Iter>::difference_type,
										typename iterator_traits<Iter>::pointer,
										typename iterator_traits<Iter>::reference>
	{
		public :
			typedef Iter												iterator_type;
			typedef typename iterator_traits<T>::reference 				reference;
			typedef typename iterator_traits<T>::pointer				pointer;
			typedef typename iterator_traits<T>::difference_type		difference_type;
			typedef tree_iter<Iter, T>									self;

		private :
			iterator_type it;

			iterator_type findMin(iterator_type currElem)
			{
				while (currElem && currElem->left)
					currElem = currElem->left;
				return currElem;
			}

			iterator_type findMax(iterator_type currElem)
			{
				while (currElem && currElem->right)
					currElem = currElem->right;
				return currElem;
			}

			iterator_type findPredessor(iterator_type elem)
			{
				iterator_type tmp = elem->parent;
			
				if (elem->left)
					return findMax(elem->left);
				while (tmp && elem == tmp->left)
				{
					elem = tmp;
					tmp = tmp->parent;
				}
				return (tmp);
			}

			iterator_type findSuccessor(iterator_type elem)
			{
				iterator_type tmp = elem->parent;
			
				if (elem->right)
					return findMin(elem->right);
				while (tmp && elem == tmp->right)
				{
					elem = tmp;
					tmp = tmp->parent;
				}
				return (tmp);
			}

		public
			tree_iter()
			: it() {}

			tree_iter(iterator_type value)
			: it(value) {}

			template <typename It, typename I>
			tree_iter(const tree_iter<It, I> & rhs)
			: it(rhs.base()) {}

			template <typename It, typename I>		
			tree_iter &operator=(const tree_iter<It, I> & rhs)
			{
				if (this != &rhs)
					it = rhs.base();
				return *this;
			}
			~tree_iter() {}


			iterator_type base() const
			{
				return it;
			}

			reference operator*() const
			{
				return it->_value;
			}
			pointer operator->() const
			{
				return &(it->_value);
			}
			self operator++(int)
			{
				tree_iter tmp = *this;
				it = findSuccessor(it);
				return tmp;
			}
			self operator--(int)
			{
				tree_iter tmp = *this;
				it = findPredessor(it);
				return tmp;
			}
			self & operator++()
			{
				it = findSuccessor(it);
				return *this;
			}
			self & operator--()
			{
				it = findPredessor(it);
				return *this;
			}
			
			friend bool operator==(	const self & rhs, 
									const self & lhs)
			{
				return rhs.it == lhs.it;
			}

			friend bool operator!=(	const self & rhs, 
									const self & lhs)
			{
				return rhs.it != lhs.it;
			}
	};

	template <class Iter>
	class reverse_iter : 	public iterator<	typename iterator_traits<Iter>::iterator_category,
												typename iterator_traits<Iter>::value_type,
												typename iterator_traits<Iter>::difference_type,
												typename iterator_traits<Iter>::pointer,
												typename iterator_traits<Iter>::reference>
	{
		public :
			typedef	Iter										iterator_type;
			typedef std::ptrdiff_t								difference_type;
			typedef typename iterator_traits<Iter>::pointer 	pointer;
			typedef typename iterator_traits<Iter>::reference 	reference;
			typedef	reverse_iter<Iter>							self;
		
		protected :
			iterator_type current;
		
		public :
			reverse_iter()
			: current() {}

			reverse_iter(const reverse_iter & it)
			:	current(it.current)
			{}

			template <class It>
			reverse_iter(const reverse_iter<It> & it)
			: current(it.base())
			{}

			explicit reverse_iter(iterator_type x)
			: current(x) {}

			iterator_type base() const
			{
				return current;
			}

			reference operator*() const
			{
				Iter tmp = current;
				return *(--tmp);
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			self & operator++()
			{
				--current;
				return *this;
			}

			self operator++(int)
			{
				reverse_iter tmp = *this;
				--current;
				return tmp;
			}

			self & operator--()
			{
				++current;
				return *this;
			}

			self operator--(int)
			{
				reverse_iter tmp = *this;
				++current;
				return tmp;
			}

			friend bool operator==(	const reverse_iter<Iter> & lhs,
									const reverse_iter<Iter> & rhs)
			{
				return lhs.base() == rhs.base();
			}

			friend bool operator!=(	const reverse_iter<Iter> & lhs,
									const reverse_iter<Iter> & rhs)
			{
				return lhs.base() != rhs.base();
			}
	};
}

#endif