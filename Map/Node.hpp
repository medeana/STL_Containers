#ifndef NODE_HPP
# define NODE_HPP

#include "nullptr.hpp"

namespace ft
{
	template<typename T>
	struct node
	{
		typedef	T						value_type;
		value_type						data;
		node*							left;
		node*							right;
		node*							prev;
		bool							nill;
		bool							black;

		node() : nill(true) {}

		node(const T val) : data(val), nill(false) {}

		node(const T& _data, node* _nill) 
		: data(_data), left(_nill), right(_nill), prev(_nill), nill(false), black(false) {}

		~node() {}

		node(node const& other) : data(other.data)
		{
			left = other.left;
			right = other.right;
			prev = other.prev;
			nill = other.nill;
			black = other.black;
		}
		
		value_type& get_data() 
		{
			return data;
		}

		const value_type& get_data() const 
		{
			return data;
		}

		void	set_prev(node* _prev)
		{
			this->prev = _prev;
		}
		
		void	set_nill(bool set)
		{
			this->nill = set;
		}

		bool get_nill() const
		{
			return this->nill;
		}

		bool get_nill() 
		{
			return this->nill;
		}

		bool get_color()
		{
			return this->black;
		}
	};

}

#endif