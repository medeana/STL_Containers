#ifndef STACK_HPP
#define STACK_HPP

#include "../Vector/vector.hpp"
#include <vector>

namespace ft {
    template<typename T, typename Container = ft::vector<T> >
    class stack
    {
    public:
		typedef Container                                   container_type;
		typedef typename Container::value_type              value_type;
		typedef typename container_type::reference          reference;
		typedef typename container_type::const_reference    const_reference;
		typedef size_t                                      size_type;

        explicit stack(const container_type& cont = container_type()) : c(cont) {}

		~stack() {};

        stack (const stack &x) {
            *this = x;
        }

        stack &operator=(const stack &x) {
            this->c = x.c;
            return (*this);
        }

		void 		push(const value_type &elems) { 
            this->c.push_back(elems);
        }
		void 		pop() {
            this->c.pop_back();
            }
		reference 	top() {
            return (this->c.back());
            }
		const_reference top() const { 
            return (this->c.back());
        }
		size_type 	size() {
            return (this->c.size());
        }
		bool		empty() const {
            return (this->c.size() == 0 ? true : false);
        }
		void	dispStack() {
			for (size_t i = 0;i < c.size();i++) {
				std::cout << c[i] <<  " ";
			}
			std::cout << std::endl;
		}

    protected :
        container_type c;

    	template < typename A , typename B>
		friend bool operator==(const ft::stack<A , B>&lhs, const ft::stack<A, B>&rhs);
		template < typename A , typename B>
		friend bool operator >= (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs);
		template < typename A , typename B>
		friend bool operator <= (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs);
		template < typename A , typename B>
		friend bool operator > (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs);
		template < typename A , typename B>
		friend bool operator < (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs);
		template < typename A , typename B>
		friend bool operator != (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs);
	};
		template < typename A , typename B>
			bool operator==(const ft::stack<A , B>&lhs, const ft::stack<A, B>&rhs) {
			return (lhs.c==rhs.c);
		}

		template < typename A, typename B >
			bool operator >= (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs) {
			return (lhs.c >= rhs.c);
		}

		template < typename A, typename B >
			bool operator <= (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs) {
			return (lhs.c <= rhs.c);
		}

		template < typename A, typename B >
			bool operator > (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs) {
			return (lhs.c > rhs.c);
		}

		template < typename A, typename B >
			bool operator < (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs) {
			return (lhs.c < rhs.c);
		}

		template < typename A, typename B >
			bool operator != (const ft::stack<A, B> &lhs, const ft::stack<A, B> &rhs) {
			return (lhs.c != rhs.c);
		}
    

}

#endif
