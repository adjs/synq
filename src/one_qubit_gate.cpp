//
// Created by adenilton on 10/3/25.
//

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "../include/one_qubit_gate.h"
#include <complex>

zyz_result OneQubit::zyz_decomposition(Eigen::Matrix2cf uMatrix) {

    double const x00 = arg(uMatrix(0, 0));
    double const x01 = arg(uMatrix(0, 1)) + M_PI;
    double const x10 = arg(uMatrix(1, 0));

    Eigen::Matrix3d A;
    A << 1.0, -1.0/2, -1.0/2,
         1.0, -1.0/2,  1.0/2,
         1.0,  1.0/2, -1.0/2;

    Eigen::Vector3d b;
    b << x00, x01, x10;

    Eigen::Vector3d angles = A.lu().solve(b);
    float const gamma =  acos(abs(uMatrix(0, 0))) * 2;
    float const alpha =  angles(0);
    float const beta =  angles(1);
    float const delta =  angles(2);
    return {alpha, beta, gamma, delta};

}

Eigen::Matrix2cf OneQubit::h_matrix() {
    Eigen::Matrix2cf const h =
        (Eigen::Matrix2cf() <<  1.0f/sqrtf(2.0f)+0.0if, 1.0f/sqrtf(2.f)+0.0if,
                                1.0f/sqrtf(2.0f)+0.0if, -1.0f/sqrtf(2.f)+0.0if).finished();
    return h;
}

Eigen::Matrix2cf OneQubit::x_matrix() {
    Eigen::Matrix2cf const x =
        (Eigen::Matrix2cf() << 0.0f + 0.0if, 1.0f + 0.0if,
                                  1.0f + 0.0if, 0.0f + 0.0if).finished();
    return x;
}

Eigen::Matrix2cf OneQubit::ry_matrix(float theta) {
    Eigen::Matrix2cf const ry =
        (Eigen::Matrix2cf() << cosf(theta/2)+0.if, -sinf(theta/2)+0.if,
                               sinf(theta/2)+0.if, cosf(theta/2)+0.if).finished();
    return ry;
}

Eigen::Matrix2cf OneQubit::rz_matrix(float theta) {
    Eigen::Matrix2cf const rz =
        (Eigen::Matrix2cf() << exp(-theta*1.if/2.f), 0.if,
                               0.if,              exp(theta*1if/2.f)).finished();
    return rz;
}
