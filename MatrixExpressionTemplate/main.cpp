#include <iostream>

#include "CMatrix.hpp"

int main() {
    CMatrix<double, 3, 3> a;

    double value = a[1][2];

    a[0][3] = 3.14;

    value = a[0][3];

    return 0;
}
