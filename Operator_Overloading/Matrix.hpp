//
//  Matrix.hpp
//  Matrix
//
//  Created by Xavier Merino on 9/3/16.
//  Copyright © 2016 Xavier Merino. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix(); // Default Constructor
    Matrix(const std::vector<std::vector<double>>& data); // Overloaded Constructor
    void add(const Matrix& other); // Adds other matrix to this matrix.
    void subtract(const Matrix& other); // Subtract other matrix to this matrix.
    void multiply(double scalar); // Multiplies this matrix by scalar.
    void multiply(const Matrix& other); // Multiplies other matrix to this matrix.
    void divide(double scalar); // Divides this matrix by scalar.
    void transpose(); // Transposes the values of this matrix.
    void zero(); // Zeroes-out all elements of this matrix.
    void show() const; // Displays the formatted elements of this matrix to console.
    double getDeterminant(); // Computes and returns the determinant of this matrix.
    double getAt(unsigned int row, unsigned int column) const; // Retrives element at row, column.
    int getRowSize() const; // Returns the dimension of the row vectors.
    int getColSize() const; // Returns the dimension of the col vectors.
    bool isSquare() const; // Is the matrix a square matrix (r = c)?
    bool hasSameDimensionAs(const Matrix& other); // Compares matrices' dimensions
    Matrix getMinor(unsigned int row, unsigned int column); // Returns minor of element row, column.

    // Operator overloading.   
    Matrix& operator+(const Matrix& rhs);
    Matrix& operator-(const Matrix& rhs);
    Matrix& operator*(double rhs);
    Matrix& operator*(const Matrix& rhs);
    Matrix& operator/(double rhs);  
    
private:
    unsigned int rowSize; // Data member to store the row size of this matrix.
    unsigned int colSize; // Data member to store the column size of this matrix.
    std::vector<std::vector<double>> matrix; // The two-dimensional data structure to store data.
};

class HelpingFunctions {
public:
    // Class function to compute the dot product of two vectors of same dimension.
    static double dotProduct(const std::vector<double>& x, const std::vector<double>& y); 
};

#endif /* Matrix_hpp */
