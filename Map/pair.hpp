#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
    	template< class T1, class T2 >
        struct pair {
			typedef T1  first_type;
			typedef T2  second_type;

			first_type  first;
			second_type second;

			pair() : first(), second() {}

			pair( const first_type& x, const second_type& y ) : first(x), second(y) {}

			pair( const pair& p ) : first(p.first), second(p.second) {}

			template< class U1, class U2 >
			pair( const pair<U1, U2>& p ) : first(p.second), second(p.first) {}

			pair & operator=(const pair& other);

            ~pair() {}
	};

	template <class T1, class T2>
	pair<T1, T2> & pair<T1, T2>::operator=(const pair<T1, T2>& other)
	{
		if (this != & other)
		{
			first = other.first;
			second = other.second;
		}
		return *this;
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 key, T2 val)
	{
		pair<T1, T2> p(key, val);
		return p;
	}

	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
	 	return lhs.first < rhs.first ||
        	 (lhs.first <= rhs.first && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template< class T1, class T2 >
	ft::pair<T1,T2> make_pair( T1 t, T2 u ) {
		return pair<T1, T2>(t, u);
	}
}


#endif