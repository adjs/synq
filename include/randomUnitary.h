//
// Created by Adenilton on 07/02/26.
//

#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <ctime>
#include <cmath>

using namespace Eigen;
using namespace std;

MatrixXcd generate_gaussian_complex_matrix(int n);
MatrixXcd random_unitary_matrix(int n);