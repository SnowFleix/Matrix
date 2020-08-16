#pragma once
#include <stdexcept>
#include <vector>
#include <typeinfo>

namespace matracies {

	template <class T, class alloc = std::allocator<T>>
	class Matrix {

	public:
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
		unsigned int dimx_, dimy_; // set to private later

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
		/// Add an element to the metrix at a specific position
		/// </summary>
		/// <param name="value">The value to add to the matrix</param>
		/// <param name="x">The column to add to</param>
		/// <param name="y">The row to add to</param>
		void add(T value, unsigned int x, unsigned int y) {
			if (isOutOfRange(x, y))
				throw out_of_range_error;
			inner_[dimx_ * y + x] = value;
		}

		// matrix operations

		/// <summary>
		/// Inverts the matrix
		/// </summary>
		void invert() {
			if (dimx_ != dimy_)
				throw matrix_not_n_by_n;
			if (!inverse(*this, *this))
				throw cannot_find_inverse;
		}

		/// <summary>
		/// Returns the deteminant of the matrix
		/// </summary>
		/// <returns>The deteminant as an integer</returns>
		/// TODO : add to a specialised templated class, won't work with matracies of types other than numbers
		int& getDeterminant() {
			return determinant(*this, this->size());
		}

		/// <summary>
		/// Normalises the matrix
		/// </summary>
		/// TODO : implement normalisation
		void normalise() {}

		// operators

		/// <summary>
		/// Checks if two matracies contain the same values
		/// </summary>
		/// <param name="arg">The matrix to compare against</param>
		/// <returns>Whether the two are the same or not as a bool</returns>
		bool operator==(Matrix<T> arg) {
			if (isOutOfRange(arg))
				throw matrix_wrong_size;
			for (int i = 0; i < inner_.size(); i++)
				if (inner_[i] != arg.inner_[i])
					return false;
			return true;
		}

		/// <summary>
		/// Checks if the two matricies are not the same
		/// </summary>
		/// <param name="arg">The matrix to compare</param>
		/// <returns>Bool</returns>
		bool operator!=(Matrix<T> arg) {
			return !(*this == arg);
		}

		/// <summary>
		/// Copies a matrix to the current one
		/// </summary>
		/// <param name="arg">The matrix to copy</param>
		/// <returns></returns>
		Matrix<T>& operator=(Matrix<T> arg) {
			if (this != arg)
				this = arg; // change later
		}

		/// <summary>
		/// Simple matrix addition
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
		/// Matrix subtraction
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
		/// Matrix multiplication
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
		/// Matrix division
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator/(Matrix<T> arg) {
			//TODO : find a way to properly divide
			return *this;
		}

		/// <summary>
		/// Overrides the += operator
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator+=(Matrix<T> arg) {
			return this + arg;
		}

		/// <summary>
		/// Overrides the -= operator
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator-=(Matrix<T> arg) {
			return this - arg;
		}

		/// <summary>
		/// Overrides the *= operator
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator*=(Matrix<T> arg) {
			return this * arg;
		}

		/// <summary>
		/// overrides the /= operator
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator/=(T arg) {
			return this / arg;
		}

		/// <summary>
		/// Allows users to do Matrix[x][y]
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		std::vector<T>& operator[](int index) {
			return getColumn(index);
		}

		/// <summary>
		/// Returns a constant iterator where the value is kept within the vector inner_
		/// </summary>
		/// <param name="key">The value to get</param>
		/// <returns>A const iterator of where the element is </returns>
		const_iterator find(const T& key) const {
			return std::find(inner_.begin(), inner_.end(), key);
		}

		/// <summary>
		/// Gets the size of the matrix
		/// </summary>
		/// <returns>Only returns the amount of columns</returns>
		size_type size() const {
			return dimx_;
		}

		/// <summary>
		/// Gets the max amount of elements possible to add to the matrix
		/// </summary>
		/// <returns>The size of the vector</returns>
		size_type max_size() const {
			return std::vector.max_size();
		}

