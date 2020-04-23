// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLLMATRIX_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLLMATRIX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLLMATRIX_EXPORTS
#define DLLMATRIX_API __declspec(dllexport)
#else
#define DLLMATRIX_API __declspec(dllimport)
#endif

struct DLLMATRIX_API DimensionException {
	char message[80];
	DimensionException() { strcpy_s(message, "Bad dimensions"); }
};


// This class is exported from the DllMatrix.dll

// 3.10. Матрица переменной размерности (тип элемента short int)
class DLLMATRIX_API CDllMatrix {
private:

	size_t rows;
	size_t columns;
	short int** matrix;

public:
	CDllMatrix(void);
	CDllMatrix(size_t rows, size_t columns);
	CDllMatrix(const CDllMatrix& m);
	CDllMatrix(std::initializer_list<std::initializer_list<short int>> list);
	virtual ~CDllMatrix();

	size_t getRows() const;
	void setRows(const size_t& rows_count);

	size_t getColumns() const;
	void setColumns(const size_t& columns_count);

	short int*& operator[](const size_t& index) const;

	CDllMatrix& operator=(const CDllMatrix& m);

	bool operator==(const CDllMatrix& m);
	bool operator!=(const CDllMatrix& m);

	CDllMatrix& operator+=(const CDllMatrix& m);
	CDllMatrix& operator-=(const CDllMatrix& m);
	CDllMatrix& operator*=(const short int& value);

	friend DLLMATRIX_API CDllMatrix operator+(const CDllMatrix& m1, const CDllMatrix& m2);
	friend DLLMATRIX_API CDllMatrix operator-(const CDllMatrix& m1, const CDllMatrix& m2);

	friend DLLMATRIX_API CDllMatrix operator*(const CDllMatrix& m, const short int& value);
	friend DLLMATRIX_API CDllMatrix operator*(const short int& value, const CDllMatrix& m);

	friend DLLMATRIX_API std::istream& operator >> (std::istream& stream, CDllMatrix& m);
	friend DLLMATRIX_API std::ostream& operator<<(std::ostream& stream, const CDllMatrix& m);

	// TODO: add your methods here.
};

extern DLLMATRIX_API int nDllMatrix;

DLLMATRIX_API int fnDllMatrix(void);
