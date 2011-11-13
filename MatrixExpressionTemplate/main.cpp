#include <iostream>
#include <type_traits>


template<typename T, int ROWS, int COLS>
class CMatrix;

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
class CMatrixBinaryExpression;

template<typename ComplexType>
struct type_traits {
    typedef typename ComplexType::value_type value_type;
};

template<typename T, int ROWS, int COLS>
struct type_traits<CMatrix<T, ROWS, COLS>> {
    typedef T value_type;
};

template<typename OP1, typename OP2, typename BINARY_OPERATOR>
struct type_traits<CMatrixBinaryExpression<OP1, OP2, BINARY_OPERATOR>> {
    typedef typename type_traits<OP1>::value_type value_type;
};


#include "CMatrix.hpp"






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

    bool trt = std::is_convertible<float, int>::value;


    bigger_type<float, float>::value_type erg1 = 1.345;
    bool test = std::is_floating_point<float>::value;



    // Matrix addition
//    a = b + c;
    b + c;
    
    const double erg = (b + c)[1][2];

    return 0;
}
