#ifndef CMATRIXROW_H
    #error "cmatrixrow_detail must not be used. It is an implementation detail."
#endif


template<typename T, int COLS>
CMatrixRow<T, COLS>::CMatrixRow(const boost::shared_array<T>& buffer, int row) : buffer_(buffer), row_(row) {}

namespace CMatrixRow_NS {
    int get_offset(int cols, int row) {
        return cols * row;
    }

}

template<typename T, int COLS>
T
CMatrixRow<T, COLS>::operator[](int col) {
    int offset = CMatrixRow_NS::get_offset(COLS, row_);
    return buffer_[offset + col];
}

template<typename T, int COLS>
T const
CMatrixRow<T, COLS>::operator[](int col) const {
    int offset = CMatrixRow_NS::get_offset(COLS, row_);
    return buffer_[offset + col];
}
