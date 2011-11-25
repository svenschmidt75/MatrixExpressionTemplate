/*
 * Name  : Matrix
 * Path  : 
 * Use   : Implements a matrix
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once

#include "details/type_traits.h"
#include "details/CMatrixRow.hpp"

#include <boost/shared_array.hpp>

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
class CMatrixBinaryExpression;


#define CMATRIX_H

template<typename T, int ROWS, int COLS>
class CMatrix {
public:
    enum {rows = ROWS, cols = COLS};

public:
    CMatrix();

    // Assignment operator
    CMatrix& operator=(typename type_traits<CMatrix<T, rows, COLS>>::RefType& in);

    template<typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
    CMatrix& operator=(CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const & in);

    // Return a row vector that acts as proxy so we can write a[row[col]
    CMatrixRow<T, COLS> operator[](int row);

    // When a[i][j] appears on the r.h.s.
    CMatrixRow<T, COLS> const operator[](int row) const;

private:
    boost::shared_array<T> buffer_;
};

// Internal implementation details
#include "details/CMatrix_detail.h"

// Matrix operators
#include "details/CMatrixBinaryExpressionOperators.h"

// Matrix binary expressions
#include "details/CMatrixBinaryExpression.hpp"
