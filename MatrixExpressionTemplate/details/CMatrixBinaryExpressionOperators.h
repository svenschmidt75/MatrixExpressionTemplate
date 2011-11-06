/*
 * Name  : CMatrixBinaryExpressionOperators
 * Path  : 
 * Use   : Implements binary operators for matrix objects
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once


template<typename OP1, typename OP2, int COLS>
struct MATRIX_PLUS {
    typename OP1::value_type operator()(typename OP1::RefType const op1, typename OP2::RefType const op2, int row, int col) const {
        typedef typename OP1::value_type T;

        T tmp = 0;

        for (int k = 0; k < COLS; ++k) {
            T tmp1 = op1[row][k];
            T tmp2 = op2[k][col];
            tmp += (tmp1 + tmp2);
        }

        return tmp;
    }

};

template<typename T, int ROWS, int COLS>
CMatrixBinaryExpression<CMatrix<T, ROWS, COLS>, CMatrix<T, ROWS, COLS>, MATRIX_PLUS<CMatrix<T, ROWS, COLS>, CMatrix<T, ROWS, COLS>, COLS> >
operator+(CMatrix<T, ROWS, COLS> const & op1, CMatrix<T, ROWS, COLS> const & op2) {
    // Check that op1::type and op2::type and T are compatible via concepts

    return CMatrixBinaryExpression<CMatrix<T, ROWS, COLS>, CMatrix<T, ROWS, COLS>, MATRIX_PLUS<CMatrix<T, ROWS, COLS>, CMatrix<T, ROWS, COLS>, COLS> >(op1, op2);
}
