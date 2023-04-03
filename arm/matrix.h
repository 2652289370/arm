#pragma once
#include <iostream>
#include<memory>


namespace matrix
{
	template<typename _Tp>
	class Matrix
	{
	public:
		using type = _Tp;
		using type_pointer = _Tp*;
		typedef std::shared_ptr<Matrix<_Tp>> Ptr;
		friend class TMatrix;
	private:
		
		uint32_t cols_, rows_;
		type_pointer* _data = nullptr;
	public:

		type_pointer const operator[](size_t col)
		{
			return _data[col];
		}
		Matrix();
		Matrix(uint32_t cols, uint32_t rows);
	
		Matrix(const Matrix<_Tp>& m)
		{
			if (m.cols_ != this->cols_ || m.rows_ != this->rows_)
			{
				creat(m.cols_, m.rows_);
			}
			for (uint32_t i = 0; i < m.cols_; i++)
				for (uint32_t j = 0;  j < m.rows_;  j++)
					this->_data[i][j] = m._data[i][j];
			
		}
		/*Matrix(Matrix<_Tp>&& m):_data(std::move(m._data)), cols_(m.cols_), rows_(m.rows_)
		{
			m._data = nullptr;
		}*/
		Matrix(uint32_t cols, uint32_t rows, const type_pointer & data)
		{
			creat(rows, cols);
			for (uint32_t i = 0; i < cols_; i++)
				for (uint32_t j = 0; j < rows_; j++)
					this->_data[i][j] = data[i * rows_ + j];
		}
		~Matrix();

		/**
		 * @brief 重新构建矩阵大小
		 * @param cols 行数
		 * @param rows 列数
		*/
		void resize(uint32_t cols, uint32_t rows);
		/**
		 * @brief 生成元素为1的矩阵
		 * @param cols 行数
		 * @param rows 列数
		*/
		static Matrix ones(uint32_t cols, uint32_t rows);
		/**
		 * @brief 获取行数
		*/
		uint32_t cols() const { return cols_; }
		/**
		 * @brief 获取列数
		*/
		uint32_t rows() const { return rows_; }

		/**
		 * @brief 生成单位矩阵
		*/
		void eye();

		friend Matrix operator*(const _Tp& val, const Matrix& m);

		Matrix operator*(const Matrix& m);

		Matrix operator*(const _Tp& val)
		{
			Matrix res(this->cols_, this->rows_);
			for (uint32_t i = 0; i < this->cols_; i++)
				for (uint32_t j = 0; j < this->rows_; j++)
					res._data[i][j] = this->_data[i][j] * val;
			return res;
		}

		Matrix& operator=(const Matrix& m);

		Matrix operator-(const Matrix& m);

		friend std::ostream& operator<<(std::ostream& out, const Matrix& m)
		{
			for (uint32_t i = 0; i < m.cols_; i++)
			{
				for (uint32_t j = 0; j < m.rows_; j++)
				{
					out << m._data[i][j] << "\t";
				}
				out << "\n";
			}
			out << std::endl;
			return out;
		}

		/**
		* @brief 获取矩阵某个元素的右值
		* @param cols 行数
		* @param rows 列数
		*/
		_Tp& at(uint32_t cols, uint32_t rows)
		{
			return _data[cols][rows];
		}

	private:
		void creat(uint32_t cols, uint32_t rows);
		void destroyArry(type_pointer* & p);
		void fill(type numb);
	};
	


	class TMatrix : public Matrix<double>
	{
	public:
		double& nx = _data[0][0];
		double& ny = _data[1][0];
		double& nz = _data[2][0];
		double& ox = _data[0][1];
		double& oy = _data[1][1];
		double& oz = _data[2][1];
		double& ax = _data[0][2];
		double& ay = _data[1][2];
		double& az = _data[2][2];
		double& px = _data[0][3];
		double& py = _data[1][3];
		double& pz = _data[2][3];
		
		TMatrix() : Matrix<double>(4, 4)
		{
		}
		TMatrix(double* data) : Matrix<double>(4, 4, data)
		{
		}

		TMatrix(const TMatrix & tm):Matrix<double>(4, 4)
		{
			if (tm.cols_ != this->cols_ || tm.rows_ != this->rows_)
			{
				creat(tm.cols_, tm.rows_);
			}
			for (uint32_t i = 0; i < tm.cols_; i++)
				for (uint32_t j = 0; j < tm.rows_; j++)
					this->_data[i][j] = tm._data[i][j];
		}
		~TMatrix(){}

		TMatrix operator*(const TMatrix& m)
		{
			if (this->rows_ != m.cols_)
			{
				throw("error:TMatrix mutipul rows do not equal cols");
			}
			TMatrix res;
			for (uint32_t i = 0; i < this->cols_; i++)
				for (uint32_t j = 0; j < m.rows_; j++)
					for (uint32_t k = 0; k < this->rows_; k++)
						res._data[i][j] += this->_data[i][k] * m._data[k][j];

			return res;
		}

		TMatrix& operator=(const TMatrix& tm)
		{
			if (tm.cols_ != 4 || tm.rows_ != 4)
			{

			}
			for (uint32_t i = 0; i < 4; i++)
				for (uint32_t j = 0; j < 4; j++)
				{
					this->_data[i][j] = tm._data[i][j];
				}
			return *this;
		}
		/**
		* @brief 将TMatrix转化为Matrix
		*/
		Matrix<double> toMatrix();
	private:

	};

	
}