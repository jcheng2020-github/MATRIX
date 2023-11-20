//
//  Matrix.cpp
//  Matrix
//

#include <vector>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <math.h>
#include <limits> 
#include "Matrix.hpp"
#include "MatrixException.hpp"

using namespace std;
const int WIDTH = 10;
const int PRECISION = 2;
// Throw exception for invalid dimensions.
double HelpingFunctions::dotProduct(const std::vector<double> &x, const std::vector<double> &y){
    if (x.size() != y.size())
    {
        MatrixException e(2,__FILE__,__LINE__);
        throw e;
    }
    else
    {
        int dimension = x.size();
        double result = 0;
        for (int n = 0;n < dimension;n++)
            result += x[n] * y[n];
        return result;
    }
}

// Throw exception for not being a square matrix.
double Matrix::getDeterminant() {
    double result = 0;
    if (colSize != rowSize)
        {
            MatrixException e(3, __FILE__, __LINE__);
            throw e;
        }

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

Matrix Matrix::getMinor(unsigned int row, unsigned int column) {
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

Matrix::Matrix(){
    rowSize = 0;
    colSize = 0;
}

// Throw exception if dimensions dont match for all columns
Matrix::Matrix(const vector<vector<double>>& data){
    int temp = data[0].size();
    for (int i = 0;i < data.size();i++)
    {
        if (data[i].size() != temp)
        {
            MatrixException e(2, __FILE__, __LINE__);
            throw e;
        }
    }
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

// Throw exception if dimensions dont match
void Matrix::add(const Matrix& other){
    if ((other.getColSize() == colSize) && (other.getRowSize() == rowSize))
    {
        for (int row_label = 0;row_label < rowSize;row_label++)
            for (int col_label = 0;col_label < colSize;col_label++)
            {
                matrix[row_label][col_label] += other.getAt(row_label, col_label);
            }
        {
            MatrixException e(0, __FILE__, __LINE__);
            throw e;
        }
    }
    else
    {
        MatrixException e(2, __FILE__, __LINE__);
        throw e;
    }
}

// Throw exception if dimensions dont match
void Matrix::subtract(const Matrix& other){
    if ((other.getColSize() == colSize) && (other.getRowSize() == rowSize))
    {
        for (int row_label = 0;row_label < rowSize;row_label++)
            for (int col_label = 0;col_label < colSize;col_label++)
            {
                matrix[row_label][col_label] -= other.getAt(row_label, col_label);
            }
        {
            MatrixException e(0, __FILE__, __LINE__);
            throw e;
        }
    }
    else
    {
        MatrixException e(2, __FILE__, __LINE__);
        throw e;
    }
}

void Matrix::multiply(double scalar){
    for (int row_label = 0;row_label < rowSize;row_label++)
        for (int col_label = 0;col_label < colSize;col_label++)
            matrix[row_label][col_label] *= scalar;
}

// Throw exception if dimensions dont match
void Matrix::multiply(const Matrix &other){
    if (other.getRowSize() == colSize)
    {
        vector<vector<double>> result;
        result.resize(rowSize);
        for (int row_label = 0;row_label < rowSize;row_label++)
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
        {
            MatrixException e(0, __FILE__, __LINE__);
            throw e;
        }
    }
    else
    {
        MatrixException e(2, __FILE__, __LINE__);
        throw e;
    }

}

// Throw DivideByZeroError exception if attempt a division by zero
void Matrix::divide(double scalar){
    if (scalar == 0)
    {
        MatrixException e(1, __FILE__, __LINE__);
        throw e;
    }
    else
    {
        for (int row_label = 0;row_label < rowSize;row_label++)
            for (int col_label = 0;col_label < colSize;col_label++)
                matrix[row_label][col_label] /= scalar;
        {
            MatrixException e(0, __FILE__, __LINE__);
            throw e;
        }
    }
}

bool Matrix::hasSameDimensionAs(const Matrix &other){
    return (other.getRowSize() != rowSize || other.getColSize() != colSize) ? false : true;
}

void Matrix::show(void) const {
    for (unsigned int row_label = 0;row_label < rowSize;row_label++)
    {
        for (unsigned int col_label = 0;col_label < colSize;col_label++)
            cout << setw(WIDTH) << left << setprecision(PRECISION) << fixed << matrix[row_label][col_label];
        cout << endl;
    }
}

void Matrix::zero(void) {
    for (int row_label = 0;row_label < rowSize;row_label++)
        for (int col_label = 0;col_label < colSize;col_label++)
            matrix[row_label][col_label] = 0;
}

double Matrix::getAt(unsigned int x, unsigned int y) const {
    return matrix[x][y]; 
}

int Matrix::getRowSize() const { return rowSize; }
int Matrix::getColSize() const { return colSize; }
bool Matrix::isSquare() const { if (colSize != rowSize)return 0;else return 1; }
void Matrix::transpose(void) {
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
Matrix& Matrix::operator+(const Matrix& rhs) {
    if ((rhs.getColSize() == colSize) && (rhs.getRowSize() == rowSize))
    {
        for (int row_label = 0;row_label < rowSize;row_label++)
            for (int col_label = 0;col_label < colSize;col_label++)
            {
                matrix[row_label][col_label] += rhs.getAt(row_label, col_label);
            }
        {
            MatrixException e(0, __FILE__, __LINE__);
            throw e;
        }
    }
    else
    {
        MatrixException e(2, __FILE__, __LINE__);
        throw e;
    }

}

Matrix& Matrix::operator-(const Matrix& rhs){
    if ((rhs.getColSize() == colSize) && (rhs.getRowSize() == rowSize))
    {
        for (int row_label = 0;row_label < rowSize;row_label++)
            for (int col_label = 0;col_label < colSize;col_label++)
            {
                matrix[row_label][col_label] -= rhs.getAt(row_label, col_label);
            }
        {
            MatrixException e(0, __FILE__, __LINE__);
            throw e;
        }
    }
    else
    {
        MatrixException e(2, __FILE__, __LINE__);
        throw e;
    }

}

Matrix& Matrix::operator*(double rhs) {    
    for (int row_label = 0;row_label < rowSize;row_label++)
        for (int col_label = 0;col_label < colSize;col_label++)
            matrix[row_label][col_label] *= rhs;
    return *this;
}

Matrix& Matrix::operator*(const Matrix& rhs) {
    if (rhs.getRowSize() == colSize)
    {
        vector<vector<double>> result;
        result.resize(rowSize);
        for (int row_label = 0;row_label < rowSize;row_label++)
            for (int col_label = 0;col_label < rhs.getColSize();col_label++)
            {
                vector<double> vector1;
                vector<double> vector2;
                for (int di = 0;di < colSize;di++)
                    vector1.push_back(matrix[row_label][di]);
                for (int di = 0;di < rhs.getRowSize();di++)
                    vector2.push_back(rhs.getAt(di, col_label));
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
        {
            MatrixException e(0, __FILE__, __LINE__);
            throw e;
        }
    }
    else
    {
        MatrixException e(2, __FILE__, __LINE__);
        throw e;
    }


}

Matrix& Matrix::operator/(double rhs) {
    if (rhs== 0)
    {
        MatrixException e(1, __FILE__, __LINE__);
        throw e;
    }
    else
    {
        for (int row_label = 0;row_label < rowSize;row_label++)
            for (int col_label = 0;col_label < colSize;col_label++)
                matrix[row_label][col_label] /= rhs;
        {
            MatrixException e(0, __FILE__, __LINE__);
            throw e;
        }
    }

}

 
