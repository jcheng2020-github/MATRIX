// Matrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Student Name: Junfu Cheng Student ID: 903968437 Florida Institute of Technology

#include <iostream>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<vector>
#include "Header.hpp"

using namespace std;

const short WIDTH = 8;
const short PRECISION = 2;


Matrix::Matrix()
{
    matrix.resize(0);
    initialize();
}

Matrix::Matrix(const vector<vector<double>>& data)
{
    matrix.resize(data.size());
    if (data.size() != 0)
       for (unsigned int row_label = 0;row_label < data.size();row_label++)
       {
          for(unsigned int col_label=0;col_label<data[0].size();col_label++)
             matrix[row_label].push_back(data[row_label][col_label]);
       }
    initialize();
}

//void display(const vector<vector<double>>& resultMatrix)
//{
//    for (unsigned int row_label = 0;row_label < resultMatrix.size();row_label++)
//    {
//        for (unsigned int col_label = 0;col_label < resultMatrix[0].size();col_label++)
//            cout << setw(WIDTH) << left << setprecision(PRECISION) << fixed << resultMatrix[row_label][col_label];
//        cout << endl;
//    }
//}

Status  Matrix::add(const Matrix& other)
{
    if (other.getMatrix().size() == matrix.size() && other.getMatrix()[0].size() == matrix[0].size())
    {
        for (unsigned int row_label = 0;row_label < matrix.size();row_label++)
        {
            for (unsigned int col_label = 0;col_label < matrix.size();col_label++)
            {
                matrix[row_label][col_label] += other.getMatrix()[row_label][col_label];
            }
        }
        return Status::NoError;
    }
    else
        return Status::DimensionError;
}

Status Matrix::subtract(const Matrix& other)
{
    if (other.getMatrix().size() == matrix.size() && other.getMatrix()[0].size() == matrix[0].size())
    {
        for (unsigned int row_label = 0;row_label < matrix.size();row_label++)
        {
            for (unsigned int col_label = 0;col_label < matrix.size();col_label++)
            {
                matrix[row_label][col_label] -= other.getMatrix()[row_label][col_label];
            }
        }
        return Status::NoError;
    }
    else
        return Status::DimensionError;
}

void Matrix::multiply(double scalar)
{
    for (unsigned int row_label = 0;row_label < matrix.size();row_label++)
    {
        for (unsigned int col_label = 0;col_label < matrix.size();col_label++)
        {
            matrix[row_label][col_label] *= scalar;
        }
    }
}

Status  Matrix::divide(double scalar)
{
    if (scalar == 0)
        return Status::DivideByZeroError;
    else
    {
        multiply(1 / scalar);
        return Status::NoError;
    }
}

Status  Matrix::multiply(const Matrix& other)
{
    vector<vector<double>> result;
    if (other.getMatrix()[0].size() == matrix.size())
    {
        result.resize(other.getMatrix().size());
        transpose();
        for (unsigned int row_label = 0;row_label < other.getMatrix().size();row_label++)
        {
            for (unsigned int col_label = 0;col_label < matrix.size();col_label++)
            {
                result[row_label].push_back(help.dotProduct(other.getMatrix()[row_label],
                                                            matrix[col_label]));
            }
        }
        set_Matrix(result);
        initialize();
        return Status::NoError;
    }
    else
        return Status::DimensionError;
}

void Matrix::transpose()
{
    vector<vector<double>> resultMatrix;
    resultMatrix.resize(matrix[0].size());
    for (unsigned int col_label = 0;col_label < matrix[0].size();col_label++)
    {
        for (unsigned int row_label = 0;row_label < matrix.size();row_label++)
            resultMatrix[col_label].push_back(matrix[row_label][col_label]);
    }
    set_Matrix(resultMatrix);
    initialize();
}

void Matrix::zero()
{
    for (unsigned int row_label = 0;row_label < matrix.size();row_label++)
    {
        for (unsigned int col_label = 0;col_label < matrix.size();col_label++)
        {
            matrix[row_label][col_label] += 0;
        }
    }
}

void Matrix::show() const
{
    for (unsigned int row_label = 0;row_label < matrix.size();row_label++)
    {
        for (unsigned int col_label = 0;col_label < matrix[0].size();col_label++)
            cout << setw(WIDTH) << left << setprecision(PRECISION) << fixed << matrix[row_label][col_label];
        cout << endl;
    }
}

double Matrix::getAt(int row, int column) const
{
    return matrix[row][column];
}

int Matrix::getRowSize() const
{
    return rowSize;
}

int Matrix::getColSize() const
{
    return colSize;
}

bool Matrix::isSquare() const
{
    if (colSize == rowSize)
        return 1;
    else
        return 0;
}

bool Matrix::hasSameDimensionAs(const Matrix& other)
{
    if (matrix.size() == 0)
        if (other.getRowSize() == 0)
            return 1;
        else
            return 0;
    if (matrix.size() == other.getRowSize() && matrix[0].size() == other.getColSize())
        return 1;
    else
        return 0;
}

