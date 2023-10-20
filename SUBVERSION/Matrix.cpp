//
//  Matrix.cpp
//  Matrix
//
//

#include "Matrix.hpp"
#include <vector>
#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include<cstdlib>

using namespace std;

const int WIDTH = 10;
const int PRECISION = 2;

Matrix::Matrix() { rowSize = 0;colSize = 0; }

Matrix::Matrix(const std::vector<std::vector<double>>& data) 
{ 
	matrix.resize(data.size());
	for (int row_label = 0;row_label < data.size();row_label++)
		for (int col_label = 0;col_label < data[row_label].size();col_label++)
		{
			matrix[row_label].push_back(data[row_label][col_label]);
		}
	rowSize = data.size();
	if (rowSize == 0)
		colSize = 0;
	else
		colSize = data[0].size();
}


Status Matrix::add(const Matrix& other)
{ 
	if ((other.getColSize() == colSize) && (other.getRowSize() == rowSize))
	{
		for (int row_label = 0;row_label < rowSize;row_label++)
			for (int col_label = 0;col_label < colSize;col_label++)
			{
				matrix[row_label][col_label] += other.getAt(row_label, col_label);
			}
		return Status::NoError;
	}
	else
		return Status::DimensionError;
}

Status Matrix::subtract(const Matrix& other) 
{ 
	if ((other.getColSize() == colSize) && (other.getRowSize() == rowSize))
	{
		for (int row_label = 0;row_label < rowSize;row_label++)
			for (int col_label = 0;col_label < colSize;col_label++)
			{
				matrix[row_label][col_label] -= other.getAt(row_label, col_label);
			}
		return Status::NoError;
	}
	else
		return Status::DimensionError;

}

Status Matrix::multiply(const Matrix& other) 
{ 
	if (other.getRowSize() == colSize)
	{
		vector<vector<double>> result;
		result.resize(rowSize);
		for(int row_label=0;row_label<rowSize;row_label++)
			for (int col_label = 0;col_label < other.getColSize();col_label++)
			{
				vector<double> vector1;
				vector<double> vector2;
				for (int di = 0;di < colSize;di++)
					vector1.push_back(matrix[row_label][di]);
				for (int di = 0;di < other.getRowSize();di++)
					vector2.push_back(other.getAt(di, col_label));
				HelpingFunctions a;
				result[row_label].push_back(a.dotProduct(vector1, vector2));
			}
		matrix.clear();
		matrix.resize(result.size());
		for (int row_label = 0;row_label < result.size();row_label++)
			for (int col_label = 0;col_label < result[0].size();col_label++)
				matrix[row_label].push_back(result[row_label][col_label]);
		rowSize = matrix.size();
		if (rowSize == 0)
			colSize = 0;
		else
			colSize = matrix[0].size();
		return Status::NoError;
	}
	else
		return Status::DimensionError;
}

Status Matrix::divide(double scalar)
{ 
	if(scalar==0)
		return Status::DivideByZeroError;
	else
	{
		for (int row_label = 0;row_label < rowSize;row_label++)
			for (int col_label = 0;col_label < colSize;col_label++)
				matrix[row_label][col_label] /= scalar;
		return Status::NoError;
	}
}

void Matrix::multiply(double scalar) 
{ 
	for (int row_label = 0;row_label < rowSize;row_label++)
		for (int col_label = 0;col_label < colSize;col_label++)
			matrix[row_label][col_label] *= scalar;	
}

void Matrix::transpose() 
{ 
	vector<vector<double>> result;
	result.resize(colSize);
	for (int row_label = 0;row_label < colSize;row_label++)
		for (int col_label = 0;col_label < rowSize;col_label++)
			result[row_label].push_back(matrix[col_label][row_label]);
		matrix.clear();
		matrix.resize(result.size());
		for (int row_label = 0;row_label < result.size();row_label++)
			for (int col_label = 0;col_label < result[0].size();col_label++)
				matrix[row_label].push_back(result[row_label][col_label]);
		rowSize = matrix.size();
		if (rowSize == 0)
			colSize = 0;
		else
			colSize = matrix[0].size();
}

void Matrix::zero() 
{ 
	for (int row_label = 0;row_label < rowSize;row_label++)
		for (int col_label = 0;col_label < colSize;col_label++)
			matrix[row_label][col_label] = 0;
}

void Matrix::show() const
{
	for (unsigned int row_label = 0;row_label < rowSize;row_label++)
	{
		for (unsigned int col_label = 0;col_label < colSize;col_label++)
			cout << setw(WIDTH) << left << setprecision(PRECISION) << fixed << matrix[row_label][col_label];
		cout << endl;
	}
}

double Matrix::getDeterminant() 
{
	double result = 0;
	if (colSize != rowSize)
		return nan("");
	else
	{
		if (rowSize == 1)
			return matrix[0][0];
		else
		{
			for (int row_label = 0;row_label < rowSize;row_label++)
				result += matrix[row_label][0] * getMinor(row_label, 0).getDeterminant() * pow(-1, (row_label + 0));
		}
		return result;
	}
}

double Matrix::getAt(int row, int column) const { return matrix[row][column]; }

int Matrix::getRowSize() const { return rowSize; }

int Matrix::getColSize() const { return colSize; }

bool Matrix::isSquare() const { if (colSize != rowSize)return 0;else return 1; }

bool Matrix::hasSameDimensionAs(const Matrix& other) {
	if ((other.getColSize() == colSize) && (other.getRowSize() == rowSize))return 1;
	else return 0;}

Matrix Matrix::getMinor(int row, int column) 
{ 
	vector<vector<double>> temp;
	temp.resize(rowSize - 1);
	int r = 0;
	for (int row_label = 0;row_label < rowSize;row_label++)
	{
		if (row_label == row)
			continue;
		else
		{
			for (int col_label = 0;col_label < colSize;col_label++)
			{
				if (col_label == column)
					continue;
				else
				{
					temp[r].push_back(matrix[row_label][col_label]);
				}
			}
			r++;
		}
	}
	Matrix result(temp);
	return result;
}

double HelpingFunctions::dotProduct(const std::vector<double>& x, const std::vector<double>& y)
{ 
	int dimension = x.size();
	double result = 0;
	for (int n = 0;n < dimension;n++)
		result += x[n] * y[n];
	return result;
}