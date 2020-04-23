// DllMatrix.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"
#include "DllMatrix.h"


// This is an example of an exported variable
DLLMATRIX_API int nDllMatrix=0;

// This is an example of an exported function.
DLLMATRIX_API int fnDllMatrix(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see DllMatrix.h for the class definition
CDllMatrix::CDllMatrix()
{
	return;
}

CDllMatrix::CDllMatrix(size_t rows, size_t columns)
{
	this->rows = rows;
	this->columns = columns;
	if (rows <= 0 || columns <= 0) throw DimensionException();
	this->matrix = new short int*[rows];
	for (size_t i = 0; i < this->rows; i++)
		this->matrix[i] = new short int[columns];
}

CDllMatrix::CDllMatrix(const CDllMatrix& m) : CDllMatrix(m.rows, m.columns)
{
	for (size_t i = 0; i < m.rows; i++)
	{
		for (size_t j = 0; j < m.columns; j++)
			this->matrix[i][j] = m.matrix[i][j];
	}
}

CDllMatrix::CDllMatrix(std::initializer_list<std::initializer_list<short int>> list)
{
	this->rows = list.size();
	size_t columns = (*list.begin()).size();
	for (std::initializer_list<std::initializer_list<short int>>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		if (iter->size() != columns) throw DimensionException();
	}
	this->columns = columns;
	size_t i = -1;
	matrix = new short int*[this->rows];
	for (std::initializer_list<short int> list_columns : list)
	{
		matrix[++i] = new short int[this->columns];
		size_t j = 0;
		for (short int value : list_columns)
		{
			matrix[i][j] = value;
			j += 1;
		}
	}
}

CDllMatrix::~CDllMatrix()
{
	for (size_t i = 0; i < this->rows; i++)
		delete[] this->matrix[i];
	delete[] this->matrix;
}

void CDllMatrix::setRows(const size_t& rows_count)
{
	this->rows = rows_count;
}

void CDllMatrix::setColumns(const size_t& colunms_count)
{
	this->columns = colunms_count;
}

size_t CDllMatrix::getRows() const
{
	return this->rows;
}

size_t CDllMatrix::getColumns() const
{
	return this->columns;
}

CDllMatrix& CDllMatrix::operator=(const CDllMatrix& m)
{
	if (this != &m)
	{
		this->rows = m.rows;
		this->columns = m.columns;
		this->matrix = new short int*[this->rows];
		for (size_t i = 0; i < this->rows; i++)
		{
			this->matrix[i] = new short int[this->columns];
			for (size_t j = 0; j < this->columns; j++)
				this->matrix[i][j] = m.matrix[i][j];
		}
	}
	return *this;
}

CDllMatrix& CDllMatrix::operator+=(const CDllMatrix& m)
{
	if (this->rows != m.rows || this->columns != m.columns) throw DimensionException();

	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < this->columns; j++)
			this->matrix[i][j] += m.matrix[i][j];
	}
	return *this;
}

CDllMatrix& CDllMatrix::operator-=(const CDllMatrix& m)
{
	if (this->rows != m.rows || this->columns != m.columns) throw DimensionException();

	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < this->columns; j++)
			this->matrix[i][j] -= m.matrix[i][j];
	}
	return *this;
}

CDllMatrix& CDllMatrix::operator*=(const short int& value)
{
	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < this->columns; j++)
			this->matrix[i][j] *= value;
	}
	return *this;
}

DLLMATRIX_API CDllMatrix operator*(const CDllMatrix& m, const short int& value)
{
	CDllMatrix res(m);
	res *= value;
	return res;
}

DLLMATRIX_API CDllMatrix operator*(const short int& value, const CDllMatrix& m)
{
	return CDllMatrix(m) * value;
}

DLLMATRIX_API std::istream& operator >> (std::istream& stream, CDllMatrix& m)
{
	size_t rows, columns;
	stream >> rows >> columns;
	if (rows <= 0 || columns <= 0) throw DimensionException();
	if (m.rows != rows || m.columns != columns)
	{
		m = CDllMatrix(rows, columns);
	}

	for (size_t i = 0; i < m.rows; i++)
	{
		for (size_t j = 0; j < m.columns; j++)
			stream >> m.matrix[i][j];
	}
	return stream;
}

DLLMATRIX_API std::ostream& operator<<(std::ostream& stream, const CDllMatrix& m)
{
	stream << m.rows << " " << m.columns << '\n';

	for (size_t i = 0; i < m.rows; i++)
	{
		for (size_t j = 0; j < m.columns; j++)
		{
			stream << m.matrix[i][j];
			if (j != m.columns - 1) stream << " ";
		}
		if (i != m.rows - 1) stream << '\n';
	}

	return stream;
}

bool CDllMatrix::operator==(const CDllMatrix& m)
{
	if (m.columns != this->columns || m.rows != this->rows) return false;
	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < this->columns; j++)
		{
			if (this->matrix[i][j] != m.matrix[i][j])
				return false;
		}
	}
	return true;
}

bool CDllMatrix::operator!=(const CDllMatrix& m)
{
	return !(*this == m);
}

short int*& CDllMatrix::operator[](const size_t& index) const
{
	if (index < 0 || index > this->rows) throw DimensionException();
	return this->matrix[index];
}

DLLMATRIX_API CDllMatrix operator+(const CDllMatrix& m1, const CDllMatrix& m2)
{
	if (m1.columns != m2.columns || m1.rows != m2.rows) throw DimensionException();

	CDllMatrix res(m1);

	res += m2;
	return res;
}

DLLMATRIX_API CDllMatrix operator-(const CDllMatrix& m1, const CDllMatrix& m2)
{
	if (m1.columns != m2.columns || m1.rows != m2.rows) throw DimensionException();

	CDllMatrix res(m1);

	res -= m2;
	return res;
}