		/// <summary>
		/// Gets an element at col x, row y
		/// </summary>
		/// <param name="x">The column</param>
		/// <param name="y">The row</param>
		/// <returns>The element at x,y</returns>
		const_reference at(int x, int y) const {
			return getAt(x, y);
		}

		/// <summary>
		/// Finds and element in the matrix
		/// </summary>
		/// <param name="key">The value requred</param>
		/// <returns>The iterator within the vector where the element is</returns>
		iterator find(const T& key) {
			return std::find(inner_.begin(), inner_.end(), key);
		}

		/// <summary>
		/// Gets the size of inner_
		/// </summary>
		/// <returns></returns>
		size_t vecSize() {
			return inner_.size();
		}

		/// <summary>
		/// Deletes all the elements of the matrix
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
		TH1* toTH1(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			TH1* temp(name, title, nbinsx, xlow, xup);
			for (int i = 0; i < inner_.size(); i++)
				if (inner_[i] > 0)
					temp->Fill(i / dimx_, weight);
			return temp;
		}

#ifdef ROOT_TH1F
		TH1F* toTH1F(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			if (!isFloat())
				throw wrong_data_type;
			return toTH1(name, title, nbinsx, xlow, xup, weight);
		}
#endif

#ifdef ROOT_TH1D
		TH1F* toTH1F(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			if (!isDouble())
				throw wrong_data_type;
			return toTH1(name, title, nbinsx, xlow, xup, weight);
		}
#endif

#ifdef ROOT_TH1I
		TH1I* toTH1I(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			if (!isInt32())
				throw wrong_data_type;
			return toTH1(name, title, nbinsx, xlow, xup, weight);
		}
#endif 

#ifdef ROOT_TH1S
		TH1S* toTH1S(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			if (!isShort())
				throw wrong_data_type;
			return toTH1(name, title, nbinsx, xlow, xup, weight);
		}
#endif 

#ifdef ROOT_TH1C
		TH1C* toTH1C(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			if (!isChar())
				throw wrong_data_type;
			return toTH1(name, title, nbinsx, xlow, xup, weight);
		}
#endif 

#ifdef ROOT_TH1K
		// k neighbour class TODO : read through ROOT documentation more to use see how it differs from the other TH1
#endif 

#endif

#ifdef ROOT_TH2

