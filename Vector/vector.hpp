#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <exception>
#include <memory>
#include <cassert>
#include <iterator>
#include <typeinfo>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
    public:
        typedef T                                                                           value_type;
        typedef Allocator                                                                   allocator_type;
        typedef typename allocator_type::pointer                                            pointer;
        typedef typename allocator_type::const_pointer                                      const_pointer;
        typedef typename allocator_type::reference                                          reference;
        typedef typename allocator_type::const_reference                                    const_reference;
        typedef typename std::size_t                                                        size_type;
        typedef typename std::ptrdiff_t                                                     difference_type;
		typedef ft::Rai_iterator<std::random_access_iterator_tag, value_type>				iterator;
		typedef ft::Rai_iterator<std::random_access_iterator_tag, const value_type>		    const_iterator;
        typedef ft::reverse_iterator<iterator>                                              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                                        const_reverse_iterator;

        //Member functions

        explicit vector(const allocator_type& alloc = allocator_type()) : arr(0), cap(0), sz(0), allocator(alloc) {
        };

        explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : cap(n), sz(n), allocator(alloc) {
                    arr = allocator.allocate(n);
                    for (size_t i = 0; i < n; i++)
                        allocator.construct(arr + i, val);
                 };

        template <typename InputIterator>
        vector(InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
                const allocator_type& alloc = allocator_type()) : arr(0), sz(0), cap(0), allocator(alloc){
            sz = ft::distance(first, last);
            cap = sz;
            arr = allocator.allocate(sz);
            // size_t i = 0;
            for(;first != last; first++)
                // arr[i++] = *first;
                push_back(*first);
        }

        // template < typename InputIterator >
        // vector(InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
        //         const allocator_type& alloc = allocator_type()) : arr(0), sz(0), cap(0), allocator(alloc) {
		// 	sz = ft::distance(first, last);
		// 	cap = sz;
		// 	arr = allocator.allocate(sz);
		// 	size_t i = 0;
		// 	while (first != last) {
		// 		arr[i] = *first;
		// 		first++;
		// 		i++;
		// 	}
		// }


        vector (const vector<value_type> &x) : cap(x.cap), sz(x.sz), allocator(x.allocator) {
            arr = allocator.allocate(x.cap);
            for (size_t i = 0; i < x.sz; i++)
                allocator.construct(arr + i, *(x.arr + i));
        };

        ~vector(){
            clear();
            if (cap)
                allocator.deallocate(arr, cap);
        };

        vector &operator=(const vector &x)
        {
            allocator.deallocate(arr, cap);
            this->sz = x.sz;
            this->cap = x.cap;
            this->allocator = x.allocator;
            this->arr = allocator.allocate(x.cap);
            for (size_t i = 0; i < x.sz; i++)
                allocator.construct(arr + i, *(x.arr + i));
            return (*this);
        };

        // Iterators:
        iterator 			begin(){
            return (iterator (arr));
        }

		const_iterator		begin() const {
            return(const_iterator (arr));
        }

		iterator			end() {
            return (iterator (arr + sz));
        }

		const_iterator 		end() const {
            return (const_iterator (arr + sz));
        }

		const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

		reverse_iterator	rbegin() {
                return reverse_iterator(end());
        }

		const_reverse_iterator rend() const {
            return const_reverse_iterator (arr);
        }

		reverse_iterator	rend()	{
            return reverse_iterator(arr);
        }
        // Capacity:

        void resize(size_type n, value_type val = value_type()){
            if (n > max_size())
                throw std::length_error("vector");
            if (n < sz)
            {
                for (size_t i = n; i < sz; i++)
                    allocator.destroy(arr + i);
            }
            else if (n > sz)
            {
                if (n > cap && n <= cap * 2)
                    reserve(cap * 2);
                else if (n > cap * 2)
                    reserve(n);
                while (++sz < n)
                    allocator.construct(arr + sz, val);
            }
        }

        // void reserve (size_type n){
        //     if (n > max_size())
        //         throw std::length_error("vector");
        //     if (n > cap)
        //     {
        //         pointer new_arr = allocator.allocate(n);
        //         for (size_t i = 0; i < n; i ++)
        //         {
        //             allocator.construct(new_arr + i, arr[i]);
        //             allocator.destroy(arr + i);
        //         }
        //         if (cap)
        //             allocator.deallocate(arr, cap);
        //         arr = new_arr;
        //         cap = n;
        //     }
        // }

		void reserve(size_type n) {
			if (n > cap && n < max_size())
			{
				T *newPtr;
				newPtr = allocator.allocate(n);
				try {
					std::uninitialized_copy(arr, arr + sz, newPtr);
				} catch(...) {
					allocator.deallocate(newPtr, n);
					throw ;
				}
				allocator.deallocate(arr, cap);
				arr = newPtr;
				cap = n;
			}
		}

        size_type size() const{
            return this->sz;
        }

        size_type max_size() const{
            return this->allocator.max_size();
        }

        size_type capacity() const{
            return this->cap;
        }

        bool empty() const{
            return sz > 0 ? 0 : 1;
        }

        // Element access:

        reference   operator[](size_type n){
            return (arr[n]);
        }

        const_reference operator[](size_type n) const{
            return (arr[n]);
        }

        reference at(size_type n)
        {
            if (n >= sz)   
                throw std::out_of_range("vector");
            else
                return (arr[n]);
        }
        const_reference at(size_type n) const{
            if (n >= sz)   
                throw std::out_of_range("vector");
            else
                return (arr[n]);
        }

        reference front(){
            return arr[0];
        }


        const_reference front() const{
            return arr[0];
        }

        reference back(){
            return arr[sz - 1];
        }

        const_reference back() const{
            return arr[sz - 1];
        }
        
        // Modifiers:

        void pop_back(){
            if (!sz)
                return ;
            allocator.destroy(arr + (sz - 1));
            sz--;
        }

        void push_back (const value_type& val){
            if (!sz)
                reserve(1);
            if (sz == cap)  
                reserve(cap * 2);
            allocator.construct(arr + sz, val);
            sz++;     
        }

        template <class InputIterator>
        void	assign(InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last) {
            clear();
            if (arr)
                allocator.deallocate(arr, cap);
            sz = ft::distance(first, last);
            cap = sz;
            arr = allocator.allocate(cap);
            for (int i = 0; first != last; first++){
                allocator.construct(arr + i, *first);
                i++;
            }
        }

        void assign (size_type n, const value_type& val){
            clear();
            if (n > cap){
                if (arr)
                    allocator.deallocate(arr, cap);
                cap = n;
                arr = allocator.allocate(cap);
            }
            for (sz = 0; sz < n; sz++)
                allocator.construct(arr + sz, val);
        }

        iterator insert (iterator position, const value_type& val){
            size_t n = ft::distance(begin(), position);
            if (sz + 1 > cap)
                reserve(cap * 2);
            size_t i = 0;
            while (arr[i])
                i++;
            while (i > n) {
                allocator.construct(arr + i + 1, *(arr + i));
                allocator.destroy(arr + i);
                i--;
            }
            allocator.construct(arr + n, val);
            sz++;
            return (iterator(begin() + n));
        }



        void insert (iterator position, size_type n, const value_type& val){
            size_t dis = ft::distance(begin(), position);
            if (sz + n > cap && sz + n > cap * 2)
                reserve(sz + n);
            else if (sz + n > cap && sz + n < cap * 2)
                reserve(cap * 2);
            size_t i = sz;
            while (i >= dis){
                allocator.construct(arr + i + n, arr[i]);
                allocator.destroy(arr + i);
                i--;
            }
            size_t j = n + dis;
            for (;dis < j; dis++)
                allocator.construct(arr + dis, val);
            sz = sz + n;
        }


        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last){
            size_t dis = ft::distance(begin(), position);
            size_t n = ft::distance(first, last);
            size_t capa = 0;
            if (sz + n >= cap * 2)
                capa = sz + n;
            else if (sz + n > cap && sz + n < cap * 2)
                capa = cap * 2;
            else
                capa = cap;
            pointer new_arr = NULL;
            new_arr = allocator.allocate(capa);
            size_t i = 0;
            for (;i < dis; i++){
                allocator.construct(new_arr + i, arr[i]);
                allocator.destroy(arr + i);
            }
            size_t j = i;
            while (first != last) {
                allocator.construct(new_arr + i, *first);
                first++;
                i++;
            }
            while (arr[j]) {
                allocator.construct(new_arr + i, arr[j]);
                allocator.destroy(arr + j);
                i++;
                j++;
            }
            allocator.deallocate(arr, cap);
            arr = new_arr;
            cap = capa;
            sz = sz + n;
        }

        iterator erase (iterator position){
            size_t n = ft::distance(begin(), position);
            allocator.destroy(arr + n);
            n++;
            while (n < size()) {
                allocator.construct(arr + n - 1, arr[n]);
                n++;
            }
            sz--;
            return (iterator(begin() + n));
        }
        
        
        iterator erase (iterator first, iterator last) {
            size_t pos = ft::distance(begin(), first);
            size_t n = ft::distance(first, last);
            size_t en = ft::distance(last, end());
            size_t i = pos + n;
            size_t j = pos;
            while (j < i) {
                allocator.destroy(arr + j);
                j++;
            }
            while (en < sz) {
                allocator.construct(arr + en - n, arr[en]);
                en++;
            }
            sz = sz - n;
            return (iterator(arr + pos));
        }

        void     clear()
        {
            for (size_type i = 0; i < sz; i++)
                allocator.destroy(arr + i);
            sz = 0;
        }

        allocator_type get_allocator() const{
            return this->allocator;
        }

        void swap (vector& x){
            std::swap(this->allocator, x.allocator);
            std::swap(this->arr, x.arr);
            std::swap(this->sz, x.sz);
            std::swap(this->cap, x.cap);
        }

    private:
        pointer arr;
        size_t  cap;
        size_t  sz;
        Allocator allocator;
    };
    
}


#endif