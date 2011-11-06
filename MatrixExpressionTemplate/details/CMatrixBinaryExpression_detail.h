#ifndef CMATRIXBINARYEXPRESSION_H
  #error "CMatrixBinaryExpression_detail cannot be used. It is an implementation detail.");
#endif

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
MatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>::MatrixBinaryExpression(typename OP1::RefType const op1, typename OP2::RefType const op2)
    : op1_(op1), op2_(op2) {}

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>
MatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>::operator[](int row) {

}

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR> const
MatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>::operator[](int row) const {

}
