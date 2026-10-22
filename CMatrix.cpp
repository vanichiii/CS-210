#include "CMatrix.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;

CMatrix::CMatrix(std::size_t rows, std::size_t columns, int initialValue)
    : rowCount(rows), columnCount(columns), data(nullptr)
{
    if (rows == 0 || columns == 0)
        throw std::invalid_argument("Matrix dimensions must be positive");

    data = static_cast<int*>(std::malloc(rows * columns * sizeof(int)));
    if (data == nullptr)
        throw std::bad_alloc();

    int* current = data;
    int* const end = data + rows * columns;
    while (current != end)
    {
        *current = initialValue;
        ++current;
    }
}

CMatrix::CMatrix(const CMatrix& other)
    : rowCount(other.rowCount),
      columnCount(other.columnCount),
      data(static_cast<int*>(
          std::malloc(other.rowCount * other.columnCount * sizeof(int))))
{
    if (data == nullptr)
        throw std::bad_alloc();

    const int* source = other.data;
    const int* const sourceEnd = other.data + rowCount * columnCount;
    int* destination = data;

    while (source != sourceEnd)
    {
        *destination = *source;
        ++source;
        ++destination;
    }
}

CMatrix::~CMatrix()
{
    std::free(data);
}

CMatrix& CMatrix::operator=(const CMatrix& other)
{
    if (this != &other)
    {
        int* replacement = static_cast<int*>(
            std::malloc(other.rowCount * other.columnCount * sizeof(int)));
        if (replacement == nullptr)
            throw std::bad_alloc();
        const int* source = other.data;
        const int* const sourceEnd =
            other.data + other.rowCount * other.columnCount;
        int* destination = replacement;

        while (source != sourceEnd)
        {
            *destination = *source;
            ++source;
            ++destination;
        }

        std::free(data);
        data = replacement;
        rowCount = other.rowCount;
        columnCount = other.columnCount;
    }

    return *this;
}

CMatrix CMatrix::add(const CMatrix& other) const
{
    if (rowCount != other.rowCount || columnCount != other.columnCount)
        throw std::invalid_argument("Matrices must have matching dimensions");

    CMatrix result(rowCount, columnCount);
    const int* left = data;
    const int* right = other.data;
    const int* const end = data + rowCount * columnCount;
    int* output = result.data;

    while (left != end)
    {
        *output = *left + *right;
        ++left;
        ++right;
        ++output;
    }

    return result;
}

CMatrix CMatrix::subtract(const CMatrix& other) const
{
    if (rowCount != other.rowCount || columnCount != other.columnCount)
        throw std::invalid_argument("Matrices must have matching dimensions");

    CMatrix result(rowCount, columnCount);
    const int* left = data;
    const int* right = other.data;
    const int* const end = data + rowCount * columnCount;
    int* output = result.data;

    while (left != end)
    {
        *output = *left - *right;
        ++left;
        ++right;
        ++output;
    }

    return result;
}

CMatrix CMatrix::multiply(const CMatrix& other) const
{
    if (columnCount != other.rowCount)
        throw std::invalid_argument("Inner matrix dimensions must match");

    CMatrix result(rowCount, other.columnCount);

    for (std::size_t row = 0; row < rowCount; ++row)
    {
        for (std::size_t column = 0; column < other.columnCount; ++column)
        {
            int sum = 0;
            const int* left = data + row * columnCount;
            const int* right = other.data + column;

            for (std::size_t position = 0;
                 position < columnCount;
                 ++position)
            {
                sum += *left * *right;
                ++left;
                right += other.columnCount;
            }

            *(result.data + row * result.columnCount + column) = sum;
        }
    }

    return result;
}

CMatrix CMatrix::transpose() const
{
    CMatrix result(columnCount, rowCount);

    for (std::size_t row = 0; row < rowCount; ++row)
    {
        for (std::size_t column = 0; column < columnCount; ++column)
        {
            *(result.data + column * result.columnCount + row) =
                *(data + row * columnCount + column);
        }
    }

    return result;
}

std::size_t CMatrix::getRows() const
{
    return rowCount;
}

std::size_t CMatrix::getColumns() const
{
    return columnCount;
}

int CMatrix::get(std::size_t row, std::size_t column) const
{
    requireValidPosition(row, column);
    return *(data + offset(row, column));
}

void CMatrix::set(std::size_t row, std::size_t column, int value)
{
    requireValidPosition(row, column);
    *(data + offset(row, column)) = value;
}

std::size_t CMatrix::offset(std::size_t row, std::size_t column) const
{
    return row * columnCount + column;
}

void CMatrix::requireValidPosition(std::size_t row, std::size_t column) const
{
    if (row >= rowCount || column >= columnCount)
        throw std::out_of_range("Matrix position is outside its dimensions");
}

void print(const CMatrix& matrix) {
    size_t rows = matrix.getRows();
    size_t columns = matrix.getColumns();
    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            cout << matrix.get(row, column) << ' ';
        }
        cout << endl;
    }
}
int main() {
    CMatrix matrix1(2, 4, 1);
    CMatrix matrix2(4, 2, 0);

    // TODO: Call to multiply matrices
    CMatrix matrix3 = matrix1.multiply(matrix2);

    print(matrix1);
    print(matrix2);
    print(matrix3);

}