# Matrix
A simple matrix class that's compatible with STL functions and CERNs ROOT library. Includes functions for + - * /,  inverting, normalisation, eigenvalues, the trace and transpose.
The whole idea of this repository is to have a reusable class for creating and computing matracies that utilise the abilities of STL and is also compatible with CERNs ROOT library for cpp.
When viewing and/or using the code please keep in mind I am only a fresh grad and not an experienced software dev, I also have fairly limited knowledge with ROOT so any advice or mistakes that you spot please don't hesitate to contact me.

### Prerequisites

Knowledge of C++, ROOT and STL.

### Installing

Add the header file to your project, use as you want

## Usage

To use the Matrix.h will all the capabilities of ROOT and Eigen::Matrix, you need to include these header files in the Matrix.h underneath my includes. If compiling with root through the commandline there should be no need to include the root library.

### To create a matrix, fill it and then output it to console

Creating matrices of different types

```cpp
// all matrcies are of 5x5, that is 5 rows by 5 columns

// matrix made from default int
matrices::Matrix<int> intMatrix(5, 5);
// uses ROOT Int_t
matrices::Matrix<Int_t> int_tMatrix(5, 5);
// uses default float type
matrices::Matrix<float> floatMatrix(5, 5);
// ROOT Float_t
matrices::Matrix<Float_t> float_tMatrix(5, 5);
// default double
matrices::Matrix<double> doubleMatrix(5, 5);
// ROOT Double_t
matrices::Matrix<Double_t> double_tMatrix(5, 5);
```



In this example we create an integer matrix, fill it with '5' and then output it to the console.

```cpp
// create a matrix<int> and fill it
matrices::Matrix<int> matrix(rows, columns);
matrix.fill(5);
std::cout << matrix;

/*
Output:

(5) (5) (5) (5) (5)
(5) (5) (5) (5) (5)
(5) (5) (5) (5) (5)
(5) (5) (5) (5) (5)
(5) (5) (5) (5) (5)
*/
```

Creating two matrcies then adding them together 

```cpp
matrices::Matrix<int> intMatrixOne(5, 5);
matrices::Matrix<int> intMatrixTwo(5, 5);

intMatrixOne.fill(5);
intMatrixTwo.fill(10);

matrices::Matrix<int> sumOf(5, 5);

sumOf = intMatrixOne + intMatrixTwo;

std::cout << sumOf;

/*
Output:

(15) (15) (15) (15) (15)
(15) (15) (15) (15) (15)
(15) (15) (15) (15) (15)
(15) (15) (15) (15) (15)
(15) (15) (15) (15) (15)
*/
```

Matrix multiplication

```cpp
matrices::Matrix<int> productOf(5, 5);
productOf = intMatrixOne * intMatrixTwo;

std::cout << productOf;

/*
Output:

(250) (250) (250) (250) (250)
(250) (250) (250) (250) (250)
(250) (250) (250) (250) (250)
(250) (250) (250) (250) (250)
(250) (250) (250) (250) (250)
*/
```

Getting the determinant of the martrix. The deteminant will be 0 for this matrix because it has repeating rows

```cpp
int det = productOf.getDeterminant();
std::cout << det;

/*
Output: 

0
*/
```

Getting the inverse of the matrix *Not fully implemeneted*

```cpp

intMarixOne.invert();

std::cout << intMatrixOne;

/*
Output:


*/
```

#Compatibility with ROOT

The Matrix<T> class is fully compatible with ROOT TMatrix and ROOT TMatrixT<T>, to convert the matrix from a Matrix<T> to a TMatrixT<T> you only need the .toTMatrixT() function, same as to copy a TMatrixT into a new Matrix<T> you can simply use it in the constructor.

```cpp
matrices::Matrix<int> matrix(5, 5);
tMatrix.fill(5);

TMatrixT<int> tMatrix = matrix.toTMatrixT();

// to copy the TMatrixT<T> into a new Matrix<T>
TMatrixT<int> newTMatrix; // we're just going to pretend we have data in here
matrices::Matrix<int> newMatrix(newTMatrix);

std::cout << newMatrix;

/*
Output:

The elements within the TMatrixT<T>
*/
```

Creating histograms from the matrix class, you can easily just create a TH1 from the matrix, it uses each row in the vector to fill the bins

```cpp
TH1F* newHistF = productOf.toTH1F("TH1F Test", "TH1F Test", 5, 0, 5);
	newHistF->Draw();
```

## Known issues

When using the code it is important to make note that the class is provided as is. I am always welcome to feedback, recommendations for features and bug reports but please do not think this is a professionally made class that is actively maintained. For known issues please refer to the github issues page.

## Authors

Felix England

Nuno Taborda

## Acknowledgments

* 
