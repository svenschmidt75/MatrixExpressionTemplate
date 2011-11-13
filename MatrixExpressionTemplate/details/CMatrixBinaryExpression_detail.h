#ifndef CMATRIXBINARYEXPRESSION_H
  #error "CMatrixBinaryExpression_detail cannot be used. It is an implementation detail.");
#endif

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>::CMatrixBinaryExpression(typename type_traits<OP1>::RefType const op1, typename type_traits<OP2>::RefType const op2)
    : op1_(op1), op2_(op2) {

    // Check that the value types are compatible
    static_assert(std::is_convertible<typename type_traits<OP1>::value_type, typename type_traits<OP2>::value_type>::value, "CMatrixBinaryExpression: Incompatible types");
}

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>
CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>::operator[](int row) {
    return CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>(op1_, op2_, row);
}

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR> const
CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>::operator[](int row) const {
    return CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>(op1_, op2_, row);
}
