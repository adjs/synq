// https://www.netlib.org/lapack/explore-html-3.6.1/df/d14/lapacke__cuncsd_8c_a0d8bba2ce527b3bd6c82a3f6bd31320b.html
// https://netlib.org/lapack/explore-html-3.6.1/de/d0d/zuncsd_8f_a6c456c8f5615f0cc513fa939498e5e79.html


#pragma once
#define EIGEN_USE_LAPACKE

#include <complex>
#define lapack_complex_double std::complex<double>

#include<Eigen/Dense>
#include <lapacke.h>


struct csd_result {
    Eigen::MatrixXcd U1;
    Eigen::MatrixXcd U2;
    std::vector<double> theta;
    Eigen::MatrixXcd V1T;
    Eigen::MatrixXcd V2T;
};
csd_result csd( const Eigen::MatrixXcd& unitary, int p, int q);
lapack_complex_double* eigen2lapack(const Eigen::MatrixXcd& unitary, int start_line, int start_col, int n_rows, int n_cols);

bool verify(const Eigen::MatrixXcd& unitary, csd_result result);

