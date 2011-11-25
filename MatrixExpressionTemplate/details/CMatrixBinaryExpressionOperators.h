/*
 * Name  : CMatrixBinaryExpressionOperators
 * Path  : 
 * Use   : Implements binary operators for matrix objects
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once

namespace CMatrix_NS {

    template<typename T, typename STD_BIN_OP>
    T eval(typename T lhs, typename T rhs) {
        return STD_BIN_OP()(lhs, rhs);
    }

    template<typename T, typename OP1, typename OP2>
    struct MATRIX_PLUS {

        typename type_traits<OP1>::value_type operator()(typename type_traits<OP1>::RefType const op1, typename type_traits<OP2>::RefType const op2, int row, int col) const {
            typedef typename type_traits<OP1>::value_type T;

            // Addition requires the matrices to be of the same type
            static_assert(OP1::rows == OP2::rows, "Operators have incompatible number of rows");
            static_assert(OP1::cols == OP2::cols, "Operators have incompatible number of cols");

            T arg1 = op1[row][col];
            T arg2 = op2[row][col];
            T tmp = eval<T, std::plus<T> >(arg1, arg2);
            return tmp;
        }

    };

    template<typename T, typename OP1, typename OP2>
    struct MATRIX_MINUS {

        typename type_traits<OP1>::value_type operator()(typename type_traits<OP1>::RefType const op1, typename type_traits<OP2>::RefType const op2, int row, int col) const {
            typedef typename type_traits<OP1>::value_type T;

            // Subtraction requires the matrices to be of the same type
            static_assert(OP1::rows == OP2::rows, "Operators have incompatible number of rows");
            static_assert(OP1::cols == OP2::cols, "Operators have incompatible number of cols");

            T arg1 = op1[row][col];
            T arg2 = op2[row][col];
            T tmp = eval<T, std::minus<T> >(arg1, arg2);
            return tmp;
        }

    };

    template<typename T, typename OP1, typename OP2>
    struct MATRIX_MUL {

        typename type_traits<OP1>::value_type operator()(typename type_traits<OP1>::RefType const op1, typename type_traits<OP2>::RefType const op2, int row, int col) const {
            typedef typename type_traits<OP1>::value_type T;

            // Assume OP1=(OP1_r, OP_1_c), where OP1_r = #rows of matrix OP1.
            // Similar for OP2.
            // Multiplication requires that OP1_c == OP2_r.
            static_assert(OP1::cols == OP2::rows, "Operators are incompatible");

            int rows = OP1::rows;
            int cols = OP1::cols;

            T tmp = 0;

            for (int k = 0; k < cols; ++k) {
                T tmp1 = op1[row][k];
                T tmp2 = op2[k][col];
                tmp += (tmp1 + tmp2);
            }

            return tmp;
        }

    };

    

    /***************************************************/
    /* Operator for multiplying a matrix with a scalar */
    /***************************************************/

    // We specialize this operator for left and right scalar multiplication
    template<typename T, typename OP1, typename OP2>
    struct MATRIX_MUL_SCALAR {};

    template<typename T, typename OP>
    struct MATRIX_MUL_SCALAR<T, OP, CMatrixScalar<T> > {

        typename type_traits<OP>::value_type operator()(typename type_traits<OP>::RefType const op1, typename type_traits<CMatrixScalar<T>>::RefType const & op2, int row, int col) const {
            typedef typename type_traits<OP>::value_type T;

            int rows = OP::rows;
            int cols = OP::cols;

            T tmp = op1[rows][cols];
            tmp *= op2.getValue();

            return tmp;
        }

    };

}

/*******************
 * Matrix + Matrix *
 *******************/

template<typename T, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B>
CMatrixBinaryExpression<T, CMatrix<T, ROWS_A, COLS_A>, CMatrix<T, ROWS_B, COLS_B>, CMatrix_NS::MATRIX_PLUS>
operator+(CMatrix<T, ROWS_A, COLS_A> const & op1, CMatrix<T, ROWS_B, COLS_B> const & op2) {

    typedef CMatrix<T, ROWS_A, COLS_A> LHSType;
    typedef CMatrix<T, ROWS_B, COLS_B> RHSType;

    // Ensure the matrices are compatible
    static_assert(ROWS_A == ROWS_B, "Matrices incompatible: Must have same number of rows");
    static_assert(COLS_A == COLS_B, "Matrices incompatible: Must have same number of cols");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<RHSType>::value_type>::value, "Incompatible value types");

    // When doing addition, both matrices need to have the same number of columns and rows. This
    // is enforced by the compiler as both matrices, that are to be added, have the same type,
    // including ROWS and COLS.
    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_PLUS>(op1, op2);
}


