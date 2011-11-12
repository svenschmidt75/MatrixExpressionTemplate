#ifndef CMATRIXROWBINARYEXPRESSION_H
    #error "CMatrixRowBinaryExpression_detail cannot be used. It is an implementation detail."
#endif

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>::CMatrixRowBinaryExpression(typename OP1::RefType op1, typename OP2::RefType op2, int row)
    : op1_(op1), op2_(op2), row_(row) {

//    static_assert(std::is_convertible<>);
}

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
typename OP1::value_type
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>::operator[](int col) {
    MATRIX_PLUS<OP1, OP2, 3> tmp;
    return tmp(op1_, op2_, row_, col);
}

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
typename OP1::value_type const
CMatrixRowBinaryExpression<OP1, OP2, BINARY_OPERATOR>::operator[](int col) const {
    MATRIX_PLUS<OP1, OP2, 3> tmp;
    return tmp(op1_, op2_, row_, col);
}
