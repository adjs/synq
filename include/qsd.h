//
// Created by adenilton on 10/11/25.
//
#pragma once

#include<complex>
#include <Eigen/Dense>

struct qsd_result {
    Eigen::VectorXcd list_d;
    Eigen::MatrixXcd gate_v;
    Eigen::MatrixXcd gate_w;
};

qsd_result qsd(Eigen::MatrixXcd gate1, Eigen::MatrixXcd gate2);

