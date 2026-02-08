//
// Created by adenilton on 10/11/25.
//
#pragma once

#include<complex>
#include <Eigen/Dense>

struct qsd_result {
    Eigen::VectorXcf list_d;
    Eigen::MatrixXcf gate_v;
    Eigen::MatrixXcf gate_w;
};

qsd_result qsd(Eigen::MatrixXcf gate1, Eigen::MatrixXcf gate2);

