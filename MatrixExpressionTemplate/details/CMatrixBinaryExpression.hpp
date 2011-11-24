/*
 * Name  : MatrixBinaryExpression
 * Path  : 
 * Use   : Implements a binary expression for matrices
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once

#include "details/CMatrixRowBinaryExpression.hpp"
#include "details/cmatrix_binary_operator_traits.h"

#define CMATRIXBINARYEXPRESSION_H

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
class CMatrixBinaryExpression {
public:
    // rows and cols depends on the operation. It is different for matrix addition
    // than it is for matrix multiplication.
    enum {rows = cmatrix_binary_operator_traits<BINARY_OPERATOR<T, OP1, OP2>>::rows, cols = cmatrix_binary_operator_traits<BINARY_OPERATOR<T, OP1, OP2>>::cols};

public:
    CMatrixBinaryExpression(typename type_traits<OP1>::RefType op1, typename type_traits<OP2>::RefType op2);

    // Return a row vector that acts as proxy so we can write a[row][col]
    CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> operator[](int row);

    // When a[i][j] appears on the r.h.s.
    // Return a row vector that acts as proxy so we can write a[row][col]
    CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const operator[](int row) const;

private:
    // We use type_traits here because Matrix objects should be held as references as
    // copy-by-value is expensive. MatrixBinaryExpression on the other hand should be
    // copied by value. This is because if a MatrixBinaryExpression holds a Matrix, it
    // is already kept as reference, so deep copies if MatrixBinaryExpression are cheap.
    typename type_traits<OP1>::RefType const op1_;
    typename type_traits<OP2>::RefType const op2_;
};

#include "details/CMatrixBinaryExpression_detail.h"
