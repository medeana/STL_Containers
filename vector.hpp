#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <exception>
#include <memory>
#include <cassert>
#include <iterator>
#include <typeinfo>

namespace ft{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
    public:
        typedef T                                           value_type;
        typedef Allocator                                   allocator_type;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename std::size_t                        size_type;
        typedef typename std::ptrdiff_t                     difference_type;


        //Member functions

        explicit vector(const allocator_type& alloc = allocator_type()) : arr(0), sz(0), cap(0), allocator(alloc) {
        };

        explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : sz(n), cap(n), allocator(alloc) {
                    arr = allocator.allocate(n);
                    for (size_t i = 0; i < n; i++)
                        allocator.construct(arr + i, val);
                 };

                // template <class InputIterator>
                // vector (InputIterator first, InputIterator last,  const allocator_type& alloc = allocator_type());


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
                // template <class InputIterator>
                // void assign (InputIterator first, InputIterator last);

        // Capacity:

        // void resize (size_type n, value_type val = value_type()){}

        // void reserve (size_type n);

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

        void     clear()
        {
            for (size_type i = 0; i < sz; i++)
                allocator.destroy(arr + i);
            sz = 0;
        }

        allocator_type get_allocator() const{
            return this->allocator;
        }


    private:
        pointer arr;
        size_t  cap;
        size_t  sz;
        Allocator allocator;
    };
    
}


#endif