// matrix1:
/*
Key Design NotesFlat
1D Vector: Instead of using a slow, fragmented std::vector<std::vector<T>>,
a flat array or vector is preferred for raw computing performance. It
speeds up cache access due to contiguous memory spatial locality.
Function Overload operator(): Prior to C++23, the classic array index
operator (operator[]) could only accept one parameter. Therefore, standard
custom matrix classes overload the parenthesis operator () to accept multiple
parameters like matrix(row, col).

Const Correctness: Both operator() and individual methods like print() have duplicated
const variations. This allows the Matrix instances to be safely passed around as
read-only references (const Matrix<T>&).
*/

#include "matrix1.h"
#include <stdexcept>

int main() {
    try {
        // TODO: Initialize a 2x3 matrix with different initial values
        same answer as one below.

        // TODO: Create a 2x3 matrix: 1,2,3 (row1) and 4,5,6 (row2).
        Matrix1<int> mat1(2,3);
        mat1(0,0) = 1;
        mat1(0,1) = 2;
        mat1(0,2) = 3;
        mat1(1,0) = 4;
        mat1(1,1) = 5;
        mat1(1,2) = 6;


        // TODO: Create a second matrix. It may have any values you choose
        //       and should be configured so that matrix multiplication may
        //       be performed.
        Matrix1<int> mat2(3,2);
        mat2(0,0) = 1;
        mat2(0,1) = 2;
        mat2(1,0) = 3;
        mat2(1,1) = 4;
        mat2(2,0) = 5;
        mat2(2,1) = 6;

        Matrix1


        std::cout << "Matrix A :\n"; mat1.print();
        std::cout << "\nMatrix B :\n"; mat2.print();

        Matrix1<int> result = mat1 * mat2;
        std::cout << "\nResult of A * B :\n"; result.print();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
