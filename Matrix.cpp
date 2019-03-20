#include "Matrix.h"

template <typename T> std::size_t Matrix<T>::rows() const {
	return Matrix<T>::_rows;
}

template <typename T> std::size_t Matrix<T>::cols() const {
	return Matrix<T>::_cols;
}


template <typename T> Matrix<T>::Matrix(std::size_t rows, std::size_t cols, T initValue) {
	T *matrix = new T[rows * cols];

	for (unsigned int i = 0; i < rows * cols; ++i) {
		matrix[i] = initValue;
	}

	Matrix::_rows = rows;
	Matrix::_cols = cols;
	_values = matrix;
}

template <typename T> Matrix<T>::~Matrix() {
	delete[] _values;
}

template <typename T> Matrix<T>::Matrix(const Matrix& a) {
	_rows = a.rows();
	_cols = a.cols();
	delete[] _values;
	_values = new T[_rows * _cols];

	size_t index = 0;

	for (size_t i = 0; i < a.rows(); ++i) {
		for (size_t j = 0; j < a.cols(); ++j) {
			_values[index] = a(i, j);
			index++;
		}
	}

}

template <typename T> Matrix<T>& Matrix<T>::operator=(const Matrix& a) {
	if (a == *this) {
		T *n_values = new T[_rows * _cols];

		for (size_t i = 0; i < _rows * _cols; ++i) {
			n_values[i] = _values[i];
		}

		delete[] _values;
		_values = n_values;
		return *this;
	}

	_cols = a.cols();
	_rows = a.rows();
	delete[] _values;
	_values = new T[_rows * _cols];

	size_t index = 0;

	for (size_t i = 0; i < a.rows(); ++i) {
		for (size_t j = 0; j < a.cols(); ++j) {
			_values[index] = a(i, j);
			index++;
		}
	}

	return *this;
}

template <typename T> T& Matrix<T>::operator()(std::size_t i, std::size_t j) {

	return _values[i * _cols + j];
}

template <typename T> const T& Matrix<T>::operator()(std::size_t i, std::size_t j) const {

	int index = i * _cols + j;
	return _values[index];
}


template <typename T> bool Matrix<T>::operator ==(const Matrix<T>& a) const {
	if (_cols != a.cols()) return false;
	if (_rows != a.rows()) return false;

	for (unsigned int i = 0; i < _rows * _cols; ++i) {
		if (_values[i] != a._values[i]) return false;
	}

	return true;
}

template <typename T> bool Matrix<T>::operator !=(const Matrix<T>& a) const {

	if (a == (*this)) return false;

	return true;
}

template <typename T> Matrix<T>& Matrix<T>::operator +=(const Matrix<T>& a) {

	assert(_rows == a.rows());
	assert(_cols == a.cols());

	for (unsigned int i = 0; i < _cols * _rows; ++i) {
		_values[i] += a._values[i];
	}

	return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator +(const Matrix<T>& a) const {

	assert(_rows == a.rows());
	assert(_cols == a.cols());

	Matrix m = Matrix(_rows, _cols, 0);

	for (unsigned int i = 0; i < _rows * _cols; ++i) {
		m._values[i] = _values[i] + a._values[i];
	}

	return m;
}

template <typename T> Matrix<T>& Matrix<T>::operator -=(const Matrix<T>& a) {

	assert(_rows == a.rows());
	assert(_cols == a.cols());

	for (unsigned int i = 0; i < _cols * _rows; ++i) {
		_values[i] -= a._values[i];
	}

	return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator -(const Matrix<T>& a) const {

	assert(_rows == a.rows());
	assert(_cols == a.cols());

	Matrix m = Matrix(_rows, _cols, 0);

	for (unsigned int i = 0; i < _rows * _cols; ++i) {
		m._values[i] = _values[i] - a._values[i];
	}

	return m;
}

template <typename T> Matrix<T>& Matrix<T>::operator *=(const Matrix<T>& x) {

	assert(_cols == x.rows());

	T *temp = new T[_rows * x.cols()];
	T sum = 0;
	int k = 0;

	for (size_t i = 0; i < _rows; ++i) {
		for (size_t j = 0; j < x.cols(); ++j) {

			for (size_t n = 0; n < _cols; ++n) {
				T val1 = _values[i * _cols + n];
				T val2 = x(n, j);
				sum += val1 * val2;
				//printf("val1: %d, val2: %d\n", val1, val2);
			}

			//printf("Sum: %f ----------\n", sum);
			temp[k] = sum;
			k++;
			sum = 0;
		}
	}

	_cols = x._cols;

	delete[] _values;
	_values = temp;

	return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator *(const Matrix<T>& a) const {

	assert(_cols == a.rows());

	Matrix m = Matrix(_rows, a.cols(), 0);
	T sum = 0;

	for (size_t i = 0; i < _rows; ++i) {
		for (size_t j = 0; j < a.cols(); ++j) {

			for (size_t n = 0; n < _cols; ++n) {
				T val1 = _values[i * _cols + n];
				T val2 = a(n, j);
				sum += val1 * val2;
				//printf("val1: %d, val2: %d\n", val1, val2);
			}

			//printf("Sum: %f ----------\n", sum);
			m(i, j) = sum;
			sum = 0;
		}
	}

	return m;
}


template <typename T> Vector<T> Matrix<T>::operator* (const Vector<T> & o) const {
	assert(_cols == o.rows());

	Vector<T> m = Vector<T>(_rows, 0);
	T sum = 0;

	for (size_t i = 0; i < _rows; ++i) {
		for (size_t j = 0; j < o.rows(); ++j) {
			
			T val1 = _values[i * _cols + j];
			T val2 = o(j);
			sum += val1 * val2;				
		}

		m(i) = sum;
		sum = 0;
	}

	return m;

}


template <typename T> Matrix<T> Matrix<T>::inverseDiagonal() const{

	assert(_rows == _cols);

	Matrix m = Matrix(_rows, _cols, 0);	

	for (size_t i = 0; i < _rows; ++i) {
		size_t diagonal_index = i * _cols + i;
		assert( _values[diagonal_index] != 0 );
		m(i, i) = 1 / _values[diagonal_index];
		
	}

	return m;
}


template <typename T> std::ostream& operator <<(std::ostream& os, const Matrix<T>& m) {
	//std::stringstream ss;

	for (size_t i = 0; i < m.rows(); ++i) {
		for (size_t j = 0; j < m.cols(); ++j) {
			//size_t index = i * m.cols() + j;
			os << m(i, j) << ' ';
		}

		os << std::endl;
	}

	return os;

}

template <typename T> std::istream& operator>> (std::istream& is, Matrix<T>& m) {
	T *input = new T[m.cols() * m.rows()];
	size_t length = m.cols() * m.rows();

	size_t i = 0;
	T x;

	while (i < length && is >> x) {
		input[i] = x;
		++i;
		//std::cout << x << std::endl;		
	}

	delete[] m._values;
	m._values = input;
	return is;
}