/***********************************
 * Matrix + MatrixBinaryExpression *
 ***********************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixBinaryExpression<T, CMatrix<T, ROWS, COLS>, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>, CMatrix_NS::MATRIX_PLUS>
operator+(CMatrix<T, ROWS, COLS> const & op1, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const & op2) {

    typedef CMatrix<T, ROWS, COLS>                                LHSType;
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> RHSType;

    // Ensure the matrices are compatible
    static_assert(ROWS == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(COLS == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_PLUS>(op1, op2);
}


/***********************************
 * MatrixBinaryExpression + Matrix *
 ***********************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixBinaryExpression<T, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>, CMatrix<T, ROWS, COLS>, CMatrix_NS::MATRIX_PLUS>
operator+(CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const & op1, CMatrix<T, ROWS, COLS> const & op2) {

    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> LHSType;
    typedef CMatrix<T, ROWS, COLS>                                RHSType;

    // Ensure the matrices are compatible
    static_assert(ROWS == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(COLS == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    /* As addition is commutative, you might think we can simply write
     * return op2 + op1, i.e. return operatpr+<>(op2, op1);
     * However, return op2 + op1; is of type
     * CMatrixBinaryExpression<
     *      T,
     *      CMatrix<T, ROWS, COLS>,
     *      CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>,
     *      CMatrix_NS::MATRIX_PLUS
     * >
     *
     * while this method returns the symmetric counter part
     * CMatrixBinaryExpression<
     *      T,
     *      CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>,
     *      CMatrix<T, ROWS, COLS>,
     *      CMatrix_NS::MATRIX_PLUS
     * >
     * which is obviously not the same type. We could, however,
     * change the return type of this function accordingly.
     */
    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_PLUS>(op1, op2);
}


/***************************************************
 * MatrixBinaryExpression + MatrixBinaryExpression *
 ***************************************************/

template<typename T, typename OP1, typename OP2, typename OP3, typename OP4, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR_A, template<typename T, typename OP3, typename OP4> class BINARY_OPERATOR_B>
CMatrixBinaryExpression<T, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A>, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_B>, CMatrix_NS::MATRIX_PLUS>
operator+(CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A> const & op1, CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B> const & op2) {

    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A> LHSType;
    typedef CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B> RHSType;

    // Ensure the matrices are compatible
    static_assert(LHSType::rows == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(LHSType::cols == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_PLUS>(op1, op2);
}





/*******************
 * Matrix - Matrix *
 *******************/

template<typename T, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B>
CMatrixBinaryExpression<T, CMatrix<T, ROWS_A, COLS_A>, CMatrix<T, ROWS_B, COLS_B>, CMatrix_NS::MATRIX_MINUS>
operator-(CMatrix<T, ROWS_A, COLS_A> const & op1, CMatrix<T, ROWS_B, COLS_B> const & op2) {

    typedef CMatrix<T, ROWS_A, COLS_A> LHSType;
    typedef CMatrix<T, ROWS_B, COLS_B> RHSType;

    // Ensure the matrices are compatible
    static_assert(ROWS_A == ROWS_B, "Matrices incompatible: Must have same number of rows");
    static_assert(COLS_A == COLS_B, "Matrices incompatible: Must have same number of cols");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<RHSType>::value_type>::value, "Incompatible value types");

    // When doing addition, both matrices need to have the same number of columns and rows. This
    // is enforced by the compiler as both matrices, that are to be added, have the same type,
    // including ROWS and COLS.
    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MINUS>(op1, op2);
}


/***********************************
 * Matrix - MatrixBinaryExpression *
 ***********************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixBinaryExpression<T, CMatrix<T, ROWS, COLS>, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>, CMatrix_NS::MATRIX_MINUS>
operator-(CMatrix<T, ROWS, COLS> const & op1, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const & op2) {

    typedef CMatrix<T, ROWS, COLS>                                LHSType;
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> RHSType;

    // Ensure the matrices are compatible
    static_assert(ROWS == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(COLS == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MINUS>(op1, op2);
}


/***********************************
 * MatrixBinaryExpression - Matrix *
 ***********************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixBinaryExpression<T, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>, CMatrix<T, ROWS, COLS>, CMatrix_NS::MATRIX_MINUS>
operator-(CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const & op1, CMatrix<T, ROWS, COLS> const & op2) {

    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> LHSType;
    typedef CMatrix<T, ROWS, COLS>                                RHSType;

    // Ensure the matrices are compatible
    static_assert(ROWS == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(COLS == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MINUS>(op1, op2);
}


/***************************************************
 * MatrixBinaryExpression - MatrixBinaryExpression *
 ***************************************************/

template<typename T, typename OP1, typename OP2, typename OP3, typename OP4, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR_A, template<typename T, typename OP3, typename OP4> class BINARY_OPERATOR_B>
CMatrixBinaryExpression<T, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A>, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_B>, CMatrix_NS::MATRIX_MINUS>
operator-(CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A> const & op1, CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B> const & op2) {

    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A> LHSType;
    typedef CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B> RHSType;

    // Ensure the matrices are compatible
    static_assert(LHSType::rows == RHSType::rows, "Matrices incompatible: Must have same number of rows");
    static_assert(LHSType::cols == RHSType::cols, "Matrices incompatible: Must have same number of cols");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MINUS>(op1, op2);
}





/*******************
 * Matrix * Matrix *
 *******************/

template<typename T, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B>
CMatrixBinaryExpression<T, CMatrix<T, ROWS_A, COLS_A>, CMatrix<T, ROWS_B, COLS_B>, CMatrix_NS::MATRIX_MUL>
operator*(CMatrix<T, ROWS_A, COLS_A> const & op1, CMatrix<T, ROWS_B, COLS_B> const & op2) {

    typedef CMatrix<T, ROWS_A, COLS_A> LHSType;
    typedef CMatrix<T, ROWS_B, COLS_B> RHSType;

    // Ensure the matrices are compatible
    static_assert(COLS_A == ROWS_B, "Matrices incompatible");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<RHSType>::value_type>::value, "Incompatible value types");

    // When doing addition, both matrices need to have the same number of columns and rows. This
    // is enforced by the compiler as both matrices, that are to be added, have the same type,
    // including ROWS and COLS.
    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MUL>(op1, op2);
}


