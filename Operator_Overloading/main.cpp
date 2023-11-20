//
//  main.cpp
//  Matrix-2
//
//  Created by Xavier Merino on 10/26/16.
//  Copyright © 2016 Xavier Merino. All rights reserved.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "Matrix.hpp"
#include "MatrixException.hpp"

TEST_CASE("Matrix: Operator + (NoError)"){
    enum { RowOne, RowTwo, RowThree };
    
    std::vector<std::vector<double>> data;
    data.resize(3);
    
    data[RowOne].push_back(1);
    data[RowOne].push_back(2);
    data[RowOne].push_back(3);
    data[RowTwo].push_back(4);
    data[RowTwo].push_back(5);
    data[RowTwo].push_back(6);
    data[RowThree].push_back(7);
    data[RowThree].push_back(8);
    data[RowThree].push_back(9);
    
    Matrix one = Matrix(data);
    Matrix two = Matrix(data);
    
    REQUIRE(one.getRowSize() == 3);
    REQUIRE(one.getColSize() == 3);
    REQUIRE(two.getRowSize() == 3);
    REQUIRE(two.getColSize() == 3);
    
    unsigned int errorKey = NoError;
    try {
        one + two;
    }
    catch(MatrixException& e) {
        errorKey = e.getKey();
    }
    
    REQUIRE(errorKey == NoError);
    
    for (int row = 0; row < one.getRowSize(); row++){
        for (int col = 0; col < one.getColSize(); col++){
            REQUIRE(one.getAt(row, col) == data[row][col] * 2);
        }
    }
}


TEST_CASE("Matrix: Operator + (Dimension Error)"){
    enum { RowOne, RowTwo, RowThree };
    
    std::vector<std::vector<double>> dataOne;
    std::vector<std::vector<double>> dataTwo;
    dataOne.resize(3);
    dataTwo.resize(2);
    
    dataOne[RowOne].push_back(1);
    dataOne[RowOne].push_back(2);
    dataOne[RowOne].push_back(3);
    dataOne[RowTwo].push_back(4);
    dataOne[RowTwo].push_back(5);
    dataOne[RowTwo].push_back(6);
    dataOne[RowThree].push_back(7);
    dataOne[RowThree].push_back(8);
    dataOne[RowThree].push_back(9);
    
    dataTwo[RowOne].push_back(1);
    dataTwo[RowOne].push_back(2);
    dataTwo[RowOne].push_back(3);
    dataTwo[RowTwo].push_back(4);
    dataTwo[RowTwo].push_back(5);
    dataTwo[RowTwo].push_back(6);
    
    Matrix one = Matrix(dataOne);
    Matrix two = Matrix(dataTwo);
    
    REQUIRE(one.getRowSize() == 3);
    REQUIRE(one.getColSize() == 3);
    REQUIRE(two.getRowSize() == 2);
    REQUIRE(two.getColSize() == 3);
    
    unsigned int errorKey = NoError;
    try {
        one + two;
    }
    catch(MatrixException& e) {
        errorKey = e.getKey();
    }

    REQUIRE(errorKey == DimensionError);
    
    for (int row = 0; row < one.getRowSize(); row++){
        for (int col = 0; col < one.getColSize(); col++){
            REQUIRE(one.getAt(row, col) == dataOne[row][col]);
        }
    }
}

TEST_CASE("Matrix: Operator - (NoError)"){
    enum { RowOne, RowTwo, RowThree };
    
    std::vector<std::vector<double>> data;
    data.resize(3);
    
    data[RowOne].push_back(1);
    data[RowOne].push_back(2);
    data[RowOne].push_back(3);
    data[RowTwo].push_back(4);
    data[RowTwo].push_back(5);
    data[RowTwo].push_back(6);
    data[RowThree].push_back(7);
    data[RowThree].push_back(8);
    data[RowThree].push_back(9);
    
    Matrix one(data);
    Matrix two(data);
    
    REQUIRE(one.getRowSize() == 3);
    REQUIRE(one.getColSize() == 3);
    REQUIRE(two.getRowSize() == 3);
    REQUIRE(two.getColSize() == 3);
    
    unsigned int errorKey = NoError;
    try {
        one - two;
    }
    catch(MatrixException& e) {
        errorKey = e.getKey();
    }
    
    REQUIRE(errorKey == NoError);
    
    for (int row = 0; row < one.getRowSize(); row++){
        for (int col = 0; col < one.getColSize(); col++){
            REQUIRE(one.getAt(row, col) == 0);
        }
    }
}

