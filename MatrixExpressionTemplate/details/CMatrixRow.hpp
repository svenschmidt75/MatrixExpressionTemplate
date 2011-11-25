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

    // The index operators both do NOT return a reference, because
    // 1. (a*b)[i][j] should not be allowed
    // 2. This is only used in matrix expressions, and when doing lazy evaluation,
    //    we need the values anyway.
    // 3. CMatrix should define these operators as returning a reference,
    //    because a[i][j] = 1; will not work otherwise.
    T& operator[](int col);
    T const & operator[](int col) const;

private:
    boost::shared_array<T> buffer_;
    const int              row_;
};

#include "CMatrixRow_detail.h"
