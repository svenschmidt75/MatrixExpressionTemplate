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

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
class CMatrixBinaryExpression;


// Base type traits
template<typename ComplexType>
struct type_traits {
    typedef typename ComplexType::value_type value_type;
};

// Specialization for CMatrix
template<typename T, int ROWS, int COLS>
struct type_traits<CMatrix<T, ROWS, COLS>> {
    typedef T                      value_type;
    typedef CMatrix<T, ROWS, COLS> RefType;
};

// Specialization for CMatrixBinaryExpression
template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
struct type_traits<CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>> {
    typedef typename type_traits<OP1>::value_type              value_type;
    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> RefType;
};
