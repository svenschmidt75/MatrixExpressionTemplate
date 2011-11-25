/*
 * Name  : CMatrixScalar
 * Path  : 
 * Use   : For multiplication of matrices with scalars
 * Author: Sven Schmidt
 * Date  : 11/25/2011
 */
#pragma once

#define CMATRIXSCALAR_H

template<typename T>
class CMatrixScalar {
public:
    CMatrixScalar(T in);

    // So we can use this type with a[i][j]
    T getValue() const;

private:
    T value_;
};

#include "details/CMatrixScalar_detail.h"
