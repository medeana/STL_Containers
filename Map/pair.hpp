#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		public:
			typedef T1	first_t;
			typedef T2	second_t;

			first_t		first;
			second_t	second;
	
			pair() : first(), second() {}

			template<class U, class V> 
			pair (const pair<U,V>& other) : first(other.first), second(other.second) {} 

			pair(const first_t& a, const second_t& b) : first(a), second(b) {}
	
			pair& operator = (const pair& other)
			{
				this->first = other.first;
				this->second = other.second;
				return *this;
			}

			pair& operator * ()
			{
				return *this;
			}
	};

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}
	
	template <class T1, class T2>
	bool operator == (const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y) 
	{
		return x.first == y.first && x.second == y.second;
	}

	template <class T1, class T2>
	bool operator < (const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y) 
	{
		return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
	}

	template <class T1, class T2>
	bool operator > (const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y) 
	{
		return (x.first > y.first || (!(y.first > x.first) && x.second > y.second));
	}

	template <class T1, class T2>
	bool operator <= (const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y) 
	{
		return !(x > y); 
	}

	template <class T1, class T2>
	bool operator >= (const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y) 
	{
		return !(x < y); 
	}

}
#endif