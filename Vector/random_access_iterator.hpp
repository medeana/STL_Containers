#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "vector.hpp"
#include "iterator_traits.hpp"

namespace ft{
    template<typename T>
    class random_iterator {
    public:
        typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
        typedef typename ft::iterator_traits<T*>::value_type		value_type;
        typedef typename ft::iterator_traits<T*>::pointer			pointer;
        typedef typename ft::iterator_traits<T*>::reference			reference;
        typedef typename ft::iterator_traits<T*>::iterator_category	iterator_category;


    random_iterator() : ptr(NULL) {};
    random_iterator(pointer p) : ptr(p) {};
    random_iterator(const random_iterator& rhs){
        *this = rhs;
    }

    ~random_iterator();
    
    random_iterator &operator=(const random_iterator &rhs){
        this->ptr = rhs.ptr;
        return (*this);
    }

    random_iterator &operator++(){
        ++(*this);
        return (*this);
    }

    random_iterator operator++(int){
        random_iterator tmp = (*this);
        ++(*this);
        return tmp;
    }

    random_iterator &operator--(){
        this->ptr--;
        return (*this);
    }

    random_iterator operator--(int){
        random_iterator tmp = (*this);
        --(*this);
        return tmp;
    }

    random_iterator &operator+=(difference_type n){
        return random_iterator(this->ptr += n)
    }

    random_iterator &operator-=(difference_type n){
        return random_iterator(this->ptr -= n);
    }

    reference operator*() const {
        return (*ptr);
    }

    reference operator->() const {
        return (this->ptr);
    }

    random_iterator operator+(difference_type n) const {
        random_iterator tmp = *this;
        return tmp + n;
    }

    random_iterator operator-(difference_type n) {
        random_iterator tmp = *this;
        return tmp - n;
    }

    difference_type operator-(const random_iterator &rhs) const {
			return this->ptr - rhs.ptr;
	}

    reference operator[](difference_type n){
        return *(this + n);
    }

    bool operator==(const random_iterator &rhs) const {
        return (this->ptr == rhs.ptr);
    }

    bool operator!=(const random_iterator &rhs) const {
        return (this->ptr != rhs.ptr);
    }

    bool operator<(const random_iterator &rhs) const {
        return (rhs.ptr - ptr) > 0;
    }
    bool operator>(const random_iterator &rhs) const {
        return operator<(rhs);
    }
    bool operator>=(const random_iterator &rhs) const {
        return !operator<(rhs);
    }
    bool operator<=(const random_iterator &rhs) const {
        return !operator>(rhs);
    }






    private:
        pointer ptr;
    };

}



#endif
