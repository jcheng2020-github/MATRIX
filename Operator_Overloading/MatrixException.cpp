//
//  MatrixException.cpp
//  Matrix-2
//
//

#include <stdio.h>
#include <string>
#include <iostream>
#include "MatrixException.hpp"

std::string eventTable[] = {
    "No Error",
    "Successfully caught the divide by zero error!",
    "Successfully caught the dimensions' mismatch error!",
    "Successfully caught the matrix not being square error!",
    "Successfully caught the out of bounds error!"
};

MatrixException::MatrixException(unsigned int key, std::string filePath, unsigned int lineNumber){
    this->lineNumber = lineNumber;
    this->filePath = filePath;
    description = eventTable[key];
    errorKey = key;
    // Error Checking:
    // If key > number of error keys then description is Invalid Event Key
    // Otherswise use the key to extract the description from the eventTable array.
    
    // Save the key into errorKey.
    // Save the filePath into the filePath data member.
    // Save the lineNumber into the lineNumber data member.

}
std::string MatrixException::getFilePath()
{
    return filePath;
}

unsigned int MatrixException::getLineNumber()
{
    return lineNumber;
}

unsigned int MatrixException::getKey()
{
    return errorKey;
}

std::string MatrixException::getDescription()
{
    return description;
}
// Implement getKey(), getDescription(), getFilePath(), getLineNumber()
