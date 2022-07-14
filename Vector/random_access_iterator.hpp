#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

	template < typename Category , typename RAI, typename Distance = ptrdiff_t,
	        typename Pointer = RAI*, typename Reference = RAI&>
	class	Rai_iterator {
	public:
		typedef RAI         value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;

		Rai_iterator() : ptr(NULL){};

		Rai_iterator(pointer ptr) : ptr(ptr){};

		Rai_iterator(const Rai_iterator	& copy) {
            *this = copy;
        }

		Rai_iterator&		operator++() {
            this->ptr++; return(*this);
        }

		Rai_iterator		operator++(int) {
            Rai_iterator	tmp(*this);
            this->ptr++;
            return(tmp);
        }

		Rai_iterator&		operator--() {
            this->ptr--;
            return *this;
        }

		Rai_iterator&		operator--(int) {
            Rai_iterator	tmp(*this);
            this->ptr--; return (tmp);
        }

		Rai_iterator		operator-(difference_type n) const {
            return Rai_iterator(this->ptr - n);
        }


		difference_type operator-(Rai_iterator	&iter){
			return this->ptr - iter.ptr;
		}

		Rai_iterator		operator+(difference_type n) const {
            return Rai_iterator(this->ptr + n);
        }

		reference 		operator[](difference_type n) {
            return *(this + n);
        }

		Rai_iterator		operator+=(difference_type n) {
            return Rai_iterator(this->ptr += n);
        }

		Rai_iterator		operator-=(difference_type n) {
            return Rai_iterator(this->ptr -= n);
        }

		reference		operator*() {
            return (*ptr);
        }

		pointer 		operator->() {
            return (this->ptr);
        }

		template < typename U >
		bool operator< (const Rai_iterator<std::random_access_iterator_tag, U> &rhs) {
            return ( this->ptr < rhs.ptr);
        }

		template < typename U >
		Rai_iterator&	operator= (const Rai_iterator<std::random_access_iterator_tag, U> &rhs) {
            *this = rhs;
            return (*this);
        }

		template < typename U >
		bool operator<= (const Rai_iterator<std::random_access_iterator_tag, U> &rhs) {
            return ( this->ptr <= rhs.ptr);
        }

		template < typename U >
		bool operator> (const Rai_iterator<std::random_access_iterator_tag, U> &rhs) {
            return ( this->ptr > rhs.ptr);
        }

		template < typename U >
		bool	operator>= (const Rai_iterator<std::random_access_iterator_tag, U> &rhs) {
            return (this->ptr >= rhs.ptr);
        }

		template < typename U >
		bool operator== (const Rai_iterator<std::random_access_iterator_tag, U> &rhs) {
            return (this->ptr == rhs.ptr);
        }

		template < typename U >
		bool operator!= (const Rai_iterator<std::random_access_iterator_tag, U> &rhs) {
            return (this->ptr != rhs.ptr);
        }

	protected:
		pointer ptr;
	};

}

#endif