double HelpingFunctions::dotProduct(const vector<double>& x, const vector<double>& y)
{
    if (x.size() == y.size())
    {
        double result = 0;
        for (unsigned int index = 0;index < x.size();index++)
            result += x[index] * y[index];
        return result;
    }
    else
        return nan("");
}

Matrix Matrix::getMinor(int row, int column)
{
    vector<vector<double>> resultMatrix;
    if (rowSize == 0)
    {
        Matrix result;
        return result;
    }
    resultMatrix.resize(rowSize - 1);
    int r = 0;
    for (int row_label = 0;row_label < rowSize;row_label++)
    {
        if (row_label == row)
            continue;
        for (int col_label = 0;col_label < colSize;col_label++)
        {
            if (col_label == column)
                continue;
            resultMatrix[r].push_back(matrix[row_label][col_label]);
        }
        r++;
    }
//    display(matrix);
//   display(resultMatrix);
    Matrix result(resultMatrix);
    return result;
}

double Matrix::getDeterminant()
{
    double result = 0;
    if (isSquare())
    {
        if (matrix.size())
        {
            if (matrix.size() == 1)
                return matrix[0][0];
            else
            for (int row_label = 0;row_label < matrix.size();row_label++)
            {
                Matrix MinorMatrix(getMinor(row_label, 0).getMatrix());
                result += matrix[row_label][0] * (((row_label + 2) % 2) ? (-1) : 1)
                    *MinorMatrix.getDeterminant();
            }
            return result;
        }
        else
            return nan("");
    }
    else
        return nan("");
}

void setElement(vector<vector<double>>& object, unsigned int r, double e)
{
    object[r].push_back(e);
}

void setMatrix(vector<vector<double>>& object, double a, double b, double c,
                                                double d, double e, double f,
                                                 double g, double h,double i)
{
    object.resize(3);
    setElement(object, 0, a); setElement(object, 0, b); setElement(object, 0, c);
    setElement(object, 1, d); setElement(object, 1, e); setElement(object, 1, f);
    setElement(object, 2, g); setElement(object, 2, h); setElement(object, 2, i);
}

int main()
{
    vector<vector<double>> object,object2;

    cout << "Group 1" << endl;
    setMatrix(object, 2, 3, 3,
                        5, 17, 4,
                          2, 8, 3);
    setMatrix(object2, 2, 5, 1,
                        2, 1, 7,
                          2, 5, 7);
    Matrix a(object),b(object2);
    cout<<"a.show()\n";
    a.show();
    cout << endl;
    cout<<"b.show()\n";
    b.show();
    a.add(b);
    cout<<"\na.add(b)\n";
    a.show();
    a.subtract(b);
    cout<<"\na.subtract(b)\n";
    a.show();
    a.multiply(4);
    cout << "\na.multiply(4)\n";
    a.show();
    a.divide(2);
    cout << "\na.divide(2)\n";
    a.show();
    a.transpose();
    cout << "\na.transpose()\n";
    a.show();
    cout << "\na.getAt(2, 1)\n"
    << endl << setprecision(PRECISION) << fixed <<a.getAt(2, 1) << endl
    << "\na.getRowSize()\n"
    << endl << setprecision(PRECISION) << fixed <<a.getRowSize() << endl
    << "\na.getColSize()\n"
    << endl << setprecision(PRECISION) << fixed <<a.getColSize() << endl
    << "\na.isSquare()\n"
    << endl << setprecision(PRECISION) << fixed << a.isSquare() << endl
    << "\na.hasSameDimensionAs(b)\n";
    cout << endl << setprecision(PRECISION) << fixed << a.hasSameDimensionAs(b) << endl;
    cout<<"\n\na.show()\n";
    a.show();
    cout<<"\nb.show()\n";
    b.show();
    cout<<"\n\na.getMinor(1, 1)\n";
    a.getMinor(1, 1).show();
    cout << endl << setprecision(PRECISION) << fixed << "\na.getDeterminant()\n"<< a.getDeterminant()<<endl;
    cout << endl << setprecision(PRECISION) << fixed << "b.getDeterminant()\n"<<b.getDeterminant()<<endl<<endl;
    cout<<"a.multiply(b)\n";
    a.multiply(b);
    a.show();
    a.zero();
    cout << "\na.zero()\n";
    a.show();

    cout << endl;
    for (unsigned t = 0;t < 45; t++)
    {
        cout << '*';
    }
    cout << endl;
    cout <<endl<< "\nGroup 2" << endl;
    vector<vector<double>> object3, object4;
    setMatrix(object3, 2, 3, 34,
                        5, 1, 4,
                            9, 8, 3);
    setMatrix(object4, 2, 5.3, 1,
                        2, 19, 7,
                         2, -12, 7);
    Matrix c(object3), d(object4);
    cout << "c.show()" << endl;
    c.show();
    cout << endl;
    cout << "d.show()" << endl;
    d.show();
    cout <<endl << setprecision(PRECISION) << fixed <<"\nc.getDeterminant()\n"<<  c.getDeterminant() << endl;
    cout << endl << setprecision(PRECISION) << fixed <<"\nd.getDeterminant()\n"<< d.getDeterminant() << endl ;
    c.multiply(d);
    cout<<"\nc.multiply(d)\n";
    c.show();
    return 0;
}
