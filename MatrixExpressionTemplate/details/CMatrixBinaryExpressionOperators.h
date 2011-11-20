/*
 * Name  : CMatrixBinaryExpressionOperators
 * Path  : 
 * Use   : Implements binary operators for matrix objects
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once

namespace CMatrix_NS {

    template<typename OP1, typename OP2>
    struct MATRIX_PLUS {
        static const int rows = type_traits<OP1>::rows;
        static const int cols = type_traits<OP1>::cols;

        typename type_traits<OP1>::value_type operator()(typename type_traits<OP1>::RefType const op1, typename type_traits<OP2>::RefType const op2, int row, int col) const {
            typedef typename type_traits<OP1>::value_type T;

            T tmp = 0;

            for (int k = 0; k < COLS; ++k) {
                T tmp1 = op1[row][k];
                T tmp2 = op2[k][col];
                tmp += (tmp1 + tmp2);
            }

            return tmp;
        }

        static void check_types() {
            // For matrix addition, both cols and rows have to the same same for
            // lhs and rhs.
            static_assert(type_traits<OP1>::rows == type_traits<OP2>::rows, "rows mismatch in MATRIX_PLUS");
            static_assert(type_traits<OP1>::cols == type_traits<OP2>::cols, "cols mismatch in MATRIX_PLUS");
        }

    };

}

/*******************
 * Matrix + Matrix *
 *******************/
 
template<typename T, int ROWS, int COLS>
CMatrixBinaryExpression<CMatrix<T, ROWS, COLS>, CMatrix<T, ROWS, COLS>, CMatrix_NS::MATRIX_PLUS<CMatrix<T, ROWS, COLS>, CMatrix<T, ROWS, COLS>> >
operator+(CMatrix<T, ROWS, COLS> const & op1, CMatrix<T, ROWS, COLS> const & op2) {
    typedef CMatrix<T, ROWS, COLS> LHSType;
    typedef CMatrix<T, ROWS, COLS> RHSType;

    // Check that the value types are compatible
//    static_assert(std::is_convertible<typename type_traits<MatrixType>::value_type, typename type_traits<MatrixType>::value_type>::value, "CMatrixBinaryExpression: Incompatible types");

    // When doing addition, both matrices need to have the same number of columns and rows. This
    // is enforced by the compiler as both matrices, that are to be added, have the same type,
    // including ROWS and COLS.
    return CMatrixBinaryExpression<LHSType, RHSType, CMatrix_NS::MATRIX_PLUS<LHSType, RHSType> >(op1, op2);
}

/***********************************
 * Matrix + MatrixBinaryExpression *
 ***********************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixBinaryExpression<CMatrix<T, ROWS, COLS>, CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>, CMatrix_NS::MATRIX_PLUS<CMatrix<T, ROWS, COLS>, CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>> >
operator+(CMatrix<T, ROWS, COLS> const & op1, CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR> const & op2) {
    typedef CMatrix<T, ROWS, COLS> LHSType;
    typedef CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR> RHSType;

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "CMatrixBinaryExpression: Incompatible types");

    // Here, we need to make sure that lhs and rhs have the same number of columns and rows.
    static_assert(type_traits<LHSType>::rows == type_traits<RHSType>::rows, "CMatrixBinaryExpression: Incompatible types");
    static_assert(type_traits<LHSType>::cols == type_traits<RHSType>::cols, "CMatrixBinaryExpression: Incompatible types");

    return CMatrixBinaryExpression<LHSType, RHSType, CMatrix_NS::MATRIX_PLUS<LHSType, RHSType> >(op1, op2);
}
