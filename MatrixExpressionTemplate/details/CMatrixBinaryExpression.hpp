/*
 * Name  : MatrixBinaryExpression
 * Path  : 
 * Use   : Implements a binary expression for matrices
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once

#include "details/CMatrixRowBinaryExpression.hpp"

#define CMATRIXBINARYEXPRESSION_H

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
class MatrixBinaryExpression {
public:
    typedef MatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR> RefType;
    typedef typename OP1::value_type                          value_type;

public:
    MatrixBinaryExpression(typename OP1::RefType op1, typename OP2::RefType op2);

    // Return a row vector that acts as proxy so we can write a[row][col]
    CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR> operator[](int row);

    // When a[i][j] appears on the r.h.s.
    CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR> const operator[](int row) const;

private:
    // We use type_traits here because Matrix objects should be held as references as
    // copy-by-value is expensive. MatrixBinaryExpression on the other hand should be
    // copied by value. This is because if a MatrixBinaryExpression holds a Matrix, it
    // is already kept as reference, so deep copies if MatrixBinaryExpression are cheap.
    typename OP1::RefType const op1_;
    typename OP2::RefType const op2_;

    // Store binary operator
    BINARY_OPERATOR                          op_;
};

#include "details/CMatrixBinaryExpression_detail.h"
