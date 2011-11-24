#include <iostream>
#include <type_traits>

#include "CMatrix.hpp"

int main() {
    CMatrix<double, 3, 3> a;
    CMatrix<double, 3, 3> b;
    CMatrix<double, 3, 3> c;

    // Matrix addition
//    a = b + c;
    (a + (b + c))[1][2];
    
    const double erg = (b + c)[1][2];

    return 0;
}
