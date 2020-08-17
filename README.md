# Matrix
A simple matrix class that's compatible with STL functions and CERNs ROOT library. Includes functions for + - * /,  inverting, normalisation, eigenvalues, the trace and transpose.
The whole idea of this repository is to have a reusable class for creating and computing matracies that utilise the abilities of STL and is also compatible with CERNs ROOT library for cpp.
When viewing and/or using the code please keep in mind I am only a fresh grad and not an experienced software dev, I also have fairly limited knowledge with ROOT so any advice or mistakes that you spot please don't hesitate to contact me.

### Prerequisites

Knowledge of C++, ROOT and STL.

### Installing

Add the header file to your project, use as you want

## Usage

```cpp
// create a matrix<int> and fill it
matracies::Matrix<int> matrix(rows, columns);
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

## Authors

Felix England

## Acknowledgments

* 