TEST_CASE("Matrix: Operator - (DimensionError)"){
    enum { RowOne, RowTwo, RowThree };
    
    std::vector<std::vector<double>> dataOne;
    std::vector<std::vector<double>> dataTwo;
    dataOne.resize(3);
    dataTwo.resize(2);
    
    dataOne[RowOne].push_back(1);
    dataOne[RowOne].push_back(2);
    dataOne[RowOne].push_back(3);
    dataOne[RowTwo].push_back(4);
    dataOne[RowTwo].push_back(5);
    dataOne[RowTwo].push_back(6);
    dataOne[RowThree].push_back(7);
    dataOne[RowThree].push_back(8);
    dataOne[RowThree].push_back(9);
    
    dataTwo[RowOne].push_back(1);
    dataTwo[RowOne].push_back(2);
    dataTwo[RowOne].push_back(3);
    dataTwo[RowTwo].push_back(4);
    dataTwo[RowTwo].push_back(5);
    dataTwo[RowTwo].push_back(6);
    
    Matrix one = Matrix(dataOne);
    Matrix two = Matrix(dataTwo);
    
    REQUIRE(one.getRowSize() == 3);
    REQUIRE(one.getColSize() == 3);
    REQUIRE(two.getRowSize() == 2);
    REQUIRE(two.getColSize() == 3);
    
    unsigned int errorKey = NoError;
    
    try {
        one - two;
    }
    catch(MatrixException& e) {
        errorKey = e.getKey();
    }

    REQUIRE(errorKey == DimensionError);
    
    for (int row = 0; row < one.getRowSize(); row++){
        for (int col = 0; col < one.getColSize(); col++){
            REQUIRE(one.getAt(row, col) == dataOne[row][col]);
        }
    }
}

TEST_CASE("Matrix: Operator *"){
    enum { RowOne, RowTwo, RowThree };
    
    std::vector<std::vector<double>> data;
    data.resize(3);
    
    data[RowOne].push_back(1);
    data[RowOne].push_back(2);
    data[RowOne].push_back(3);
    data[RowTwo].push_back(4);
    data[RowTwo].push_back(5);
    data[RowTwo].push_back(6);
    data[RowThree].push_back(7);
    data[RowThree].push_back(8);
    data[RowThree].push_back(9);
    
    Matrix one = Matrix(data);
    Matrix two = Matrix(data);
    
    REQUIRE(one.getRowSize() == 3);
    REQUIRE(one.getColSize() == 3);
    REQUIRE(two.getRowSize() == 3);
    REQUIRE(two.getColSize() == 3);
    
    one * 10.0;
    
    for (int row = 0; row < one.getRowSize(); row++){
        for (int col = 0; col < one.getColSize(); col++){
            REQUIRE(one.getAt(row, col) == data[row][col] * 10);
        }
    }
}

TEST_CASE("Testing dotProduct() - Dimensionality Exception"){
    std::vector<double> dataOne;
    std::vector<double> dataTwo;
    
    dataOne.push_back(1);
    dataOne.push_back(2);
    dataOne.push_back(3);
    
    dataTwo.push_back(9);
    dataTwo.push_back(8);
    dataTwo.push_back(7);
    dataTwo.push_back(1234);
    
    // Code to test addition error.
    unsigned int errorKey = NoError;
    try {
        double result = HelpingFunctions::dotProduct(dataOne, dataTwo);
    }
    catch(MatrixException& e) {
        errorKey = e.getKey();
    }
    
    REQUIRE(errorKey == DimensionError);
}

