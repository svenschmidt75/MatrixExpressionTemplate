/*
 * Name  : CMatrixRow
 * Path  : 
 * Use   : Acts as a proxy so Matrix[i][j] is supported
 * Author: Sven Schmidt
 * Date  : 11/5/2011
 */
#pragma once

#include <boost/shared_array.hpp>

#define CMATRIXROW_H

template<typename T, int COLS>
class CMatrixRow {
public:
    CMatrixRow(const boost::shared_array<T>& buffer, int row);

    // When it appears as lvalue
    T& operator[](int col);
    const T& operator[](int col) const;

private:
    boost::shared_array<T> buffer_;
    const int              row_;
};

#include "CMatrixRow_detail.h"
