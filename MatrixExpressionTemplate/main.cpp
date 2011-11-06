#include <iostream>

#include "CMatrix.hpp"

int main() {
    CMatrix<double, 3, 3> a;
    CMatrix<double, 3, 3> b;
    CMatrix<double, 3, 3> c;

    // Matrix addition
//    a = b + c;
    b + c;
    (b + c)[0][1];

    return 0;
}
