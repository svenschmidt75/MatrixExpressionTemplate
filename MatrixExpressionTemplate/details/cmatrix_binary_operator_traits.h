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





/***************************************************************/
/* Full specialization for matrix subtraction: Matrix - Matrix */
/***************************************************************/
template<typename T, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MINUS<
        T,
        CMatrix<T, ROWS_A, COLS_A>,
        CMatrix<T, ROWS_B, COLS_B>
    >
> {
    typedef cmatrix_binary_operator_traits<
        CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrix<T, ROWS_A, COLS_A>,
        CMatrix<T, ROWS_A, COLS_A>
        >
    > trait;

    enum {rows = trait::rows, cols = trait::cols};
};



/*******************************************************************/
/* Full specialization for matrix subtraction: Matrix - MatrixExpr */
/*******************************************************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MINUS<
        T,
        CMatrix<T, ROWS, COLS>,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>
    >
> {
    typedef cmatrix_binary_operator_traits<
        CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrix<T, ROWS, COLS>,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>
        >
    > trait;

    enum {rows = trait::rows, cols = trait::cols};
};



/*******************************************************************/
/* Full specialization for matrix subtraction: MatrixExpr - Matrix */
/*******************************************************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MINUS<
        T,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>,
        CMatrix<T, ROWS, COLS>
    >
> {
    typedef cmatrix_binary_operator_traits<
        CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>,
        CMatrix<T, ROWS, COLS>
        >
    > trait;

    enum {rows = trait::ROWS, cols = trait::COLS};
};



/***********************************************************************/
/* Full specialization for matrix subtraction: MatrixExpr - MatrixExpr */
/***********************************************************************/

template<typename T, typename OP1, typename OP2, typename OP3, typename OP4, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR_A, template<typename T, typename OP3, typename OP4> class BINARY_OPERATOR_B>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MINUS<
        T,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A>,
        CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B>
    >
> {
    typedef cmatrix_binary_operator_traits<
        CMatrix_NS::MATRIX_PLUS<
        T,
        CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A>,
        CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B>
        >
    > trait;

    enum {rows = trait::ROWS, cols = trait::COLS};
};






/******************************************************************/
/* Full specialization for matrix multiplication: Matrix * Matrix */
/******************************************************************/
template<typename T, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MUL<
    T,
    CMatrix<T, ROWS_A, COLS_A>,
    CMatrix<T, ROWS_B, COLS_B>
    >
> {
    typedef CMatrix<T, ROWS_A, COLS_A> LHSType;
    typedef CMatrix<T, ROWS_B, COLS_B> RHSType;

    // Ensure matrices are compatible
    static_assert(LHSType::cols == RHSType::rows, "Invalid matrix multiplication");

    enum {rows = LHSType::rows, cols = RHSType::cols};
};



/**********************************************************************/
/* Full specialization for matrix multiplication: Matrix * MatrixExpr */
/**********************************************************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MUL<
    T,
    CMatrix<T, ROWS, COLS>,
    CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>
    >
> {
    typedef CMatrix<T, ROWS, COLS>                                LHSType;
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> RHSType;

    // Ensure matrices are compatible
    static_assert(LHSType::cols == RHSType::rows, "Invalid matrix multiplication");

    enum {rows = LHSType::rows, cols = RHSType::cols};
};



/**********************************************************************/
/* Full specialization for matrix multiplication: MatrixExpr * Matrix */
/**********************************************************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MUL<
    T,
    CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>,
    CMatrix<T, ROWS, COLS>
    >
> {
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> LHSType;
    typedef CMatrix<T, ROWS, COLS>                                RHSType;

    // Ensure matrices are compatible
    static_assert(LHSType::cols == RHSType::rows, "Invalid matrix multiplication");

    enum {rows = LHSType::rows, cols = RHSType::cols};
};



/**************************************************************************/
/* Full specialization for matrix multiplication: MatrixExpr * MatrixExpr */
/**************************************************************************/

template<typename T, typename OP1, typename OP2, typename OP3, typename OP4, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR_A, template<typename T, typename OP3, typename OP4> class BINARY_OPERATOR_B>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MUL<
    T,
    CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A>,
    CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B>
    >
> {
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A> LHSType;
    typedef CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B> RHSType;

    // Ensure matrices are compatible
    static_assert(LHSType::cols == RHSType::rows, "Invalid matrix multiplication");

    enum {rows = LHSType::rows, cols = RHSType::cols};
};






/*************************************************************************/
/* Full specialization for matrix/scalar multiplication: Matrix * Scalar */
/*************************************************************************/
template<typename T, int ROWS, int COLS>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MUL_SCALAR<
    T,
    CMatrix<T, ROWS, COLS>,
    CMatrixScalar<T>
    >
> {
    typedef CMatrix<T, ROWS, COLS> LHSType;
    typedef CMatrixScalar<T>       RHSType;

    enum {rows = LHSType::rows, cols = LHSType::cols};
};



/*************************************************************************/
/* Full specialization for matrix/scalar multiplication: Scalar * Matrix */
/*************************************************************************/
template<typename T, int ROWS, int COLS>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MUL_SCALAR<
    T,
    CMatrixScalar<T>,
    CMatrix<T, ROWS, COLS>
    >
> {
    typedef CMatrixScalar<T>       LHSType;
    typedef CMatrix<T, ROWS, COLS> RHSType;

    enum {rows = RHSType::rows, cols = RHSType::cols};
};



/**********************************************************************/
/* Full specialization for matrix multiplication: MatrixExpr * Scalar */
/**********************************************************************/

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MUL_SCALAR<
    T,
    CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>,
    CMatrixScalar<T>
    >
> {
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> LHSType;
    typedef CMatrixScalar<T>                     RHSType;

    enum {rows = LHSType::rows, cols = LHSType::cols};
};



/**********************************************************************/
/* Full specialization for matrix multiplication: Scalar * MatrixExpr */
/**********************************************************************/

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct cmatrix_binary_operator_traits<
    CMatrix_NS::MATRIX_MUL_SCALAR<
    T,
    CMatrixScalar<T>,
    CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>
    >
> {
    typedef CMatrixScalar<T>                                      LHSType;
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> RHSType;

    enum {rows = RHSType::rows, cols = RHSType::cols};
};
