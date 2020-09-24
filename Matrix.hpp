#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <typeinfo>
#include <iterator>
#include <cmath>

namespace mathUtils {
	
	#define _PI     3.1415926535897932384626433832795f
	#define _TWOPI  6.283185307179586476925286766559f
	#define _HALFPI 1.5707963267948966192313216916398f

	inline float abs(float x) {
		float r;
		__asm {
			abs.s %0, %1 : =&f (r) : f(x)
		}
		return r;
	}

	inline float min(float a, float b) {
		float r;
		__asm {
			min.s % 0, % 1, % 2 : = &f(r) : f(a), f(b)
		}
		return r;
	}

	inline float max(float a, float b) {
		float r;
		__asm {
			max.s %0, %1, %2 : =&f (r) : f (a), f (b)
		}
		return r;
	}

	inline float sqrt(float x) {
		float r;
		__asm {
			sqrt.s % 0, % 1 : = &f(r) : f(x)
		}
		return r;
	}

	float cos(float x)
	{
		float r;
		__asm {
			lui     $9,  0x3f00       
			.set noreorder            
			.align 3                  
			abs.s   %0,  %1           
			lui     $8,  0xbe22       
			mtc1    $9,  $f1          
			ori     $8,  $8,    0xf983
			mtc1    $8,  $f8          
			lui     $9,  0x4b00       
			mtc1    $9,  $f3          
			lui     $8,  0x3f80       
			mtc1    $8,  $f2          
			mula.s  %0,  $f8          
			msuba.s $f3, $f2          
			madda.s $f3, $f2          
			lui     $8,  0x40c9       
			msuba.s %0,  $f8          
			ori     $8,  0x0fdb       
			msub.s  %0,  $f1,   $f2   
			lui     $9,  0xc225       
			abs.s   %0,  %0           
			lui     $10, 0x3e80       
			mtc1    $10, $f7          
			ori     $9,  0x5de1       
			sub.s   %0,  %0,    $f7   
			lui     $10, 0x42a3       
			mtc1    $8,  $f3          
			ori     $10, 0x3458       
			mtc1    $9,  $f4          
			lui     $8,  0xc299       
			mtc1    $10, $f5          
			ori     $8,  0x2663       
			mul.s   $f8, %0,    %0    
			lui     $9,  0x421e       
			mtc1    $8,  $f6          
			ori     $9,  0xd7bb       
			mtc1    $9,  $f7          
			nop                       
			mul.s   $f1, %0,    $f8   
			mul.s   $f9, $f8,   $f8   
			mula.s  $f3, %0           
			mul.s   $f2, $f1,   $f8   
			madda.s $f4, $f1          
			mul.s   $f1, $f1,   $f9   
			mul.s   %0,  $f2,   $f9   
			madda.s $f5, $f2          
			madda.s $f6, $f1          
			madd.s  %0,  $f7,   %0    
			.set reorder              
			: =&f (r)
			: f (x)
			: $f1, $f2, $f3, $f4, $f5, $f6, $f7, $f8, $f9, $8, $9, $10
		}
		return r;
	}