		TH2* toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, 
			       Int_t nbinsy, Double_t ylow, Double_t yup) {
			TH2* temp(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
			for (int i = 0; i < inner_.size(); i++)
				if (inner_[i] > 0)
					temp->Fill(i / dimx_, i % dimy_, inner_[i]); // uses the element as the weight
			return temp;
		}

#ifdef ROOT_TH2F
		TH2F* toTH2F(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			if (!)
				throw wrong_data_type;
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2D
		TH2D* toTH2D(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			if (!isDouble())
				throw wrong_data_type;
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2S
		TH2S* toTH2S(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			if (!isShort())
				throw wrong_data_type;
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2I
		TH2I* toTH2I(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			if (!isInt32())
				throw wrong_data_type;
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2C
		TH2C* toTH2C(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			if (!isChar())
				throw wrong_data_type;
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2GL
		// implement later
#endif

#ifdef ROOT_TH2Poly
		// implement later
#endif

#endif

#ifdef ROOT_TMatrixT
#ifdef ROOT_TMatrix

		Matrix(TMatrix tMatrix)
			: dimx_(tMatrix.GetNrows()), dimy_(tMatrix.GetNcols()) {
			if (!typeid(T).name() == "Float_T")
				throw wrong_data_type;
			inner_.resize(dimx_ * dimy_);
			inner_ = tMatrix.GetMatrixArray();
		}

		operator TMatrix() const {
			TMatrix temp(dimx_, dimy_);
			for (int i = 0; i < inner_.size(); i++)
				temp[i % dimx_][i / dimy_] = inner_[i];
			return temp;
		}

		Matrix<T>& operator=(TMatrix<T> arg) {
			return Matrix<T>(arg);
		}

		TMatrix toTMatrix() {
			if (!typeid(T).name() == "Float_T")
				throw wrong_data_type;
			return static_cast<TMatrix>(*this);
		}

#endif

		Matrix(TMatrixT<T> tMatrix)
			: dimx_(tMatrix.GetNrows()), dimy_(tMatrix.GetNcols()) {
			inner_.resize(dimx_ * dimy_);
			inner_ = tMatrix.GetMatrixArray();
		}

		TMatrixT<T> toTMatrixT() {
			return static_cast<TMatrixT<T>>(*this);
		}

		operator TMatrixT<T>() const {
			TMatrix temp(dimx_, dimy_);
			for (int i = 0; i < inner_.size(); i++)
				temp[i % dimx_][i / dimy_] = inner_[i];
			return temp;
		}

		Matrix<T>& operator=(TMatrixT<T> arg) {
			return Matrix<T>(arg);
		}

#endif

	private:
		std::out_of_range out_of_range_error("Matrix indices out of range"); // create our outofrange error
		std::invalid_argument matrix_wrong_size("The passed matix is not of the same size as the base");
		std::invalid_argument wrong_data_type("The passed datatype does not match that used in the function");
		std::domain_error cannot_find_inverse("Cannot find the inverse of the matrix");

		/// <summary>
		/// Checks if the type of the matrix is an int32
		/// </summary>
		/// <returns></returns>
		bool isInt32() {
			return typeid(T).name == "__int32" || typeid(T).name == "int32_t";
		}

		/// <summary>
		/// Checks if the type of the matrix is a double
		/// </summary>
		/// <returns></returns>
		bool isDouble() {
			return typeid(T).name == "double" || typeid(T).name == "Double_t" || typeid(T).name == "double_t";
		}

		/// <summary>
		/// Checks if the type of the matrix is a float
		/// </summary>
		/// <returns></returns>
		bool isFloat() {
			return typeid(T).name == "float" || typeid(T).name == "float_t" || typeid(T).name == "Float_t";
		}

		/// <summary>
		/// Checks if the type of the matrix is a short
		/// </summary>
		/// <returns></returns>
		bool isShort() {
			return typeid(T).name == "short" || typeid(T).name == "Short_t";
		}

		/// <summary>
		/// Checks if the type of the matrix is a char
		/// </summary>
		/// <returns></returns>
		bool isChar() {
			return typeid(T).name == "char" || typeid(T).name == "Char_t";
		}

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
		/// Gets a row at the specified index
		/// </summary>
		/// <param name="row"></param>
		/// <returns></returns>
		/// <remarks>returns a reference to a temp variable</remarks>
		std::vector<T>& getRow(int row) {
			if (row > dimy_)
				throw out_of_range_error;
			std::vector<T> temp;
			for (int i = row * dimy_; i < dimx_; i++)
				temp.push_back(inner_[i]);
			return temp;
		}

		/// <summary>
		/// Gets a whole column at the specified index
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
		/// Multiplies two matricies and sends creates a new on called out
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
		/// Gets the cofactor of the matrix
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
		/// Gets the determinant of the matrix
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
			if (!(isInt32() || isDouble() || isFloat() || isShort()))
				throw wrong_data_type;
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
		friend std::ostream& operator<<(std::ostream& os, Matrix<T>& matrix) {
			std::string builder = "";
			for (int loop = 0; loop < matrix.vecSize(); loop++) {
				if (loop % matrix.dimx_ == 0 && i != 0) {
					builder += "\n";
				}
				builder += "(" + matrix.getAt(loop % matrix.dimx_, loop / matrix.dimy_).toString() + ") ";
			}
			os << builder;
			return os;
		}
	};
}