/*
 * Name  : type_traits
 * Path  : 
 * Use   : Abstraction for types. Advantage is that we only need to change type_traits, not where it is used.
 *         If no type_traits is used, we would have to change all occurrences individually.
 * Author: Sven Schmidt
 * Date  : 11/13/2011
 */
#pragma once

// Forward declaration of used types
template<typename T, int ROWS, int COLS>
class CMatrix;

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
class CMatrixBinaryExpression;





// Base type traits
template<typename ComplexType>
struct type_traits {
    typedef typename ComplexType::value_type value_type;
    static const int                         rows = ComplexType::ROWS;
    static const int                         cols = ComplexType::COLS;
};

// Specialization for CMatrix
template<typename T, int ROWS, int COLS>
struct type_traits<CMatrix<T, ROWS, COLS>> {
    typedef T                      value_type;
    typedef CMatrix<T, ROWS, COLS> RefType;
    static const int               rows = ROWS;
    static const int               cols = COLS;
};

// Specialization for CMatrixBinaryExpression
template<typename OP1, typename OP2, typename BINARY_OPERATOR>
struct type_traits<CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>> {
    typedef typename type_traits<OP1>::value_type              value_type;
    typedef CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR> RefType;

    // The number of rows and columns of the resulting matrix depends on
    // the binary operator. For example, for addition, rows and cols will
    // be the same. But multiplying a (m1 by m2) matrix with (n1 by n2)
    // has the constraint that m2==n1 and the result is a (m1 by n2)
    // matrices.
    static const int                                           rows = CMatrix_NS::bin_op_type_traits<OP1, OP2, BINARY_OPERATOR<OP1, OP2>>::rows;
//    static const int                                           rows = CMatrix_NS::bin_op_type_traits<OP1, OP2, BINARY_OPERATOR<OP1, OP2>>::cols;
};

