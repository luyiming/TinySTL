/**
 * @file	SparseMatrix.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date 	2017-1-4
 */

#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

template <typename T>
struct Trituple {
	int row = 0, col = 0;
	T value;
	Trituple<T>() : row(0), col(0) {}
	Trituple<T>(int row, int col, T value) : row(row), col(col), value(value) {}
	Trituple<T>(const Trituple<T> &rhs) {
		row = rhs.row;
		col = rhs.col;
		value = rhs.value;
	}
	Trituple<T>& operator = (const Trituple<T> &rhs) {
		if (&rhs != this) {
			row = rhs.row;
			col = rhs.col;
			value = rhs.value;
		}
		return *this;
	}
};

template <typename T>
class SparseMatrix {
	template <typename U> friend ostream& operator << (ostream& out, const SparseMatrix<U> &rhs);
	template <typename U> friend SparseMatrix<U> operator + (const SparseMatrix<U>& lhs, const SparseMatrix<U>& rhs);
	template <typename U> friend SparseMatrix<U> operator - (const SparseMatrix<U>& lhs, const SparseMatrix<U>& rhs);
	template <typename U> friend SparseMatrix<U> operator * (const SparseMatrix<U>& lhs, const SparseMatrix<U>& rhs);
	template <typename U> friend SparseMatrix<U> operator * (const U& lhs, const SparseMatrix<U>& rhs);
	template <typename U> friend SparseMatrix<U> operator * (const SparseMatrix<U>& lhs, const U& rhs);
	template <typename U> friend SparseMatrix<U> operator / (const SparseMatrix<U>& lhs, const SparseMatrix<U>& rhs);
public:
	SparseMatrix();
	SparseMatrix(int row, int col);
	SparseMatrix(const SparseMatrix<T>& rhs);
	~SparseMatrix();
	T getValue(int row, int col) const;
	bool setValue(int row, int col, T value);
	bool contains(int row, int col) const;
	void insert(int row, int col, T value);
	int size() const;
	bool isEmpty() const;
	SparseMatrix<T> transpose() const;
	// SparseMatrix<T> inverse() const;
	SparseMatrix<T>& operator = (const SparseMatrix<T> rhs);
	void output_debug(int type) const {
		if (type == 1) {
			for (int i = 0; i < rowSize; i++) {
				for (int j = 0; j < colSize; j++) {
					cout << getValue(i, j) << "\t";
				}
				cout << endl;
			}
		}
		else if (type == 0)
		{
			cout << "Term\trow\tcol\tvalue" << endl;
			for (int i = 0; i < termSize; i ++) {
				cout << "Term " << i << ": " << smArray[i].row << "\t" <<
						smArray[i].col << "\t" << smArray[i].value << endl;
			}
		}
	}
private:
	int rowSize, colSize, termSize;
	vector<Trituple<T> > smArray;
	vector<int> rowStart;
};

#include "detail/SparseMatrix.impl.hpp"

#endif // SPARSE_MATRIX_HPP
