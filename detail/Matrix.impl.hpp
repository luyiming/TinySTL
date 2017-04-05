/**
 * @file	Matrix.impl.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date 	2017-1-4
 */
#ifndef MATRIX_IMPL_HPP
#define MATRIX_IMPL_HPP

#include "Matrix.hpp"
#include <cstring>
#include <iostream>

using namespace std;

Matrix::Matrix() {
	this->mat = NULL;
	this->row = 0;
	this->col = 0;
}

Matrix::Matrix(int r, int c) {
	if (r > 0 && c > 0) {
		this->row = r;
		this->col = c;
		this->mat = new double[r * c];
	}
	else {
		cerr << "error: row and col <= 0" << endl;
		Matrix();
	}
}

Matrix::Matrix(int r, int c, double val) {
	if (r > 0 && c > 0) {
		this->row = r;
		this->col = c;
		this->mat = new double[r * c];
		for (int r = 0; r < row; r++)
			for (int c = 0; c < col; c++)
				(*this)[r][c] = val;
	}
	else {
		cerr << "error: row and col <= 0" << endl;
		Matrix();
	}
}

Matrix::~Matrix()
{
	this->clear();
}

Matrix::Matrix(const Matrix& rhs)
{
	if (!rhs.isEmpty()) {
		this->row = rhs.row;
		this->col = rhs.col;
		this->mat = new double[row * col];
		memcpy(this->mat, rhs.mat, sizeof(double) * row * col);
	}
	else
		Matrix();
}

Matrix& Matrix::operator = (const Matrix& rhs)
{
	if (this == &rhs)
		return *this;
	this->row = rhs.row;
	this->col = rhs.col;
	if (this->mat != NULL)
		delete[]mat;
	this->mat = new double[row * col];
	memcpy(this->mat, rhs.mat, sizeof(double) * row * col);
	return *this;
}

double abs(double x) {
	return x > 0 ? x : -x;
}
bool operator == (const Matrix& lhs, const Matrix& rhs) {
	if (lhs.row == rhs.row && lhs.col == rhs.col) {
		for (int r = 0; r < lhs.row; ++r) {
			for (int c = 0; c < lhs.col; ++c) {
				if (abs(lhs[r][c] - rhs[r][c]) > 1e-6) {
					return false;
				}
			}
		}
		return true;
	}
	else
		return false;
}

Matrix operator + (const Matrix& lhs, const Matrix& rhs)
{
	Matrix res(lhs.row, lhs.col);
	if (lhs.row != rhs.row || lhs.col != rhs.col)
	{
		cerr << "matrix add not match" << endl;
		return res;
	}
	for (int r = 0; r < lhs.row; ++r)
		for (int c = 0; c < lhs.col; ++c)
			res[r][c] = lhs[r][c] + rhs[r][c];
	return res;
}

Matrix operator + (const double lhs, const Matrix& rhs)
{
	Matrix res(rhs.row, rhs.col);
	for (int r = 0; r < rhs.row; ++r)
		for (int c = 0; c < rhs.col; ++c)
			res[r][c] = lhs + rhs[r][c];
	return res;
}

Matrix operator + (const Matrix& lhs, const double rhs)
{
	Matrix res(lhs.row, lhs.col);
	for (int r = 0; r < lhs.row; ++r)
		for (int c = 0; c < lhs.col; ++c)
			res[r][c] = lhs[r][c] + rhs;
	return res;
}

Matrix operator - (const Matrix& lhs, const Matrix& rhs)
{
	Matrix res(lhs.row, lhs.col);
	if (lhs.row != rhs.row || lhs.col != rhs.col)
	{
		cerr << "matrix sub not match" << endl;
		return res;
	}
	for (int r = 0; r < lhs.row; ++r)
		for (int c = 0; c < lhs.col; ++c)
			res[r][c] = lhs[r][c] - rhs[r][c];
	return res;
}

Matrix operator - (const double lhs, const Matrix& rhs)
{
	Matrix res(rhs.row, rhs.col);
	for (int r = 0; r < rhs.row; ++r)
		for (int c = 0; c < rhs.col; ++c)
			res[r][c] = lhs - rhs[r][c];
	return res;
}

Matrix operator - (const Matrix& lhs, const double rhs)
{
	Matrix res(lhs.row, lhs.col);
	for (int r = 0; r < lhs.row; ++r)
		for (int c = 0; c < lhs.col; ++c)
			res[r][c] = lhs[r][c] - rhs;
	return res;
}

Matrix operator / (const Matrix& lhs, const Matrix& rhs)
{
	return lhs * rhs.inverse();
}

Matrix operator * (const double lhs, const Matrix& rhs)
{
	Matrix res(rhs.row, rhs.col);
	for (int r = 0; r < rhs.row; ++r)
		for (int c = 0; c < rhs.col; ++c)
			res[r][c] = lhs * rhs[r][c];
	return res;
}

Matrix operator * (const Matrix& lhs, const double rhs)
{
	Matrix res(lhs.row, lhs.col);
	for (int r = 0; r < lhs.row; ++r)
		for (int c = 0; c < lhs.col; ++c)
			res[r][c] = lhs[r][c] * rhs;
	return res;
}

Matrix operator * (const Matrix& lhs, const Matrix& rhs)
{
	Matrix res(lhs.row, rhs.col);
	if (lhs.col != rhs.row)
	{
		cerr << "matrix multiply not match" << endl;
		return res;
	}
	for (int r = 0; r < res.row; ++r) {
		for (int c = 0; c < res.col; ++c) {
			res[r][c] = 0.0;
			for (int k = 0; k < lhs.col; ++k)
				res[r][c] += (lhs[r][k] * rhs[k][c]);
		}
	}
	return res;
}

