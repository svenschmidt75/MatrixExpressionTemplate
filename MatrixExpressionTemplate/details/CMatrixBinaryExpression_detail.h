#ifndef CMATRIXBINARYEXPRESSION_H
    #error "CMatrixBinaryExpression_detail must not be used. It is an implementation detail."
#endif


template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>::CMatrixBinaryExpression(typename type_traits<OP1>::RefType const op1, typename type_traits<OP2>::RefType const op2)
    : op1_(op1), op2_(op2) {

    // Check that the value types are compatible
//    static_assert(std::is_convertible<typename type_traits<OP1>::value_type, typename type_traits<OP2>::value_type>::value, "CMatrixBinaryExpression: Incompatible types");
}

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>
CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>::operator[](int row) {
    return CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>(op1_, op2_, row);
}

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const
CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>::operator[](int row) const {
    return CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>(op1_, op2_, row);
}
