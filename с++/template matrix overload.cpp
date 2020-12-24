#include "stdafx.h"
#include<iostream>
#include <fstream>
using namespace std;

template<typename __T>
class Matrix
{
private:
	int row;
	int col;
	__T **num;
public:
	Matrix(const int, const int);
	Matrix(const Matrix<__T>&);
	~Matrix();
	Matrix  operator% (const Matrix<__T>&);
	Matrix& operator= (const Matrix<__T>&);
	__T*    operator[](const int);
	template<typename T> friend std::ostream& operator<<(std::ostream&, const Matrix<T>&);
	template<typename T> friend std::istream& operator >> (std::istream&, const Matrix<T>&);
	void read_file();
	void write_file();
};

template<typename __T>
void Matrix<__T>::read_file()
{
	ifstream fin("input_file.txt");
	for (int i = 0; i<this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
			fin >> this->num[i][j];
	}
	fin.close();
}

template<typename __T>
void Matrix<__T>::write_file()
{
	ofstream fout("output_file.txt");
	for (int i = 0; i<this->row; ++i)
	{
		for (int j = 0; j<this->col; ++j)
			fout << num[i][j] << ((char)(j == col - 1) ? '\n' : ' ');
	}
	fout.close();
}

template<typename __T>
Matrix<__T>::Matrix(const int __row, const int __col)
{
	row = __row;
	col = __col;
	if (row>0 && col>0)
	{
		num = new __T*[row];
		for (int i = 0; i<row; ++i)
			num[i] = new __T[col];
	}
	else
	{
		row = 0;
		col = 0;
		num = NULL;
	}
	return;
}

template<typename __T>
Matrix<__T>::Matrix(const Matrix<__T>& __temp)
{
	row = __temp.row;
	col = __temp.col;
	if (row>0 && col>0)
	{
		num = new __T*[row];
		for (int i = 0; i<row; ++i)
			num[i] = new __T[col];
		for (int i = 0; i<row; ++i)
			for (int j = 0; j<col; ++j)
				num[i][j] = __temp.num[i][j];
	}
	else
	{
		row = 0;
		col = 0;
		num = NULL;
	}
	return;
}

template<typename __T>
Matrix<__T>::~Matrix()
{
	if (num)
	{
		for (int i = 0; i<row; ++i)
			delete[] num[i];
		delete[] num;
	}
	return;
}

template<typename __T>
Matrix<__T> Matrix<__T>::operator%(const Matrix<__T>& B)
{
	if (this->row == B.row&&this->col == B.col)
	{
		Matrix<__T> result(this->row, this->col);
		for (int i = 0; i < row; ++i)
		{
			__T max = B.num[i][0];
			for (int j = 1; j < col; ++j)
			{
				if (max < B.num[i][j])
					max = B.num[i][j];
			}
			for (int j = 0; j < col; ++j)
			{
				result.num[i][j] = this->num[i][j] / max;
			}
		}
		return result;
	}
	else
	{
		Matrix<__T> NullMatrix(0, 0);
		std::string WarningInformation = "No matching matrix";
		throw WarningInformation;
		return NullMatrix;
	}
}

template<typename __T>
Matrix<__T>& Matrix<__T>::operator=(const Matrix<__T>& B)
{
	if (num)
	{
		for (int i = 0; i<row; ++i)
			delete[] num[i];
		delete num;
	}
	row = B.row;
	col = B.col;
	if (row>0 && col>0)
	{
		num = new __T*[row];
		for (int i = 0; i<row; ++i)
			num[i] = new __T[col];
		for (int i = 0; i<row; ++i)
			for (int j = 0; j<col; ++j)
				num[i][j] = B.num[i][j];
	}
	else
	{
		row = 0;
		col = 0;
		num = NULL;
	}
	return *this;
}

template<typename __T>
__T* Matrix<__T>::operator[](const int addr)
{
	return addr >= this->row ? NULL : this->num[addr];
}


template<typename T>
std::ostream& operator<<(std::ostream& strm, const Matrix<T>& aim)
{
	for (int i = 0; i<aim.row; ++i)
	{
		for (int j = 0; j<aim.col; ++j)
			strm << aim.num[i][j] << ((char)(j == aim.col - 1) ? '\n' : ' ');
	}
	return strm;
}

template<typename T>
std::istream& operator >> (std::istream& strm, const Matrix<T>& aim)
{
	for (int i = 0; i<aim.row; ++i)
		for (int j = 0; j<aim.col; ++j)
			strm >> aim.num[i][j];
	return strm;
}


int main()
{
	int size;
	cout << "size = ";
	cin >> size;
	Matrix<int> matr(size, size);
	int select = 0;

	cout << "Init matrix from:" << endl;
	cout << "1)file" << endl;
	cout << "2)keyboard" << endl;
	cout << "Select: ";
	cin >> select;
	switch (select)
	{
	case 1: {
		matr.read_file();
		break;
	}
	case 2:
	{
		cin >> matr;
		break;
	}
	default:
		break;
	}

	cout << "Overload matrix[0][0] = 111" << endl << endl;
	matr[0][0] = 111;
	cout << "matrix1:" << endl << matr << endl;
	Matrix<int> matr2(size, size);
	matr2 = matr;
	cout << "matrix2:" << endl << matr2 << endl;
	cout << "Overload operator %" << endl << endl;
	
	matr = matr % matr2;

	cout << "Print matrix:" << endl;
	cout << "1)file" << endl;
	cout << "2)dispay" << endl;
	cout << "Select: ";
	cin >> select;

	switch (select)
	{
	case 1: {
		matr.write_file();
		break;
	}
	case 2:
	{
		cout << matr;
		break;
	}
	default:
		break;
	}



	system("pause");
	return 0;
}