	float asin(float x)
	{
		float r;
		__asm {
			.set noreorder            
			.align 3                  
			lui     $8,  0x3f80       
			mtc1    $0,  $f8          
			mtc1    $8,  $f1          
			lui     $8,  0x3f35       
			mfc1    $9,  %1           
			ori     $8,  $8,    0x04f3
			adda.s  $f1, $f8          
			lui     $10, 0x8000       
			msub.s  $f2, %1,    %1    
			not     $11, $10          
			and     $11, $9,    $11   
			subu    $8,  $8,    $11   
			nop                       
			and     $9,  $9,    $10   
			sqrt.s  $f2, $f2          
			srl     $8,  $8,    31    
			abs.s   %0,  %1           
			lui     $11, 0x3fc9       
			ori     $11, 0x0fdb       
			or      $11, $9,    $11   
			movz    $11, $0,    $8    
			xor     $10, $9,    $10   
			mtc1    $11, $f6          
			movz    $10, $9,    $8    
			min.s   %0,  $f2,   %0    
			lui     $9,  0x3e2a       
			lui     $8,  0x3f80       
			ori     $9,  $9,    0xaaab
			or      $8,  $10,   $8    
			or      $9,  $10,   $9    
			mtc1    $8,  $f3          
			lui     $8,  0x3d99       
			mul.s   $f7, %0,    %0    
			ori     $8,  $8,    0x999a
			mtc1    $9,  $f4          
			lui     $9,  0x3d36       
			or      $8,  $10,   $8    
			ori     $9,  $9,    0xdb6e
			mtc1    $8,  $f5          
			or      $9,  $10,   $9    
			mul.s   $f1, %0,    $f7   
			lui     $8,  0x3cf8       
			adda.s  $f6, $f8          
			ori     $8,  $8,    0xe38e
			mul.s   $f8, $f7,   $f7   
			or      $8,  $10,   $8    
			madda.s $f3, %0           
			mul.s   $f2, $f1,   $f7   
			madda.s $f4, $f1          
			mtc1    $9,  $f6          
			mul.s   $f1, $f1,   $f8   
			mul.s   %0,  $f2,   $f8   
			mtc1    $8,  $f7          
			madda.s $f5, $f2          
			madda.s $f6, $f1          
			madd.s  %0,  $f7,   %0    
			.set reorder              
			: =&f (r)
			: f (x)
			: $f1, $f2, $f3, $f4, $f5, $f6, $f7, $f8
		}
		return r;
	}

	inline float mod(float a, float b)
	{
		float r;
		__asm {
			.set push                
			.set noreorder           
			div.s  %0,  %1,    %2    
			mtc1   $0,  $f8          
			mfc1   $10, %0           
			srl    $8,  $10,   23    
			addiu  $9,  $0,    127+23
			andi   $8,  $8,    0xff  
			addiu  $12, $0,    1     
			addiu  $11, $8,   -127   
			subu   $8,  $9,    $8    
			pmaxw  $8,  $8,    $0    
			sllv   $8,  $12,   $8    
			lui    $9,  0x8000       
			negu   $8,  $8           
			srl    $11, $11,   31    
			movz   $9,  $8,    $11   
			and    $10, $9,    $10   
			mtc1   $10, %0           
			adda.s %1,  $f8          
			msub.s %0,  %2,    %0    
			.set pop                 
			: =&f (r)
			: f (a), f (b)
			: $8, $9, $10, $11, $12, $f8
		}
		return r;
	}

	inline float invSqrt(float x) {
		return 1.0f / sqrt(x);
	}

	inline float sin(float x) {
		return cos(x - _HALFPI);
	}

	inline float acos(float x) {
		return _HALFPI - asin(x);
	}
}

namespace matrices {

	template <class T, class alloc = std::allocator<T>>
	class Matrix {

	public:

		// public variables
		std::vector<T> inner_; // set to private later
		int dimx_, dimy_; // set to private later

		/// <summary>
		/// Default constructor 
		/// </summary>
		/// <param name="dimx">Amount of columns</param>
		/// <param name="dimy">Amount of rows</param>
		Matrix(int dimx, int dimy)
			: dimx_(dimx), dimy_(dimy) {
			inner_.resize(dimx_ * dimy_);
		}

		/// <summary>
		/// Returns a value at the specified position within the matrix
		/// </summary>
		/// <param name="col">Position in the row</param>
		/// <param name="row">Position in the column</param>
		/// <returns>Object requested</returns>
		/// <remarks>Will throw an error if out of range</remarks>
		T& getAt(int col, int row) {
			if (isOutOfRange(col, row))
				throw std::out_of_range("Index out of range");
			return inner_[dimx_ * row + col];
		}

