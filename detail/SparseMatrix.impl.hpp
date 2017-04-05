/**
 * @file	SparseMatrix.impl.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date 	2017-1-4
 */

#ifndef SPARSE_MATRIX_IMPL_HPP
#define SPARSE_MATRIX_IMPL_HPP

#include "SparseMatrix.hpp"
#include <iostream>
#include <cassert>
#include <vector>

template <typename T>
SparseMatrix<T>::SparseMatrix() {
	rowSize = colSize = termSize = 0;
}

template <typename T>
SparseMatrix<T>::SparseMatrix(int row, int col) {
	rowSize = row;
	colSize = col;
	termSize = 0;
}

template <typename T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& rhs) {
	rowSize = rhs.rowSize;
	colSize = rhs.colSize;
	termSize = rhs.termSize;
	smArray = rhs.smArray;
	rowStart = rhs.rowStart;
}

template <typename T>
SparseMatrix<T>::~SparseMatrix() {
}

template <typename T>
SparseMatrix<T>& SparseMatrix<T>::operator = (const SparseMatrix<T> rhs) {
	if (this != &rhs) {
		rowSize = rhs.rowSize;
		colSize = rhs.colSize;
		termSize = rhs.termSize;
		smArray = rhs.smArray;
		rowStart = rhs.rowStart;
	}
	return *this;
}

template <typename T>
T SparseMatrix<T>::getValue(int row, int col) const {
	for (int i = 0; i < termSize; i++) {
		if (smArray[i].row == row && smArray[i].col == col) {
			return smArray[i].value;
		}
		if (smArray[i].row > row || (smArray[i].row == row && smArray[i].col > col)) {
			return 0;
		}
	}
	return 0;
}

template <typename T>
bool SparseMatrix<T>::setValue(int row, int col, T value) {
	for (int i = 0; i < termSize; i++) {
		if (smArray[i].row == row && smArray[i].col == col) {
			smArray[i].value = value;
			return true;
		}
		if (smArray[i].row > row || (smArray[i].row == row && smArray[i].col > col)) {
			return false;
		}
	}
	return false;
}

template <typename T>
bool SparseMatrix<T>::contains(int row, int col) const {
	for (int i = 0; i < termSize; i++) {
		if (smArray[i].row == row && smArray[i].col == col) {
			return true;
		}
		if (smArray[i].row > row || (smArray[i].row == row && smArray[i].col > col)) {
			return false;
		}
	}
	return false;
}

template <typename T>
int SparseMatrix<T>::size() const {
	return termSize;
}

template <typename T>
bool SparseMatrix<T>::isEmpty() const {
	return termSize == 0;
}

template <typename T>
void SparseMatrix<T>::insert(int row, int col, T value) {
	Trituple<T> m(row, col, value);
	if (contains(row, col)) {
		setValue(row, col, value);
		return;
	}
	smArray.push_back(Trituple<T>());
	int i;
	for (i = termSize; i > 0; i--) {
		if (smArray[i - 1].row < row)
			break;
		else if (smArray[i - 1].row == row && smArray[i - 1].col < col)
			break;
		smArray[i] = smArray[i - 1];
	}
	smArray[i] = m;
	termSize++;
	row++;
	col++;
	if (row > rowSize)
		rowSize = row;
	if (col > colSize)
		colSize = col;
}


template <typename T>
SparseMatrix<T> SparseMatrix<T>::transpose() const {
	SparseMatrix<T> res(*this);
	res.rowSize = colSize;
	res.colSize = rowSize;
	int *rowSizeArray = new int[colSize];
	int *rowStartArray = new int[colSize];
	if (termSize > 0) {
		for (int i = 0; i < colSize; i++) {
			rowSizeArray[i] = 0;
		}
		for (int i = 0; i < termSize; i++) {
			rowSizeArray[smArray[i].col]++;
		}
		rowStartArray[0] = 0;
		for (int i = 1; i < colSize; i++) {
			rowStartArray[i] = rowStartArray[i - 1] + rowSizeArray[i - 1];
		}
		for (int i = 0; i < termSize; i++) {
			int rowNumber = rowStartArray[smArray[i].col]++;
			res.smArray[rowNumber] = smArray[i];
			res.smArray[rowNumber].row = smArray[i].col;
			res.smArray[rowNumber].col = smArray[i].row;
		}
	}
	delete[] rowSizeArray;
	delete[] rowStartArray;
	return res;
}

template <typename T>
ostream& operator << (ostream& out, const SparseMatrix<T> &rhs) {
	for (int i = 0; i < rhs.rowSize; i++) {
		for (int j = 0; j < rhs.colSize; j++) {
			out << rhs.getValue(i, j) << " ";
		}
		out << endl;
	}
	return out;
}

template <typename T>
 SparseMatrix<T> operator + (const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	 SparseMatrix<T> res(lhs);
	 //TODO: implement
	 return res;
 }

template <typename T>
 SparseMatrix<T> operator - (const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	 SparseMatrix<T> res(lhs);
	 //TODO: implement
	 return res;
 }

template <typename T>
 SparseMatrix<T> operator * (const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	 SparseMatrix<T> res(lhs);
	 //TODO: implement
	 return res;
 }

template <typename T>
 SparseMatrix<T> operator * (const T& lhs, const SparseMatrix<T>& rhs) {
	 SparseMatrix<T> res(lhs);
	 //TODO: implement
	 return res;
 }

template <typename T>
 SparseMatrix<T> operator * (const SparseMatrix<T>& lhs, const T& rhs) {
	 SparseMatrix<T> res(lhs);
	 //TODO: implement
	 return res;
 }

template <typename T>
 SparseMatrix<T> operator / (const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	 SparseMatrix<T> res(lhs);
	 //TODO: implement
	 return res;
 }


#endif // SPARSE_MATRIX_IMPL_HPP
