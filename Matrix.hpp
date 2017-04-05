/**
 * @file	Matric.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date 	2017-1-4
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdlib>

class Matrix
{
private:
	double *mat = NULL;
	int row = 0, col = 0;

public:
	Matrix();
	~Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, double val);
	Matrix(const Matrix& rhs);

	Matrix& operator = (const Matrix& rhs);
	friend bool  operator == (const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator + (const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator + (const Matrix& lhs, const double  rhs);
	friend Matrix operator + (const double  lhs, const Matrix& rhs);
	friend Matrix operator - (const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator - (const Matrix& lhs, const double  rhs);
	friend Matrix operator - (const double  lhs, const Matrix& rhs);
	friend Matrix operator / (const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator * (const double  lhs, const Matrix& rhs);
	friend Matrix operator * (const Matrix& lhs, const double  rhs);
	friend Matrix operator * (const Matrix& lhs, const Matrix& rhs);
	double* operator [] (int index);
	const double* operator [] (int index) const;

	void transpose();
	const Matrix inverse() const;
	double det() const;
	double dot() const;
	double dot(const Matrix& rhs) const;

	bool isEmpty() const;
	void resize(int r, int c);
	void clear();
	void display();
};

#include "detail/Matrix.impl.hpp"

#endif // MATRIX_HPP
