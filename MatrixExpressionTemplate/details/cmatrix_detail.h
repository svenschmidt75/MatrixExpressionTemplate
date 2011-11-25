#ifndef CMATRIX_H
    #error "CMatrix_detail must not be used. It is an implementation detail."
#endif


template<typename T, int ROWS, int COLS>
CMatrix<T, ROWS, COLS>::CMatrix() : buffer_(new T[ROWS * COLS]) {}

template<typename T, int ROWS, int COLS>
CMatrix<T, ROWS, COLS>&
CMatrix<T, ROWS, COLS>::operator=(typename type_traits<CMatrix<T, rows, COLS>>::RefType& in) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            (*this)[i][j] = in[i][j];
    }

    return *this;
}

template<typename T, int ROWS, int COLS>
template<typename OP1, typename OP2, template<typename T, typename OP1, typename OP2> class BINARY_OPERATOR>
CMatrix<T, ROWS, COLS>&
CMatrix<T, ROWS, COLS>::operator=(CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> const & in) {

    typedef CMatrixBinaryExpression<T, OP1, OP2, BINARY_OPERATOR> InType;

    // Check compatibility
    static_assert(ROWS == InType::rows, "Row mismatch");
    static_assert(COLS == InType::cols, "Column mismatch");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            (*this)[i][j] = in[i][j];
        }
    }

    return *this;
}

template<typename T, int ROWS, int COLS>
CMatrixRow<T, COLS>
CMatrix<T, ROWS, COLS>::operator[](int row) {
    return CMatrixRow<T, COLS>(buffer_, row);
}

template<typename T, int ROWS, int COLS>
CMatrixRow<T, COLS> const
CMatrix<T, ROWS, COLS>::operator[](int row) const {
    return CMatrixRow<T, COLS>(buffer_, row);
}
