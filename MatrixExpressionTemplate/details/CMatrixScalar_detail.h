#ifndef CMATRIXSCALAR_H
    #error "CMatrixScalar_detail must not be used. It is an implementation detail."
#endif


template<typename T>
CMatrixScalar<T>::CMatrixScalar(T in) : value_(in) {};

template<typename T>
T
CMatrixScalar<T>::getValue() const {
    return value_;
}
