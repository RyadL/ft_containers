#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef	T				value_type;
		typedef	Container		container_type;
		typedef	std::size_t		size_type;

	protected:
		Container	sub_container;

	public:
		explicit	stack(const container_type &ctnr = container_type()) : sub_container(ctnr)
		{
		}

		value_type	&top(void)
		{
			return sub_container.back();
		}

		const value_type	&top(void) const
		{
			return sub_container.back();
		}

		bool		empty(void) const
		{
			return sub_container.empty();
		}

		size_type	size(void) const
		{
			return sub_container.size();
		}

		void push(const value_type &val)
		{
			sub_container.push_back(val);
		}

		void pop(void)
		{
			sub_container.pop_back();
		}

		friend	bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs.sub_container == rhs.sub_container;
		}
		friend	bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs.sub_container != rhs.sub_container;
		}
		friend	bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs.sub_container < rhs.sub_container;
		}
		friend	bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs.sub_container <= rhs.sub_container;
		}
		friend	bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs.sub_container > rhs.sub_container;
		}
		friend	bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs.sub_container >= rhs.sub_container;
		}
	};
}

#endif