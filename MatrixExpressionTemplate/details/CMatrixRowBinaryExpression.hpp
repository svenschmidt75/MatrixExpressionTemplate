/*
 * Name  : CMatrixRowBinaryExpression
 * Path  : 
 * Use   : Acts as a proxy so Matrix[i][j] is supported
 * Author: Sven Schmidt
 * Date  : 11/6/2011
 */
#pragma once

#include <boost/shared_array.hpp>

#define CMATRIXROWBINARYEXPRESSION_H

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
class CMatrixRowBinaryExpression {
public:
    typedef typename type_traits<OP1>::value_type value_type;

public:
    CMatrixRowBinaryExpression(typename OP1::RefType const op1, typename OP2::RefType const op2, int row);

    // When it appears as lvalue
    value_type operator[](int col);
    value_type const operator[](int col) const;

private:
    typename OP1::RefType op1_;
    typename OP2::RefType op2_;
    const int             row_;
};

#include "CMatrixRowBinaryExpression_detail.h"
