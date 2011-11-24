#ifndef CMATRIXROWBINARYEXPRESSION_H
    #error "CMatrixRowBinaryExpression_detail cannot be used. It is an implementation detail."
#endif

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>::CMatrixRowBinaryExpression(typename type_traits<OP1>::RefType op1, typename type_traits<OP2>::RefType op2, int row)
    : op1_(op1), op2_(op2), row_(row) {}

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
typename type_traits<OP1>::value_type
CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>::operator[](int col) {
    return CMatrix_NS::MATRIX_PLUS<T, OP1, OP2>()(op1_, op2_, row_, col);
}

template<typename T, typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
typename type_traits<OP1>::value_type const
CMatrixRowBinaryExpression<T, OP1, OP2, BINARY_OPERATOR>::operator[](int col) const {
    return CMatrix_NS::MATRIX_PLUS<T, OP1, OP2>()(op1_, op2_, row_, col);
}
