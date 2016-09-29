#pragma once
#include <iterator>

template<typename T>
class skip_iterator : public std::iterator<std::random_access_iterator_tag, T>
{
	T *pos;
	size_t step;
public:
	typedef std::iterator<std::random_access_iterator_tag, T> base_type;
	typedef typename base_type::difference_type difference_type;
	typedef typename base_type::reference reference;

	skip_iterator(T *pos, size_t step) : pos(pos), step(step) {}
	skip_iterator(const skip_iterator &i) : pos(i.pos), step(step) {}

	difference_type operator- (skip_iterator r)
	{
		return (pos - r.pos) / step;
	}
	skip_iterator operator+ (typename base_type::difference_type n)
	{
		return skip_iterator(pos + n * step);
	}
	skip_iterator operator++ ()
	{
		pos += step;
		return *this;
	}
	bool operator== (skip_iterator const &r)
	{
		return pos == r.pos;
	}
	bool operator!= (skip_iterator const &r)
	{
		return !(*this == r);
	}
	reference operator* ()
	{
		return *pos;
	}
};