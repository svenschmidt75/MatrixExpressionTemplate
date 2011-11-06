/*
 * Name  : CMatrixBinaryExpressionOperators
 * Path  : 
 * Use   : Implements binary operators for matrix objects
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once


template<typename T>
class MATRIX_PLUS {

};

template<typename T, int ROWS, int COLS>
CMatrixBinaryExpression<CMatrix<T, ROWS, COLS>, CMatrix<T, ROWS, COLS>, MATRIX_PLUS<T> >
operator+(CMatrix<T, ROWS, COLS> const & op1, CMatrix<T, ROWS, COLS> const & op2) {
    // Check that op1::type and op2::type and T are compatible via concepts

    return CMatrixBinaryExpression<CMatrix<T, ROWS, COLS>, CMatrix<T, ROWS, COLS>, MATRIX_PLUS<T> >(op1, op2);
}
