#include <iostream>
#include <type_traits>

#include "CMatrix.hpp"

template<typename OP>
struct type_traits {
    typedef typename OP::value_type value_type;
};


template<typename OP1, typename OP2>
struct test {
    typename type_traits<OP1>::value_type var1;
};








template<typename T1, typename T2, bool>
struct bigger_type_ {
    typedef T1 value_type;
};

template<typename T1, typename T2>
struct bigger_type_<T1, T2, true> {
    typedef T2 value_type;
};

template<typename T1, typename T2>
struct bigger_type {
    typedef typename bigger_type_<T1, T2, std::is_floating_point<T1>::value>::value_type value_type;
};






int main() {
    CMatrix<double, 3, 3> a;
    CMatrix<double, 3, 3> b;
    CMatrix<double, 3, 3> c;

//    auto t = CMatrixBinaryExpression<CMatrix<double, 3, 3>, CMatrix<double, 3, 3>, MATRIX_PLUS<CMatrix<double, 3, 3>, CMatrix<double, 3, 3>, 3> >(a, b);

    test<CMatrixBinaryExpression<CMatrix<double, 3, 3>, CMatrix<double, 3, 3>, MATRIX_PLUS<CMatrix<double, 3, 3>, CMatrix<double, 3, 3>, 3> >, CMatrix<double, 3, 3> > t;
    t.var1 = 1;

    bigger_type<float, float>::value_type erg1 = 1.345;
    bool test = std::is_floating_point<float>::value;



    // Matrix addition
//    a = b + c;
    b + c;
    
    const double erg = (b + c)[1][2];

    return 0;
}
