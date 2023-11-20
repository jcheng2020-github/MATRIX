//
//  MatrixException.hpp
//  Matrix-2
//
//  Created by Xavier Merino on 10/26/16.
//  Copyright © 2016 Xavier Merino. All rights reserved.
//

#ifndef MatrixException_hpp
#define MatrixException_hpp

#include <string>

enum { NoError, DivideByZeroError, DimensionError, MatrixNotSquareError, OutOfRangeError, NumOfErrorKeys };

class MatrixException {

public:
    MatrixException(unsigned int errorKey, std::string filePath, unsigned int lineNumber);
    std::string getDescription();
    std::string getFilePath();
    unsigned int getLineNumber();
    unsigned int getKey();

private:
    std::string description;
    std::string filePath;
    unsigned int lineNumber;
    unsigned int errorKey;
    
};

#endif