/***********************************
 * Matrix * MatrixBinaryExpression *
 ***********************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixBinaryExpression<T, CMatrix<T, ROWS, COLS>, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>, CMatrix_NS::MATRIX_MUL>
operator*(CMatrix<T, ROWS, COLS> const & op1, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const & op2) {

    typedef CMatrix<T, ROWS, COLS>                                LHSType;
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> RHSType;

    // Ensure the matrices are compatible
    static_assert(COLS == RHSType::rows, "Matrices incompatible");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MUL>(op1, op2);
}


/***********************************
 * MatrixBinaryExpression * Matrix *
 ***********************************/

template<typename T, int ROWS, int COLS, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixBinaryExpression<T, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>, CMatrix<T, ROWS, COLS>, CMatrix_NS::MATRIX_MUL>
operator*(CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const & op1, CMatrix<T, ROWS, COLS> const & op2) {

    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> LHSType;
    typedef CMatrix<T, ROWS, COLS>                                RHSType;

    // Ensure the matrices are compatible
    static_assert(ROWS == RHSType::cols, "Matrices incompatible");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MUL>(op1, op2);
}


/***************************************************
 * MatrixBinaryExpression * MatrixBinaryExpression *
 ***************************************************/

template<typename T, typename OP1, typename OP2, typename OP3, typename OP4, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR_A, template<typename T, typename OP3, typename OP4> class BINARY_OPERATOR_B>
CMatrixBinaryExpression<T, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A>, CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_B>, CMatrix_NS::MATRIX_MUL>
operator*(CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A> const & op1, CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B> const & op2) {

    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR_A> LHSType;
    typedef CMatrixBinaryExpression<T, OP3, OP4, BINARY_OPERATOR_B> RHSType;

    // Ensure the matrices are compatible
    static_assert(LHSType::rows == RHSType::cols, "Matrices incompatible");

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<LHSType>::value_type, typename type_traits<OP1>::value_type>::value, "Incompatible value types");

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MUL>(op1, op2);
}









/*******************
 * Matrix * Scalar *
 *******************/

template<typename T, int ROWS, int COLS>
CMatrixBinaryExpression<T, CMatrix<T, ROWS, COLS>, CMatrixScalar<T>, CMatrix_NS::MATRIX_MUL_SCALAR>
operator*(CMatrix<T, ROWS, COLS> const & op1, T value) {

    typedef CMatrix<T, ROWS, COLS> LHSType;
    typedef CMatrixScalar<T>       RHSType;

    return CMatrixBinaryExpression<T, LHSType, RHSType, CMatrix_NS::MATRIX_MUL_SCALAR>(op1, value);
}
