#include <iostream>
#include <type_traits>

#include "CMatrix.hpp"

int main() {
    {
        CMatrix<double, 3, 3> a;
        CMatrix<double, 3, 3> b;
        CMatrix<double, 3, 3> c;

        // Matrix addition
        //    a = b + c;
        (a + (b + c))[1][2];
        ((b + c) + a)[1][2];
        ((b + c) + (a + b))[1][2];
    }

    {
        CMatrix<double, 3, 3> a;
        CMatrix<double, 3, 3> b;
        CMatrix<double, 3, 3> c;

        (a - (b + c))[1][2];
        ((b - c) + a)[1][2];
        ((b - c) + (a - b))[1][2];
    }

    {
        CMatrix<double, 3, 4> a;
        CMatrix<double, 4, 4> b;
        CMatrix<double, 3, 4> c;

        (a * b)[1][2];
        (c + (a * b))[1][2];
    }

    return 0;
}
