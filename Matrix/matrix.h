#pragma once
#include "skip_iterator.h"
#include <algorithm>

template<typename T>
class matrix
{
public:
	//嵌套类型定义
	typedef T value_type;
	typedef T* iterator;//迭代全部数据
	typedef T* row_iterator;//迭代一行数据
	typedef skip_iterator<T> col_iterator;//迭代一列数据
	//只读迭代器类型定义
	typedef const T* const_iterator;
	typedef const T* const_row_iterator;
	typedef skip_iterator<const T> const_col_iterator;

private:
	T *data;//数据指针
	size_t n_row;//行数
	size_t n_col;//列数

public:
	//构造与析构
	matrix(size_t n_row, size_t n_col) : data(new T[n_row * n_col]), n_row(n_row), n_col(n_col) {}
	//辅助构造函数
	matrix(matrix const &m) : data(new T[m.n_row * m.n_col]), n_row(m.n_row), n_col(m.n_col)
	{
		std::copy(m.begin(), m.end(), begin());
	}

	template<typename Iterator>
	matrix(size_t n_row, size_t n_col, Iterator i) : data(new T[n_row * n_col]), n_row(n_row), n_col(n_col)
	{
		Iterator j = i;
		std::advance(j, n_row * n_col);
		std::copy(i, j, begin());
	}
	~matrix() { delete[] data; }

	iterator begin() { return data; }
	iterator end() { return data + n_row * n_col; }
	row_iterator row_begin(size_t n) { return fata + n * n_col; }
	row_iterator row_end(size_t n) { return row_begin(n) + n_col; }
	col_iterator col_begin(size_t n) { return col_iterator(data + n, n_col); }
	col_iterator col_end(size_t n) { return col_begin(n) + n_row; }

	const_iterator begin() const { return data; }
	const_iterator end() const { return data + n_row * n_col; }
	const_row_iterator row_begin(size_t n) const { return data + n * n_col; }
	const_row_iterator row_end(size_t n) const { return row_begin(n) + n_col; }
	const_col_iterator col_begin(size_t n) const { return const_col_iterator(data + n, n_col); }
	const_col_iterator col_end(size_t, n) const { return col_begin(n) + n_row; }

	size_t num_row() const { return n_row; }
	size_t num_col() const { return n_col; }

	T& operator() (size_t i, size_t j) { return data[i * n_col + j]; }
	T const& operator() (size_t i, size_t j) const { return data[i * n_col + j]; }

	matrix& operator= (matrix const &m)
	{
		if (&m == this) return *this;
		if (n_row * n_col < m.n_row * m.n_col)
		{
			delete[] data;
			data = new T[m.n_row * m.n_col];
		}
		n_row = m.n_row;
		n_col = m.n_col;
		std::copy(m.begin(), m.end(), begin());
	}
};