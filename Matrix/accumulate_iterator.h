#pragma once
#include <iterator>

template<typename T, typename BinFunc>
class accumulate_iterator : public std::iterator<std::output_iterator_tag, T>
{
	T &ref_x;//�ۼ����ñ�������
	BinFunc bin_func;//�ۼ����ú�����ref_x = bin_func(ref_x, v)
public:
	accumulate_iterator(T &ref_x, BinFunc bin_func) : ref_x(ref_x), bin_func(bin_func) {}

	//ȥ���ò�����������
	accumulate_iterator operator*() { return *this; }

	//��ֵ����ʵ���ۼ�
	template<typename T0>
	T0 const& operator= (T0 const &v)
	{
		ref_x = bin_func(ref_x, v);
	}

	accumulate_iterator& operator++() { return *this; }
};

template<typename T, typename BinFunc>
accumulate_iterator<T, Bin_Func> accumulater(T &ref_x, Bin_Func bin_func)
{
	return accumulate_iterator<T, BinFunc>(ref_x, bin_func);
}