//
//  Matrix.hpp
//  Matrix-Student
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <vector>

enum Status { NoError=0, DivideByZeroError=1, DimensionError=2 };
class Matrix {
    
public:
    Matrix();

    Matrix(const std::vector<std::vector<double>>& data);
    
    Status add(const Matrix& other);
    
    Status subtract(const Matrix& other);
    
    Status multiply(const Matrix& other);
    
    Status divide(double scalar);
    
    void multiply(double scalar);
    
    void transpose();
    
    void zero();
    
    void show() const;
    
    double getDeterminant();
    
    double getAt(int row, int column) const;
    
    int getRowSize() const;
    
    int getColSize() const;
    
    bool isSquare() const;
    
    bool hasSameDimensionAs(const Matrix& other);
    
    Matrix getMinor(int row, int column);
    
private:
    
    int rowSize;
    
    int colSize;
    
    std::vector<std::vector<double>> matrix;

};

class HelpingFunctions {
public:
    static double dotProduct(const std::vector<double>& x, const std::vector<double>& y);
};

#endif /* Matrix_hpp */