double* Matrix::operator [] (int index)
{
	if (this->mat == NULL) {
		cerr << "matrix has no value, index out of range" << endl;
		return NULL;
	}
	return &mat[index * col];
}

const double* Matrix::operator [] (int index) const
{
	if (this->mat == NULL) {
		cerr << "matrix has no value, index out of range" << endl;
		return NULL;
	}
	return &mat[index * col];
}

void Matrix::transpose()
{
	for (int r = 0; r < row; ++r) {
		for (int c = 0; c < r; ++c) {
			int t = (*this)[c][r];
			(*this)[c][r] = (*this)[r][c];
			(*this)[r][c] = t;
		}
	}
}

//������ʽ��ֵ��
double Matrix::det() const
{
	if (row != col) {
		cerr << "matrix should be n * n" << endl;
		return 0.0;
	}
	int n = row;
	if (n == 2)
		return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
	if (n < 2)
		return 0.0;
	double res = 0.0;
	for (int i = 0; i < n; i++)
	{
		Matrix temp(n - 1, n - 1);
		for (int r = 1; r < n; ++r)
		{
			for (int c = 0; c < i; ++c)
				temp[r - 1][c] = (*this)[r][c];
			for (int c = i + 1; c < n; ++c)
				temp[r - 1][c - 1] = (*this)[r][c];
		}
		if (i % 2 == 0)
			res = res + (*this)[0][i] * temp.det();
		else
			res = res - (*this)[0][i] * temp.det();
	}
	return res;
}

//���������� ������������ʽ��ֵ��������ʽ��ֵ
const Matrix Matrix::inverse() const
{
	if (this->row != this->col)
	{
		cerr << "inverse should be n * n" << endl;
		return Matrix();
	}
	int n = this->row;
	Matrix res(n, n);
	double resultSum = this->det();
	if (resultSum == 0)
	{
		cerr << "no inverse" << endl;
		return Matrix();
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; ++j)
		{
			Matrix temp(n - 1, n - 1);
			for (int r = 0; r < i; ++r)
			{
				for (int c = 0; c < j; ++c)
					temp[r][c] = (*this)[r][c];
				for (int c = j + 1; c < n; ++c)
					temp[r][c - 1] = (*this)[r][c];
			}
			for (int r = i + 1; r < n; ++r)
			{
				for (int c = 0; c < j; ++c)
					temp[r - 1][c] = (*this)[r][c];
				for (int c = j + 1; c < n; ++c)
					temp[r - 1][c - 1] = (*this)[r][c];
			}
			if ((i + j) % 2 == 0)
				res[j][i] = temp.det() / resultSum;
			else
				res[j][i] = -(temp.det() / resultSum);
		}
	}
	return res;
}

void Matrix::display()
{
	if (this->mat == NULL) {
		cout << "NULL" << endl;
		return;
	}
	cout << "row: " << this->row << "\t" << "col: " << this->col << endl;
	for (int r = 0; r < this->row; ++r) {
		for (int c = 0; c < this->col; ++c) {
			cout << (*this)[r][c] << " ";
		}
		cout << endl;
	}
}

double Matrix::dot() const {
	if (this->row != 1 && this->col != 1) {
		cerr << "only vertex has dot product" << endl;
		return 0.0;
	}
	double res = 0.0;
	if (this->row == 1) {
		for (int i = 0; i < this->col; i++) {
			res += ((*this)[0][i] * (*this)[0][i]);
		}
	}
	else {
		for (int i = 0; i < this->row; i++) {
			res += ((*this)[i][0] * (*this)[i][0]);
		}
	}
	return res;
}

double Matrix::dot(const Matrix& rhs) const {
	if (this->row == rhs.row && this->col == rhs.col) {
		if (this->row != 1 && this->col != 1) {
			cerr << "only vertex has dot product" << endl;
			return 0.0;
		}
		double res = 0.0;
		if (this->row == 1) {
			for (int i = 0; i < this->col; i++) {
				res += ((*this)[0][i] * rhs[0][i]);
			}
		}
		else {
			for (int i = 0; i < this->row; i++) {
				res += ((*this)[i][0] * rhs[i][0]);
			}
		}
		return res;
	}
	else {
		cerr << "vertex not match" << endl;
		return 0.0;
	}
}

void Matrix::resize(int r, int c)
{
	if (r <= 0 || c <= 0) {
		cerr << "row and col <= 0" << endl;
		return;
	}

	double *temp = new double[r * c];

	if (!this->isEmpty()) {
		int temp_row = r < this->row ? r : this->row;
		int temp_col = c < this->col ? c : this->col;
		for (int i = 0; i < temp_row; i++) {
			for (int j = 0; j < temp_col; j++) {
				temp[temp_col * i + j] = (*this)[i][j];
			}
		}
	}

	this->row = r;
	this->col = c;

	if (this->mat != NULL)
		delete[]mat;

	this->mat = temp;
}

void Matrix::clear()
{
	if (this->mat != NULL)
		delete[]mat;
	this->mat = NULL;
	this->row = 0;
	this->col = 0;
}

bool Matrix::isEmpty() const
{
	if (this->mat == NULL)
		return true;
	else
		return false;
}

#endif // MATRIX_IMPL_HPP
