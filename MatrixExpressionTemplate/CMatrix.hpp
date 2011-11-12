/*
 * Name  : Matrix
 * Path  : 
 * Use   : Implements a matrix
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once

#include "details\CMatrixRow.hpp"

#include <boost/shared_array.hpp>

#define CMATRIX_H

template<typename T, int ROWS, int COLS>
class CMatrix {
private:
    template<typename T, int ROWS, int COLS>
    struct type_traits_ {
        typedef T value_type;
    };

public:
    typedef CMatrix<T, ROWS, COLS> RefType;
    typedef type_traits_<T, COLS, ROWS> type_traits;

public:
    CMatrix();

    // Return a row vector that acts as proxy so we can write a[row[col]
    CMatrixRow<T, COLS> operator[](int row);

    // When a[i][j] appears on the r.h.s.
    CMatrixRow<T, COLS> const operator[](int row) const;

private:
    boost::shared_array<T> buffer_;
};

#include "details/cmatrix_detail.h"

// Matrix binary expressions
#include "details/CMatrixBinaryExpression.hpp"

// Matrix operators
#include "details/CMatrixBinaryExpressionOperators.h"
