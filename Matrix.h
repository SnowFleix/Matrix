#pragma once
#include <stdexcept>
#include <vector>

template <class T, class alloc = std::allocator<T>>
class Matrix
{
private:
	std::out_of_range out_of_range_error("Matrix indices out of range"); // create our outofrange error
	std::invalid_argument matrix_wrong_size("The passed matix is not of the same size as the base");

	/// <summary>
	/// Checks if a passed matrix is the same size as one passed through
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	bool isOutOfRange(Matrix<T> arg) {
		return arg.dimx_ >= dimx_ || arg.dimy_ >= dimy_
	}

	/// <summary>
	/// Check if the number x,y is the same as rows,columns
	/// </summary>
	/// <param name="x">Columns to check</param>
	/// <param name="y">Rows to check</param>
	/// <returns></returns>
	bool isOutOfRange(unsigned int x, unsigned int y) {
		return x >= dimx_ || y >= dimy_
	}

public:
	// STL functionality
	using matrix_type = T;
	using value_type = matrix_type;
	using allocator_type = alloc;
	using reference = matrix_type&;
	using const_reference = const matrix_type&;
	using pointer = typename std::allocator_traits<allocator_type>::pointer;
	using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
	using iterator = std::vector::iterator<matrix_type>;
	using const_iterator = std::vector::const_iterator<matrix_type>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using difference_type = std::iterator_traits<iterator>::difference_type;
	using size_type = std::size_t;

	// public variables
	std::vector<T> inner_; // set to private later
	unsigned int dimx_, dimy_;

	/// <summary>
	/// Default constructor 
	/// </summary>
	/// <param name="dimx">Amount of columns</param>
	/// <param name="dimy">Amount of rows</param>
	Matrix(unsigned int dimx, unsigned int dimy)
		: dimx_(dimx), dimy_(dimy) {
		inner_.resize(dimx_ * dimy_);
	}

	/// <summary>
	/// Returns a value at the specified position within the matrix
	/// </summary>
	/// <param name="x">Position in the row</param>
	/// <param name="y">Position in the column</param>
	/// <returns>Object requested</returns>
	/// <remarks>Will throw an error if out of range</remarks>
	T& getAt(unsigned int x, unsigned int y) {
		if (isOutOfRange(x, y))
			throw out_of_range_error;
		return inner_[dimx_ * y + x];
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void add(T value, unsigned int x, unsigned int y) {
		if (isOutOfRange(x, y))
			throw out_of_range_error;
		inner_[dimx_ * y + x] = value;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator=(Matrix<T> arg) {
		if (this != arg)
			this = arg;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	bool operator==(Matrix<T> arg) {
		if (isOutOfRange(arg))
			throw matrix_wrong_size;
		for (int i = 0; i < inner_.size(); i++)
			if (inner_[i] != arg.inner_[i])
				return false;
		return true;
	}

	// Binary arithmetic operators

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator+(Matrix<T> arg) {
		if (isOutOfRange(arg))
			throw matrix_wrong_size;
		for (int i = 0; i < dimx_ * dimy_; i++)
			inner_[i] += arg.getAt(i % dimx_, i / dimy_);
		return *this;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator-(Matrix<T> arg) {
		if (isOutOfRange(arg))
			throw matrix_wrong_size;
		for (int i = 0; i < dimx_ * dimy_; i++)
			inner_[i] -= arg.getAt(i % dimx_, i / dimy_);
		return *this;
	}
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator*(Matrix<T> arg) {
		//TODO : find a way to properly multiply
		return *this;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator/(Matrix<T> arg) {
		//TODO : find a way to properly divide
		return *this;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator+=(Matrix<T> arg) {
		return this + arg;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator-=(Matrix<T> arg) {
		return this - arg;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator*=(Matrix<T> arg) {
		return this * arg;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="arg"></param>
	/// <returns></returns>
	Matrix<T>& operator/=(T arg) {
		return this / arg;
	}

	// STL functions

	/* Selectors */
	const_iterator find(const T& key) const {

	}

	size_type size() const {

	}

	size_type max_size() const {
		return std::vector.max_size();
	}

	reference at(const key_type& key) {

	}

	const_reference at(const key_type& key) const {

	}

	/* Mutators */
	iterator find(const key_type& key) {

	}

	void erase(const key_type& key) {
		delete inner_;
		inner_ = std::vector<T>;
		inner_.resize(dimx_ * dimy_);
	}

	/// <summary>
	/// Clears the vector
	/// </summary>
	void clear() {
		delete inner_;
		inner_ = std::vector<T>;
		inner_.resize(dimx_ * dimy_);
	}

	/*
	// TODO : refactor so it's much better code
	// outputs the matrix in text format
	friend ostream& operator<<(ostream& os, Matrix& matrix) {
		string builder = "";
		for (int loop = 0; loop < matrix.inner_.size(); loop++) {
			if (loop % matrix.dimx_ == 0 && i != 0) {
				builder += "\n";
			}
			builder += "(" + matrix.getAt(loop % matrix.dimx_, loop / matrix.dimy_).toString() + ") "; i++;
		}
		os << builder;
		return os;
	}*/
};