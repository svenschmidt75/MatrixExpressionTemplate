#ifdef CMATRIXROW_H
typedef int mt;
#else
typedef float mt;
#endif

static_assert(sizeof(mt) == 4, "cmatrixrow_detail cannot be used. It is an implementation detail.");

template<typename T, int COLS>
CMatrixRow<T, COLS>::CMatrixRow(const boost::shared_array<T>& buffer, int row) : buffer_(buffer), row_(row) {}

namespace {
    int get_offset(int cols, int row) {
        return cols * row;
    }

}

template<typename T, int COLS>
T&
CMatrixRow<T, COLS>::operator[](int col) {
    int offset = get_offset(COLS, row_);
    return buffer_[offset + col];
}

template<typename T, int COLS>
T const &
CMatrixRow<T, COLS>::operator[](int col) const {
    int offset = get_offset(COLS, row_);
    return buffer_[offset + col];
}
