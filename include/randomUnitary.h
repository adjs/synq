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

MatrixXcf generate_gaussian_complex_matrix(int n);
MatrixXcf random_unitary_matrix(int n);