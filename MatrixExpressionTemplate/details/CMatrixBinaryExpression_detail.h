#ifndef CMATRIXBINARYEXPRESSION_H
  #error "CMatrixBinaryExpression_detail cannot be used. It is an implementation detail.");
#endif

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>::CMatrixBinaryExpression(typename OP1::RefType const op1, typename OP2::RefType const op2)
    : op1_(op1), op2_(op2) {}

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
