#ifndef CMATRIX_H
    #error "CMatrix_detail must not be used. It is an implementation detail."
#endif


template<typename T, int ROWS, int COLS>
CMatrix<T, ROWS, COLS>::CMatrix() : buffer_(new T[ROWS * COLS]) {}

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