		/// <summary>
		/// Add an element to the metrix at a specific position
		/// </summary>
		/// <param name="value">The value to add to the matrix</param>
		/// <param name="col">The column to add to</param>
		/// <param name="row">The row to add to</param>
		void add(T value, int col, int row) {
			if (isOutOfRange(col, row))
				throw std::out_of_range("Index out of range");
			inner_[dimx_ * row + col] = value;
		}

		// matrix operations

		/// <summary>
		/// Inverts the matrix
		/// </summary>
		void invert() {
			if (dimx_ != dimy_)
				throw std::invalid_argument("Matrix is not n by n");
			if (!inverse(*this, *this))
				throw std::domain_error("Cannot find inverse");
		}

		/// <summary>
		/// Returns the deteminant of the matrix
		/// </summary>
		/// <returns>The deteminant as an integer</returns>
		/// TODO : add to a specialised templated class, won't work with matracies of types other than numbers
		double getDeterminant() {
			return 0.0; //determinant(*this, this->dimx_);
		}

		/// <summary>
		/// Gets the cofactor of the matrix
		/// </summary>
		/// <param name="elimCol"></param>
		/// <param name="elimRow"></param>
		std::string getCofactor(int elimCol, int elimRow, Matrix<T> matrix) {
			if (dimx_ == 1 || dimy_ == 1)
				throw std::out_of_range("Bro wot doing??");
			return (determinant(createSubMatrix(matrix, elimRow, elimCol), matrix.dimx_ - 1) + " * " + std::to_string((int)pow(-1, elimCol + elimRow)) + " ");
		}

