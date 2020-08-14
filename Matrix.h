#pragma once
#include <stdexcept>
#include <vector>


namespace matracies {

	template <class T, class alloc = std::allocator<T>>
	class Matrix {

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

		// matrix operations

		/// <summary>
		/// 
		/// </summary>
		void invert() {
			if (dimx_ != dimy_)
				throw matrix_not_n_by_n;
			if (!inverse(*this, *this))
				throw cannot_find_inverse;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		int& getDeterminant() {
			return determinant(*this, this->size());
		}

		/// <summary>
		/// 
		/// </summary>
		void normalise() {}

		// operators

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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator=(Matrix<T> arg) {
			if (this != arg)
				this = arg;
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
		/// TODO : make this more efficient
		Matrix<T>& operator*(Matrix<T> arg) {

			Matrix<T> temp(dimx_, dimy_);
			multiply(this, arg, temp);
			return temp;
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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		const_iterator find(const T& key) const {
			return std::find(inner_.begin(), inner_.end(), key);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		size_type size() const {
			return dimx_;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		size_type max_size() const {
			return std::vector.max_size();
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		const_reference at(int x, int y) const {
			return getAt(x, y);
		}

		/* Mutators */

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		iterator find(const T& key) {
			return std::find(inner_.begin(), inner_.end(), key);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
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

#ifdef ROOT_TH1

#endif

#ifdef ROOT_TH2

#endif

#ifdef ROOT_TH3

#endif

#ifdef ROOT_TMatrixT

		Matrix(TMatrix tMatrix)
			: dimx_(tMatrix.GetNrows()), dimy_(tMatrix.GetNcols()) {
			inner_.resize(dimx_ * dimy_);

		}

#endif


	private:
		std::out_of_range out_of_range_error("Matrix indices out of range"); // create our outofrange error
		std::invalid_argument matrix_wrong_size("The passed matix is not of the same size as the base");
		std::domain_error cannot_find_inverse("");

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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="row"></param>
		/// <returns></returns>
		std::vector<T> getRow(int row) {
			if (row > dimy_)
				throw out_of_range_error;
			std::vector<T> temp;
			for (int i = row; i < dimy_; i++)
				temp.push_back(inner_[i]);
			return temp;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="row"></param>
		/// <returns></returns>
		std::vector<T> getColumn(int column) {
			if (column > dimx_)
				throw out_of_range_error;
			std::vector<T> temp;
			for (int i = row; i < dimx_; i++)
				temp.push_back(inner_[i] + dimx_ * i);
			return temp;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="matrixOne"></param>
		/// <param name="matrixTwo"></param>
		/// <param name="out"></param>
		void multiply(Matrix<T> matrixOne, Matrix<T> matrixTwo, Matrix<T>& out) {
			for (int i = 0; i < dimx_; i++) {
				for (int j = 0; j < dimy_; j++) {
					out.add(i, j, 0) = 0;
					for (int k = 0; k < matrixOne.dimx_; k++)
						out.getAt(i, j) += matrixOne.getAt(i, k) *
						matrixTwo.getAt(k, j);
				}
			}
		}

		// TODO : rename all the one letter variables to something actually meaningful and useful

		/// <summary>
		/// 
		/// </summary>
		/// <param name="M">The matrix to inverse</param>
		/// <param name="t"></param>
		/// <param name="p"></param>
		/// <param name="q"></param>
		/// <param name="n"></param>
		void getCofactor(Matrix<T> M, Matrix<T> t, int p, int q, int n) {
			int i = 0, j = 0;
			for (int r = 0; r < n; r++) {
				for (int c = 0; c < n; c++) { //Copy only those elements which are not in given row r and column c: 
					if (r != p && c != q) {
						t.getAt(i, j++) = M.getAt(r, c); //If row is filled increase r index and reset c index
						if (j == n - 1) {
							j = 0; i++;
						}
					}
				}
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="M">The matrix to inverse</param>
		/// <param name="n">The </param>
		/// <returns></returns>
		int determinant(Matrix<T>& M, int n) { //to find determinant 
			int D = 0;
			if (n == 1)
				return M.getAt(0, 0);
			Matrix<T> t(M.size(), M.size()); //store cofactors
			int s = 1; //store sign multiplier 
					   //To Iterate each element of first row
			for (int f = 0; f < n; f++) {
				//For Getting Cofactor of M[0][f] do getCofactor(M, t, 0, f, n); D += s * M[0][f] * DET(t, n - 1);
				s = -s;
			}
			return D;
		}

		/// <summary>
		/// Creates an adjoint matrix using asj
		/// </summary>
		/// <param name="M">The matrix to inverse</param>
		/// <param name="adj">The adjoint matrix, another out matrix</param>
		void adjoint(Matrix<T>& M, Matrix<T>& adj) {
			//to find adjoint matrix 
			if (M.size() == 1) {
				adj.getAt(0, 0) = 1;
				return;
			}
			int s = 1,
				Matrix<T> t(M.size(), M.size());
			for (int i = 0; i < M.size(); i++) {
				for (int j = 0; j < M.size(); j++) {
					//To get cofactor of M[i][j]
					getCofactor(M, t, i, j, M.size());
					s = ((i + j) % 2 == 0) ? 1 : -1; //sign of adj[j][i] positive if sum of row and column indexes is even.
					adj.getAt(j, i) = (s) * (determinant(t, M.size() - 1)); //Interchange rows and columns to get the transpose of the cofactor matrix
				}
			}
		}

		/// <summary>
		/// Inverts the matrix
		/// </summary>
		/// <param name="M">The matrix to inverse</param>
		/// <param name="inv">The inverse aka the out matrix</param>
		/// <returns></returns>
		bool inverse(Matrix<T> M, Matrix<T>& inv) {
			int det = determinant(M, M.size());
			if (det == 0) {
				throw cannot_find_inverse;
				return false;
			}
			Matrix<T> adj(M.size(), M.size());
			adjoint(M, adj);
			for (int i = 0; i < M.size(); i++)
				for (int j = 0; j < M.size(); j++)
					inv.getAt(i, j) = adj.getAt(i, j) / T(det);
			return true;
		}

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
		}
	};
}