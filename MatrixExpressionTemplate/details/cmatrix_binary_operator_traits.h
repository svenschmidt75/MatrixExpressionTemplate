/*
 * Name  : cmatrix_binary_operator_traits
 * Path  : 
 * Use   : Abstraction for types. Advantage is that we only need to change type_traits, not where it is used.
 *         If no type_traits is used, we would have to change all occurrences individually.
 * Author: Sven Schmidt
 * Date  : 11/24/2011
 */
#pragma once

#include "details/CMatrixBinaryExpressionOperators.h"

// Forward declarations
template<typename T, int ROWS, int COLS>
class CMatrix;


template<typename BINARY_OPERATOR>
struct cmatrix_binary_operator_traits {};

// Full specialization for matrix addition: Matrix + Matrix
template<typename T, int ROWS, int COLS>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrix<T, ROWS, COLS>,
        CMatrix<T, ROWS, COLS>
    >
> {
    // We no not use static const int here, as that would mean we have to create an instance
    // of this type in order to reserve the memory for these variables. Using an enum instead
    // avoids this.
    enum {rows = ROWS, cols = COLS};
};

// Full specialization for matrix addition: Matrix + MatrixExpr
template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_PLUS<
    T,
    CMatrix<T, ROWS, COLS>,
    CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>
    >
> {
    // We no not use static const int here, as that would mean we have to create an instance
    // of this type in order to reserve the memory for these variables. Using an enum instead
    // avoids this.
    enum {rows = ROWS, cols = COLS};
};
