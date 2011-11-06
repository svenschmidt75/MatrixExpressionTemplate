#ifndef CMATRIXROWBINARYEXPRESSION_H
    #error "CMatrixRowBinaryExpression_detail cannot be used. It is an implementation detail."
#endif

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>::CMatrixRowBinaryExpression(typename OP1::RefType const op1, typename OP2::RefType const op2, int row)
    : op1_(op1), op2_(op2), row_(row) {}

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
typename OP1::value_type&
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>::operator[](int col) {
    int offset = get_offset(COLS, row_);
    return buffer_[offset + col];
}

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
typename OP1::value_type const &
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>::operator[](int col) const {
    int offset = get_offset(COLS, row_);
    return buffer_[offset + col];
}
