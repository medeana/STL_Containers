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


        explicit vector(const allocator_type& alloc = allocator_type()) : arr(0), sz(0), cap(0), allocator(alloc) {
        };

        explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : sz(n), cap(n), allocator(alloc) {
                    arr = allocator.allocate(n);
                    for (size_t i = 0; i < n; i++)
                        allocator.construct(arr + i, val);
                 };

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

        void assign (size_type n, const value_type& val){
            clear();
            if (n > cap){
                if (arr)
                    allocator.deallocate(arr, cap);
                cap = n;
                arr = allocator.allocate(x.cap);
            }
            for (size = 0; size < n; size++)
                allocator.construct(arr + size, val);
        }

    private:
        pointer arr;
        size_t  cap;
        size_t  sz;
        Allocator allocator;
    };
    
}


#endif