		/// <summary>
		/// Transposes this matrix
		/// </summary>
		void transpose() {
			Matrix<T> temp = *this;
			for (int i = 0; i < dimy_ * dimx_; i++)
				inner_[i] = temp.getAt(i / dimy_, i % dimx_);
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
			//if (isOutOfRange(arg))
				//throw std::invalid_argument("Matrix is out of range");
			if (inner_.size() == 0) return false;
			if (arg.size() == 0) return false;
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
		//Matrix<T>& operator=(Matrix<T> arg) {
		//	if (this != arg)
		//		this = arg; // change later
		//}

		/// <summary>
		/// Simple matrix addition
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		/// TODO : Need to fix this function as it will change this object
		/// rather than just return a new one with the two matrices added together
		Matrix<T> operator+(Matrix<T> arg) {
			if (isOutOfRange(arg))
				throw std::invalid_argument("Matrix is out of range");
			Matrix<T> temp(*this);
			for (int i = 0; i < temp.inner_.size(); i++)
				temp.inner_[i] = this->getAt(i % dimx_, i / dimy_) + arg.getAt(i % dimx_, i / dimy_);
			return temp;
		}

		/// <summary>
		/// Matrix subtraction
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T> operator-(Matrix<T> arg) {
			if (isOutOfRange(arg))
				throw std::invalid_argument("Matrix is out of range");
			Matrix<T> temp(*this);
			for (int i = 0; i < temp.inner_.size(); i++)
				temp.inner_[i] = this->getAt(i % dimx_, i / dimy_) - arg.getAt(i % dimx_, i / dimy_);
			return temp;
		}

		/// <summary>
		/// Matrix multiplication
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		/// TODO : make this more efficient
		Matrix<T> operator*(Matrix<T> arg) {
			if (isOutOfRange(arg))
				throw std::out_of_range("Matrix out of range");
			Matrix<T> temp(dimx_, dimy_);
			multiply(*this, arg, temp);
			return temp;
		}

		/// <summary>
		/// Matrix division
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T> operator/(Matrix<T> arg) {
			//TODO : find a way to properly divide
			return *this;
		}

		/// <summary>
		/// Overrides the += operator
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator+=(Matrix<T> arg) {
			return *this + arg;
		}

		/// <summary>
		/// Overrides the -= operator
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator-=(Matrix<T> arg) {
			return *this - arg;
		}

		/// <summary>
		/// Overrides the *= operator
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator*=(Matrix<T> arg) {
			return *this * arg;
		}

		/// <summary>
		/// overrides the /= operator
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		Matrix<T>& operator/=(T arg) {
			return *this / arg;;
		}

		/// <summary>
		/// Allows users to do Matrix[col][row]
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		/// This is pretty inefficient but it does allow users to use the [col][row] as if
		/// they are using a 2D array, perhaps find a better way to implement this
		std::vector<T> operator[](int index) {
			return getColumn(index);
		}

		/// <summary>
		/// Returns a constant iterator where the value is kept within the vector inner_
		/// </summary>
		/// <param name="key">The value to get</param>
		/// <returns>A const iterator of where the element is </returns>
		typename std::vector<T>::iterator find(const T& key) const {
			return std::find(inner_.begin(), inner_.end(), key);
		}

		/// <summary>
		/// Gets the size of the matrix
		/// </summary>
		/// <returns>Only returns the amount of columns</returns>
		size_t size() const {
			return dimx_ * dimy_;
		}

		/// <summary>
		/// Gets the max amount of elements possible to add to the matrix
		/// </summary>
		/// <returns>The size of the vector</returns>
		size_t max_size() const {
			return std::vector.max_size();
		}

		/// <summary>
		/// Gets an element at col, row
		/// </summary>
		/// <param name="col">The column</param>
		/// <param name="row">The row</param>
		/// <returns>The element at col,row</returns>
		T& at(int col, int row) const {
			return getAt(col, row);
		}

		/// <summary>
		/// Finds and element in the matrix
		/// </summary>
		/// <param name="key">The value requred</param>
		/// <returns>The iterator within the vector where the element is</returns>
		typename std::vector<T>::iterator find(const T& key) {
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
		void erase() {
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

		/// <summary>
		/// Fills the matrix with the passed object
		/// (All elements in the matrix will be equal to the passed value)
		/// </summary>
		/// <param name="objToFill"></param>
		void fill(T objToFill) {
			for (int i = 0; i < inner_.size(); i++)
				inner_[i] = objToFill;
		}

#ifdef ROOT_TH1

		/// <summary>
		/// Fills a histogram with each row of the matrix
		/// </summary>
		/// <returns></returns>
		template<typename HistT>
		void fillHistogram(HistT hist, int weight) {
			for (int i = 0; i < inner_.size(); i++)
				if (inner_[i] > 0)
					hist->Fill(i / dimx_, weight);
		}

		/// <summary>
		/// Converts a matrix to a TH1, it uses each row to fill the bin in the histogram
		/// </summary>
		/// <returns></returns>
		TH1* toTH1(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			/*TH1* temp = new TH1(name, title, nbinsx, xlow, xup);
			for (int i = 0; i < inner_.size(); i++)
				if (inner_[i] > 0)
					temp->Fill(i / dimx_, weight);
			return temp;*/
		}

#ifdef ROOT_TH1F
		/// <summary>
		/// Checks if the matrix is a float matrix then converts it to a TH1F
		/// </summary>
		/// <returns></returns>
		TH1F* toTH1F(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			//if (!isFloat())
				//throw std::invalid_argument("Matrix is of wrong type");
			TH1F* temp = new TH1F(name, title, nbinsx, xlow, xup);
			fillHistogram(temp, weight);
			return temp;
		}
#endif

#ifdef ROOT_TH1D
		/// <summary>
		/// Checks if the matrix is a double matrix then converts it to a TH1D
		/// </summary>
		/// <returns></returns>
		TH1D* toTH1D(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			//if (!isDouble())
				//throw std::invalid_argument("Matrix is of wrong type");
			TH1D* temp = new TH1D(name, title, nbinsx, xlow, xup);
			fillHistogram(temp, weight);
			return temp;
		}
#endif

#ifdef ROOT_TH1I
		/// <summary>
		/// Checks if the matrix is a int32 matrix then converts it to a TH1I
		/// </summary>
		/// <returns></returns>
		TH1I* toTH1I(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			//if (!isInt32())
				//throw std::invalid_argument("Matrix is of wrong type");
			TH1I* temp = new TH1I(name, title, nbinsx, xlow, xup);
			fillHistogram(temp, weight);
			return temp;
		}
#endif 

#ifdef ROOT_TH1S
		/// <summary>
		/// Checks if the matrix is a short matrix then converts it to a TH1S
		/// </summary>
		/// <returns></returns>
		TH1S* toTH1S(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			//if (!isShort())
				//throw std::invalid_argument("Matrix is of wrong type");
			TH1S* temp = new TH1S(name, title, nbinsx, xlow, xup);
			fillHistogram(temp, weight);
			return temp;
		}
#endif 

#ifdef ROOT_TH1C
		/// <summary>
		/// Checks if the matrix is a char matrix then converts it to a TH1C
		/// </summary>
		/// <returns></returns>
		TH1C* toTH1C(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, int weight = 1) {
			//if (!isChar())
				//throw std::invalid_argument("Matrix is of wrong type");
			TH1C* temp = new TH1C(name, title, nbinsx, xlow, xup);
			fillHistogram(temp, weight);
			return temp;
		}
#endif 

#ifdef ROOT_TH1K
		// k neighbour class TODO : read through ROOT documentation more to use see how it differs from the other TH1
#endif 

#endif

#ifdef ROOT_TH2

		/// <summary>
		/// Fills a histogram with each row of the matrix
		/// </summary>
		/// <returns></returns>
		template<typename HistT>
		void fill2DHistogram(HistT hist, int weight) {
			for (int i = 0; i < inner_.size(); i++)
				if (inner_[i] > 0)
					hist->Fill(i / dimx_, i % dimy_, weight);
		}

		/// <summary>
		/// Convets the matrix to a TH2, uses each element and fills the each bin with a weight that is equal to the element
		/// </summary>
		/// <returns></returns>
		TH2* toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			TH2* temp = new TH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
			for (int i = 0; i < inner_.size(); i++)
				if (inner_[i] > 0)
					temp->Fill(i / dimx_, i % dimy_, inner_[i]); // uses the element as the weight
			return temp;
		}

#ifdef ROOT_TH2F
		/// <summary>
		/// Checks if the matrix is a float matrix then converts it to a TH2F
		/// </summary>
		/// <returns></returns>
		TH2F* toTH2F(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			//if (!)
				//throw std::invalid_argument("Matrix is of wrong type");
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2D
		/// <summary>
		/// Checks if the matrix is a double matrix then converts it to a TH2D
		/// </summary>
		/// <returns></returns>
		TH2D* toTH2D(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			//if (!isDouble())
				//throw std::invalid_argument("Matrix is of wrong type");
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2S
		/// <summary>
		/// Checks if the matrix is a short matrix then converts it to a TH2S
		/// </summary>
		/// <returns></returns>
		TH2S* toTH2S(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			//if (!isShort())
				//throw std::invalid_argument("Matrix is of wrong type");
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2I
		/// <summary>
		/// Checks if the matrix is a int32 matrix then converts it to a TH2I
		/// </summary>
		/// <returns></returns>
		TH2I* toTH2I(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			//if (!isInt32())
				//throw std::invalid_argument("Matrix is of wrong type");
			return toTH2(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup);
		}
#endif

#ifdef ROOT_TH2C
		/// <summary>
		/// Checks if the matrix is a char matrix then converts it to a TH2C
		/// </summary>
		/// <returns></returns>
		TH2C* toTH2C(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup,
			Int_t nbinsy, Double_t ylow, Double_t yup) {
			//if (!isChar())
				//throw std::invalid_argument("Matrix is of wrong type");
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

		/// <summary>
		/// New copy constructor for copying the TMatrix class
		/// </summary>
		/// <returns></returns>
		Matrix(TMatrix tMatrix)
			: dimx_(tMatrix.GetNrows()), dimy_(tMatrix.GetNcols()) {
			if (!typeid(T).name() == "Float_T")
				throw std::invalid_argument("Matrix is of wrong type");
			inner_.resize(dimx_ * dimy_);
			inner_ = tMatrix.GetMatrixArray();
		}

		/// <summary>
		/// Overrides a cast to TMatrix
		/// </summary>
		/// <returns></returns>
		operator TMatrix() const {
			TMatrix temp(dimx_, dimy_);
			for (int i = 0; i < inner_.size(); i++)
				temp[i % dimx_][i / dimy_] = inner_[i];
			return temp;
		}

		/// <summary>
		/// Overrides the = operator for making the Matrix<T> = root::TMatrix
		/// </summary>
		/// <returns></returns>
		Matrix<T>& operator=(TMatrix arg) {
			return Matrix(arg);
		}

		/// <summary>
		/// Checks if the matrix is a char matrix then converts it to a TH2C
		/// </summary>
		/// <returns></returns>
		TMatrix toTMatrix() {
			return static_cast<TMatrix>(*this);
		}

#endif

		/// <summary>
		/// New copy constructor for copying the TMatrixT<T> class
		/// </summary>
		/// <returns></returns>
		Matrix(TMatrixT<T> tMatrix)
			: dimx_(tMatrix.GetNrows()), dimy_(tMatrix.GetNcols()) {
			inner_.resize(dimx_ * dimy_);
			inner_ = tMatrix.GetMatrixArray();
		}

		/// <summary>
		/// Adds a new function to convert this Matrix<T> to a TMatrixT<T>
		/// </summary>
		/// <returns></returns>
		TMatrixT<T> toTMatrixT() {
			TMatrixT<T> temp((Int_t)dimx_, (Int_t)dimy_);
			for (int i = 0; i < inner_.size(); i++)
				temp[i % dimx_][i / dimy_] = inner_[i];
			return temp;
		}

		/// <summary>
		/// Overrides a cast to TMatrixT
		/// </summary>
		/// <returns></returns>
		operator TMatrixT<T>() const {
			return this->toTMatrixT();
		}

		/// <summary>
		/// Overrides a cast to TMatrixT<T>
		/// </summary>
		/// <returns></returns>
		Matrix<T>& operator=(TMatrixT<T> arg) {
			return Matrix<T>(arg);
		}

#endif

#ifdef EIGEN_MATRIX_H 

		/// <summary>
		/// A new copy constructor for the 
		/// </summary>
		/// <returns></returns>
		Matrix(Eigen::Matrix<T, int, int> eigenMatrix) {
			// must already be the same size as this matrix
			inner_.resize(eigenMatrix.rows() * eigenMatrix.cols());
			for (int i = 0; i < inner_.size(); i++)
				*this->add(temp[i % dimx_][i / dimy_], i % dimx_, i / dimy_);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Eigen::Matrix<T, dimy_, dimx_> toEigenMatrix() {
			Eigen::Matrix<T, dimy_, dimx_> temp;
			for (int i = 0; i < inner_.size(); i++)
				temp[i % dimx_][i / dimy_] = inner_[i];
			return temp;
		}

		/// <summary>
		/// Overrides a cast to the Eigen::Matrix class
		/// </summary>
		/// <returns></returns>
		operator Eigen::Matrix<T, dimy_, dimx_>() const {
			return *this->toEigenMatrix();
		}

		/// <summary>
		/// Overrides a cast to TMatrixT<T>
		/// </summary>
		/// <returns></returns>
		Matrix<T>& operator=(Eigen::Matrix<T, dimy_, dimx_> arg) {
			return Matrix<T>(arg);
		}
#endif

	private:
		/// <summary>
		/// Checks if the type of the matrix is an int32
		/// </summary>
		/// <returns></returns>
		bool isInt32() {
			return typeid(T).name() == "__int32" || typeid(T).name() == "int32_t";
		}

		/// <summary>
		/// Checks if the type of the matrix is a double
		/// </summary>
		/// <returns></returns>
		bool isDouble() {
			return typeid(T).name() == "double" || typeid(T).name() == "Double_t" || typeid(T).name() == "double_t";
		}

		/// <summary>
		/// Checks if the type of the matrix is a float
		/// </summary>
		/// <returns></returns>
		bool isFloat() {
			return typeid(T).name() == "float" || typeid(T).name() == "float_t" || typeid(T).name() == "Float_t";
		}

		/// <summary>
		/// Checks if the type of the matrix is a short
		/// </summary>
		/// <returns></returns>
		bool isShort() {
			return typeid(T).name() == "short" || typeid(T).name() == "Short_t";
		}

		/// <summary>
		/// Checks if the type of the matrix is a char
		/// </summary>
		/// <returns></returns>
		bool isChar() {
			return typeid(T).name() == "char" || typeid(T).name() == "Char_t";
		}

		/// <summary>
		/// Checks if a passed matrix is the same size as one passed through
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		bool isOutOfRange(Matrix<T> arg) {
			return arg.dimx_ > dimx_ || arg.dimy_ > dimy_; // assumes the vector cannot have - indexs
		}

		/// <summary>
		/// Check if the number col,row is the same as rows,columns
		/// </summary>
		/// <param name="col">Columns to check</param>
		/// <param name="row">Rows to check</param>
		/// <returns></returns>
		bool isOutOfRange(int col, int row) {
			return col > dimx_ || row > dimy_ || col < 0 || row < 0;
		}

		/// <summary>
		/// Gets a row at the specified index
		/// </summary>
		/// <param name="row"></param>
		/// <returns></returns>
		/// <remarks>returns a reference to a temp variable</remarks>
		std::vector<T> getRow(int row) {
			if (row > dimy_)
				throw std::out_of_range("Index out of range");
			std::vector<T> temp;
			for (int i = 0; i < dimx_; i++)
				temp.push_back(inner_[i * dimy_]);
			return temp;
		}

		/// <summary>
		/// Gets a whole column at the specified index
		/// </summary>
		/// <param name="row"></param>
		/// <returns></returns>
		std::vector<T> getColumn(int column) {
			if (column > dimx_)
				throw std::out_of_range("Index out of range");
			std::vector<T> temp;
			for (int i = 0; i < dimx_; i++)
				temp.push_back(inner_[i] + dimx_ * i);
			return temp;
		}

		/// <summary>
		/// Multiplies two matricies and sends creates a new on called out
		/// </summary>
		/// <param name="matrixOne"></param>
		/// <param name="matrixTwo"></param>
		/// <param name="out"></param>
		/// TODO : Does not work, need to refactor
		void multiply(Matrix<T> matrixOne, Matrix<T> matrixTwo, Matrix<T>& out) {
			for (int x = 0; x < matrixOne.dimx_; x++) {
				for (int y = 0; y < matrixTwo.dimx_; y++) {
					int dotProduct = 0;
					for (int i = 0; i < matrixOne.dimx_; i++) {
						int matrixRow = matrixOne.getRow(x)[i];
						dotProduct += matrixOne.getRow(x)[i] * matrixTwo.getRow(y)[i];
					}
					out.add(dotProduct, x, y);
				}
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="matrix"></param>
		/// <param name="row"></param>
		/// <param name="col"></param>
		/// <returns></returns>
		Matrix<T> createSubMatrix(Matrix<T> matrix, int elimRow, int elimCol) {
			Matrix<T> temp(matrix.dimx_ - 1, matrix.dimx_ - 1);
			for (int i = 0; i < matrix.size(); i++) { //Copy only those elements which are not in given row r and column c: 
				int row = i / matrix.dimy_; int col = i % matrix.dimx_;
				if (row != elimRow && col != elimCol) {
					if (row > elimRow)
						row -= 1;
					if (col > elimCol)
						col -= 1;
					temp.add(matrix.inner_[i], row, col); //If row is filled increase r index and reset c index
				}
			}
			return temp;
		}

		// TODO : rename all the one letter variables to something actually meaningful and useful

		/// <summary>
		/// Gets the determinant of the matrix
		/// </summary>
		/// <param name="matrix">The matrix to inverse</param>
		/// <param name="matrixHeight">The height of the matrix, aka how many elements in the column</param>
		/// <returns></returns>
		std::string determinant(Matrix<T> matrix, int matrixHeight) { //to find determinant 
			if (matrix.dimx_ != matrix.dimy_)
				throw std::out_of_range("Bro wot doing??");
			std::string det = "";
			if (matrixHeight == 2) 
				return "(" + std::to_string(matrix.getAt(0, 0)) 
				+ " * " 
				+ std::to_string(matrix.getAt(1, 1))  + ")"
				+ " - (" 
				+ std::to_string(matrix.getAt(1, 0)) 
				+ " * " 
				+ std::to_string(matrix.getAt(0, 1)) 
				+ ") ";
			for (int colElem = 0; colElem < matrixHeight; colElem++)
				det += "* " + getCofactor(0, colElem, matrix) + " * " + std::to_string(matrix[0][colElem]) + " ";
			return det;
		}
		
		/// <summary>
		/// Creates an adjoint matrix using asj
		/// </summary>
		/// <param name="M">The matrix to inverse</param>
		/// <param name="adj">The adjoint matrix, another out matrix</param>
		void adjoint(Matrix<T>& M, Matrix<T>& adj) {
			////to find adjoint matrix 
			//if (M.size() == 1) {
			//	adj.getAt(0, 0) = 1;
			//	return;
			//}
			//int s = 1;
			//Matrix<T> t(M.size(), M.size());
			//for (int i = 0; i < M.size(); i++) {
			//	for (int j = 0; j < M.size(); j++) {
			//		//To get cofactor of M[i][j]
			//		getCofactor(M, t, i, j, M.size());
			//		s = ((i + j) % 2 == 0) ? 1 : -1; //sign of adj[j][i] positive if sum of row and column indexes is even.
			//		adj.add(j, i, (s) * (determinant(t, dimx_() - 1))); //Interchange rows and columns to get the transpose of the cofactor matrix
			//	}
			//}
		}

		/// <summary>
		/// Inverts the matrix
		/// </summary>
		/// <param name="M">The matrix to inverse</param>
		/// <param name="inv">The inverse aka the out matrix</param>
		/// <returns></returns>
		bool inverse(Matrix<T> M, Matrix<T>& inv) {
			//// fix later
			////if (!(isInt32() || isDouble() || isFloat() || isShort()))
			//	//throw std::invalid_argument("The matrix is not a valid type");
			//int det = determinant(M, M.dimx_);
			//if (det == 0) {
			//	//throw std::domain_error("Cannot find inverse");
			//	return false;
			//}
			//Matrix<T> adj(M.size(), M.size());
			//adjoint(M, adj);
			//for (int i = 0; i < M.size(); i++)
			//	for (int j = 0; j < M.size(); j++)
			//		inv.add(i, j, adj.getAt(i, j) / T(det));
			//return true;
		}

		// TODO : refactor so it's much better code
		// outputs the matrix in text format
		friend std::ostream& operator<<(std::ostream& os, Matrix<T>& matrix) {
			std::string builder = "";
			for (int loop = 0; loop < matrix.vecSize(); loop++) {
				if (loop % matrix.dimx_ == 0 && loop != 0) {
					builder += "\n";
				}
				builder += "(" + std::to_string(matrix.getAt(loop % matrix.dimx_, loop / matrix.dimy_)) + ") ";
			}
			os << builder;
			return os;
		}
	};
}
