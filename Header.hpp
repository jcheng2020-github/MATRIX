#include<vector>

using namespace std;

#ifndef Matrix_hpp
#define Matrix_hpp

enum class Status { NoError = 0, DivideByZeroError = 1, DimensionError = 2 };

class Matrix
{
public:
	Matrix();
	Matrix(const vector<vector<double>>& data);
	void initialize()
	{
		if (matrix.size() == 0)
		{
		    rowSize = 0;
		    colSize = 0;
		}
		else
		{
		    rowSize = matrix.size();
		    colSize = matrix[0].size();
		}
	}

	void set_Matrix(const vector<vector<double>>& data)
	{
		matrix.resize(0);
		matrix.resize(data.size());
		for (unsigned int row_label = 0;row_label < data.size();row_label++)
		{
			for (unsigned int col_label = 0;col_label < data[0].size();col_label++)
				matrix[row_label].push_back(data[row_label][col_label]);
		}
	}

	vector<vector<double>> getMatrix() const
	{
		return matrix;
	}

	Status add(const Matrix& other);
	Status subtract(const Matrix& other);
	void multiply(double scalar);
	Status multiply(const Matrix& other);
	Status divide(double scalar);
	void transpose();
	void zero();
	void show() const;
	double getAt(int row, int column) const;
	int getRowSize() const;
	int getColSize() const;
	bool isSquare() const;
	bool hasSameDimensionAs(const Matrix& other);
	Matrix getMinor(int row, int column);
	double getDeterminant();
private:
	vector<vector<double>> matrix;
	int rowSize;
	int colSize;
};

class HelpingFunctions
{
public:
	double dotProduct(const vector<double>& x, const vector<double>& y);
};

HelpingFunctions help;
#endif
