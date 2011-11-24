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

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
class CMatrixBinaryExpression;


template<typename BINARY_OPERATOR>
struct cmatrix_binary_operator_traits {};


/************************************************************/
/* Full specialization for matrix addition: Matrix + Matrix */
/************************************************************/

/* Note that we explicitly allow for the matrices to have different rows and cols.
 * Although this is an invalid combination for addition, the static_asserts will
 * issue a user-friendly error message. If we were to only allow for the same
 * ROWS and COLS, i.e.
 *              template<typename T, int ROWS, int COLS>
 * and the user passes in matrices of different type, the compiler would try to
 * find a match for cmatrix_binary_operator_traits and would find the one above,
 * that is the fall back. Since it doesn't have rows/cols defined, the user ends
 * up with a cryptic error message.
 */
template<typename T, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrix<T, ROWS_A, COLS_A>,
        CMatrix<T, ROWS_B, COLS_B>
    >
> {
    typedef CMatrix<T, ROWS_A, COLS_A> LHSType;
    typedef CMatrix<T, ROWS_B, COLS_B> RHSType;

    // Ensure the matrices are compatible
    static_assert(LHSType::rows == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(LHSType::cols == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // We no not use static const int here, as that would mean we have to create an instance
    // of this type in order to reserve the memory for these variables. Using an enum instead
    // avoids this.
    enum {rows = ROWS_A, cols = COLS_A};
};



/****************************************************************/
/* Full specialization for matrix addition: Matrix + MatrixExpr */
/****************************************************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrix<T, ROWS, COLS>,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>
    >
> {
    typedef CMatrix<T, ROWS, COLS>                                LHSType;
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> RHSType;

    // Ensure the matrices are compatible
    static_assert(LHSType::rows == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(LHSType::cols == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // We no not use static const int here, as that would mean we have to create an instance
    // of this type in order to reserve the memory for these variables. Using an enum instead
    // avoids this.
    enum {rows = ROWS, cols = COLS};
};



/****************************************************************/
/* Full specialization for matrix addition: MatrixExpr + Matrix */
/****************************************************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>,
        CMatrix<T, ROWS, COLS>
    >
> {
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> LHSType;
    typedef CMatrix<T, ROWS, COLS>                                RHSType;
    typedef cmatrix_binary_operator_traits<CMatrix_NS::MATRIX_PLUS<T, RHSType, LHSType>> traits;

    // Matrix addition is commutative
    enum {rows = traits::rows, cols = traits::cols};
};



/********************************************************************/
/* Full specialization for matrix addition: MatrixExpr + MatrixExpr */
/********************************************************************/

template<typename T, typename OP1, typename OP2, typename OP3, typename OP4, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR_A, template<typename T, typename OP3, typename OP4> class BINARY_OPERATOR_B>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A>,
        CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B>
    >
> {
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A> LHSType;
    typedef CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B> RHSType;

    // Ensure the matrices are compatible
    static_assert(LHSType::rows == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(LHSType::cols == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // We no not use static const int here, as that would mean we have to create an instance
    // of this type in order to reserve the memory for these variables. Using an enum instead
    // avoids this.
    enum {rows = LHSType::rows, cols = LHSType::cols};
};
