#include "matrix.h"

namespace matrix
{
#define _EXPLICIT_DEFINE(CT) template class Matrix<CT>
	_EXPLICIT_DEFINE(char);
	_EXPLICIT_DEFINE(int);
	_EXPLICIT_DEFINE(float);
	_EXPLICIT_DEFINE(double);
#undef _EXPLICIT_DEFINE

	template<typename _Tp>
	Matrix<_Tp>::Matrix() : cols_(0), rows_(0)
	{
		creat(cols_, rows_);
	}

	template<typename _Tp>
	Matrix<_Tp>::Matrix(uint32_t cols, uint32_t rows) : cols_(cols), rows_(rows)
	{
		creat(cols_, rows_);
	}

	template<typename _Tp>
	Matrix<_Tp>::~Matrix()
	{
		destroyArry(_data);
	}

	template<typename _Tp>
	void Matrix<_Tp>::creat(uint32_t cols, uint32_t rows)
	{
		destroyArry(_data);
		this->cols_ = cols;
		this->rows_ = rows;
		_data = new type_pointer[cols_];
		for (uint32_t i = 0; i < cols_; i++)
		{
			_data[i] = new type[rows_]{ 0 };
		}
	}

	template<typename _Tp>
	void  Matrix<_Tp>::destroyArry(type_pointer*& p)
	{
		
		if (p == nullptr)
			return;
		for (uint32_t i = 0; i < cols_; i++)
			delete[]p[i];
		delete[]p;
		p = nullptr;
		rows_ = cols_ = 0;
	}


	template<typename _Tp>
	void Matrix<_Tp>::eye()
	{
		uint32_t min_ = cols_ > rows_ ? rows_ : cols_;
		for (uint32_t i = 0; i < min_; i++)
		{
			_data[i][i] = 1;
		}
	}

	template<typename _Tp>
	void Matrix<_Tp>::resize(uint32_t cols, uint32_t rows)
	{
		//destroyArry(_data);
		creat(cols, rows);
	}

	template<typename _Tp> Matrix<_Tp>
	Matrix<_Tp>::ones(uint32_t cols, uint32_t rows)
	{
		Matrix<_Tp> m;
		m.destroyArry(m._data);
		m.creat(cols, rows);
		m.fill(1);
		return m;
	}

	template<typename _Tp>void
		Matrix<_Tp>::fill(type numb)
	{
		for (uint32_t i = 0; i < cols_; i++)
			for (uint32_t j = 0; j < rows_; j++)
				this->_data[i][j] = numb;
	}

	template<typename _Tp>
	Matrix<_Tp>& Matrix<_Tp>::operator=(const Matrix& m)
	{
		if (this != &m)
		{
			if (this->cols_ != m.cols_ || this->rows_ != m.rows_)
			{
				creat(m.cols_, m.rows_);
			}
			for (uint32_t i = 0; i < m.cols_; i++)
				for (uint32_t j = 0; j < m.rows_; j++)
				{
					this->_data[i][j] = m._data[i][j];
				}

		}
		return *this;
	}

	template<typename _Tp>
	Matrix<_Tp> Matrix<_Tp>::operator*(const Matrix& m)
	{
		if (this->rows_ != m.cols_)
		{
			throw("error:Matrix mutipul rows do not equal cols");
		}
		Matrix res(this->cols_, m.rows_);
		for (uint32_t i = 0; i < this->cols_; i++)
			for (uint32_t j = 0; j < m.rows_; j++)
				for (uint32_t k = 0; k < this->rows_; k++)
					res._data[i][j] += this->_data[i][k] * m._data[k][j];

		return res;
	}

	template<typename _Tp>
	Matrix<_Tp> Matrix<_Tp>::operator-(const Matrix& m)
	{
		if (this->cols_ != m.cols_ || this->rows_ != m.rows_)
		{
			throw("error:Matrix mutipul rows do not equal cols");
		}
		Matrix res(this->cols_, m.rows_);
		for (uint32_t i = 0; i < this->cols_; i++)
			for (uint32_t j = 0; j < m.rows_; j++)
			{
				res[i][j] = this->_data[i][j] - m._data[i][j];
			}

		return res;
	}

	Matrix<double> TMatrix::toMatrix()
	{
		Matrix<double> res(this->cols(), this->rows());
		for (size_t i = 0; i < this->cols(); i++)
		{
			for (size_t j = 0; j < this->rows(); j++)
			{
				res[i][j] = this->_data[i][j];
			}
		}
		return res;
	}


#define _EXPLICIT_DEFINE(CT) template Matrix<CT> operator*(const CT& val, const Matrix<CT>& m)
	_EXPLICIT_DEFINE(char);
	_EXPLICIT_DEFINE(int);
	_EXPLICIT_DEFINE(float);
	_EXPLICIT_DEFINE(double);
#undef _EXPLICIT_DEFINE


	template<typename _Tp>
	Matrix<_Tp> operator*(const _Tp& val, const Matrix<_Tp>& m)
	{
		Matrix res(m.cols_, m.rows_);
		for (uint32_t i = 0; i < m.cols_; i++)
			for (uint32_t j = 0; j < m.rows_; j++)
				res._data[i][j] = m._data[i][j] * val;
		return res;
	}




	/*TMatrix& TMatrix::operator=(const TMatrix& tm)
	{
		if (this != &tm)
		{
			for (uint32_t i = 0; i < 4; i++)
				for (uint32_t j = 0; j < 4; j++)
				{
					this->_data[i][j] = tm._data[i][j];
				}
		}
		return *this;
	}*/

}