TEST_CASE("Testing Multiplication: DimensionError"){
    enum { RowOne, RowTwo, RowThree };
    
    std::vector<std::vector<double>> dataOne;
    std::vector<std::vector<double>> dataTwo;
    
    dataOne.resize(3);
    dataTwo.resize(1);
    
    dataOne[RowOne].push_back(1);
    dataOne[RowOne].push_back(2);
    dataOne[RowOne].push_back(3);
    dataOne[RowTwo].push_back(4);
    dataOne[RowTwo].push_back(5);
    dataOne[RowTwo].push_back(6);
    dataOne[RowThree].push_back(7);
    dataOne[RowThree].push_back(8);
    dataOne[RowThree].push_back(9);
    
    dataTwo[RowOne].push_back(9);
    dataTwo[RowOne].push_back(8);
    dataTwo[RowOne].push_back(7);
    
    Matrix one = Matrix(dataOne);
    Matrix two = Matrix(dataTwo);
    
    // Code to test addition error.
    unsigned int errorKey = NoError;
    try {
        one.multiply(two);
    }
    catch(MatrixException& e) {
        errorKey = e.getKey();
    }
    // Verify that the dimension error was successfully thrown and caught.
    REQUIRE(errorKey == DimensionError);
    
    for (int row = 0; row < one.getRowSize(); row++){
        for (int col = 0; col < one.getColSize(); col++){
            REQUIRE(one.getAt(row, col) == dataOne[row][col]);
        }
    }
}

TEST_CASE("Testing Division: DivideByZeroError"){
    enum { RowOne, RowTwo, RowThree };
    
    std::vector<std::vector<double>> dataOne;
    dataOne.resize(3);
    
    dataOne[RowOne].push_back(3);
    dataOne[RowOne].push_back(6);
    dataOne[RowOne].push_back(9);
    dataOne[RowTwo].push_back(12);
    dataOne[RowTwo].push_back(15);
    dataOne[RowTwo].push_back(18);
    dataOne[RowThree].push_back(21);
    dataOne[RowThree].push_back(24);
    dataOne[RowThree].push_back(27);
    
    Matrix one = Matrix(dataOne);
    
    unsigned int errorKey = NoError;
    
    // Attempt to divide by zero.
    try {
        one.divide(0);
    } catch( MatrixException& e) {
        // Set the error key.
        errorKey = e.getKey();
    }
    REQUIRE( errorKey == DivideByZeroError );
}

TEST_CASE("Testing getDeterminant(): Invalid Matrix"){
    enum { RowOne, RowTwo };
    
    std::vector<std::vector<double>> dataOne;
    dataOne.resize(2);
    
    dataOne[RowOne].push_back(5);
    dataOne[RowOne].push_back(4);
    dataOne[RowOne].push_back(7);
    dataOne[RowOne].push_back(-1);
    dataOne[RowTwo].push_back(4);
    dataOne[RowTwo].push_back(0);
    dataOne[RowTwo].push_back(10);
    
    // Code to test addition error.
    unsigned int errorKey = NoError;
    try {
        Matrix one = Matrix(dataOne);
    } catch(MatrixException& e) {
        errorKey = e.getKey();
    }
    // Verify that the dimension error was successfully thrown and caught.
    REQUIRE(errorKey == DimensionError);
}

TEST_CASE("Testing getDeterminant(): Not Square Matrix"){
    enum { RowOne, RowTwo };
    
    std::vector<std::vector<double>> dataOne;
    dataOne.resize(2);
    
    dataOne[RowOne].push_back(5);
    dataOne[RowOne].push_back(4);
    dataOne[RowOne].push_back(7);
    dataOne[RowOne].push_back(-1);
    dataOne[RowTwo].push_back(4);
    dataOne[RowTwo].push_back(0);
    dataOne[RowTwo].push_back(10);
    dataOne[RowTwo].push_back(8);
    
    // Try to create an invalid matrix.
    Matrix one = Matrix(dataOne);
    
    // Code to test addition error.
    unsigned int errorKey = NoError;
    try {
        double determinant = one.getDeterminant();
    } catch(MatrixException& e) {
        errorKey = e.getKey();
    }
    // Verify that the dimension error was successfully thrown and caught.
    REQUIRE(errorKey == MatrixNotSquareError);
}
