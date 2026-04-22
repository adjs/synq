//
// Created by adenilton on 10/10/25.
//


#pragma once
#define EIGEN_USE_LAPACKE

#include<complex.h>
#define lapack_complex_float std::complex<float>
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
csd_result csd(Eigen::MatrixXcd& unitary, int p, int q);
lapack_complex_float* eigen2lapack(Eigen::MatrixXcd& unitary, int start_line, int start_col, int n_rows, int n_cols);

bool verify(Eigen::MatrixXcd& unitary, csd_result result);

