#include <iostream>
#include <math.h>
#include <assert.h>


template <typename T> 
class Vector {
private:
	std::size_t _rows;
	std::size_t _cols = 1;
	T *_values = nullptr;

public:
	Vector(std::size_t rows, T initValue) {
		T *Vector = new T[rows];

		for (unsigned int i = 0; i < rows; i++) {
			Vector[i] = initValue;
		}

		_rows = rows;
		_values = Vector;
	}

	~Vector() {
		delete[] _values;
	}

	Vector(const Vector<T>& a) {
		_rows = a.rows();
		delete[] _values;
		_values = new T[_rows];

		size_t index = 0;

		for (size_t i = 0; i < a.rows(); i++) {
			_values[index] = a(i);
			index++;
		}
	}

	Vector& operator=(const Vector<T>& a) {
		if (a == *this) {
			T *n_values = new T[_rows];

			for (size_t i = 0; i < _rows; ++i) {
				n_values[i] = _values[i];
			}

			delete[] _values;
			_values = n_values;
			return *this;
		}

		_rows = a.rows();
		delete[] _values;
		_values = new T[_rows];

		size_t index = 0;

		for (size_t i = 0; i < a.rows(); ++i) {
			_values[index] = a(i);
			index++;
		}

		return *this;
	}

	std::size_t rows() const {
		return Vector<T>::_rows;
	}

	std::size_t cols() const {
		return Vector<T>::_cols;
	}

	std::size_t size() const{
		return _rows;
	}


	T& operator()(std::size_t i) {
		return _values[i];
	}

	const T& operator()(std::size_t i) const {
		return _values[i];
	}

	bool operator ==(const Vector<T>& a) const {
		if (_cols != a.cols()) return false;
		if (_rows != a.rows()) return false;

		for (unsigned int i = 0; i < _rows * _cols; ++i) {
			if (_values[i] != a._values[i]) return false;
		}

		return true;
	}

	bool operator !=(const Vector<T>& a) const {
		if (a == (*this)) return false;

		return true;
	}



	Vector& operator +=(const Vector<T>& a) {
		assert(_rows == a.rows());
		assert(_cols == a.cols());

		for (unsigned int i = 0; i < _rows; ++i) {
			_values[i] += a._values[i];
		}

		return *this;
	}

	Vector operator +(const Vector<T>& a) const {
		assert(_rows == a.rows());
		assert(_cols == a.cols());

		Vector m = Vector(_rows, _cols, 0);

		for (unsigned int i = 0; i < _rows; ++i) {
			m._values[i] = _values[i] + a._values[i];
		}

		return m;
	}

	Vector& operator -=(const Vector<T>& a) {
		assert(_rows == a.rows());
		assert(_cols == a.cols());

		for (unsigned int i = 0; i < _rows; ++i) {
			_values[i] -= a._values[i];
		}

		return *this;
	}

	Vector operator -(const Vector<T>& a) const {
		assert(_rows == a.rows());
		assert(_cols == a.cols());

		Vector m = Vector(_rows, 0);

		for (unsigned int i = 0; i < _rows; ++i) {
			m._values[i] = _values[i] - a._values[i];
		}

		return m;
	}

	Vector& operator *=(const Vector<T>& x) {
		assert(_cols == x.rows());

		T *temp = new T[_rows * x.cols()];
		T sum = 0;
		int k = 0;

		for (size_t i = 0; i < _rows; ++i) {

			for (size_t n = 0; n < x._rows(); ++n) {
				T val1 = _values[i * _cols + n];
				T val2 = x(n);
				sum += val1 * val2;
			}

			temp[k] = sum;
			k++;
			sum = 0;

		}

		_cols = x._cols;

		delete[] _values;
		_values = temp;

		return *this;
	}


	Vector operator *(const Vector<T>& a) const {
		assert(_cols == a.rows());

		Vector m = Vector(_rows, 0);
		T sum = 0;

		for (size_t i = 0; i < _rows; ++i) {

			for (size_t n = 0; n < a._rows(); ++n) {
				T val1 = _values[i * _cols + n];
				T val2 = a(n);
				sum += val1 * val2;
			}

			m(i) = sum;
			sum = 0;

		}

		return m;
	}

	T l2Norm() {
		T norm = (T)0;
		for (int i = 0; i < _rows; ++i) {
			norm += _values[i] * _values[i];
		}

		return sqrt(norm);
	}



	friend std::ostream& operator <<(std::ostream& os, const Vector<T>& m) {
		for (size_t i = 0; i < m.rows(); ++i) {
			//size_t index = i * m.cols() + j;
			os << m(i) << std::endl;
		}

		return os;
	}

	friend std::istream& operator >>(std::istream& is, Vector<T>& m){
		T *input = new T[m.rows()];
		size_t length = m.rows();
		std::istream si = si;

		size_t i = 0;
		T x;

		while (i < length && is >> x) {
			input[i] = x;
			i++;
			//std::cout << x << std::endl;		
		}

		//si = is;
		delete[] m._values;
		m._values = input;
		return is;
	}

};


