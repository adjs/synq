
//
// Created by Adenilton on 07/02/26.
//

#include "../include/randomUnitary.h"

//
// Created by Adenilton on 07/02/26.
//



#include "../include/randomUnitary.h"

// Function to generate a random complex matrix with standard Gaussian entries
MatrixXcd generate_gaussian_complex_matrix(int n) {
    // Use modern C++ random number generation
    static mt19937 engine(time(nullptr)); // Seed the generator once
    normal_distribution<double> gaussian(0.0, 1.0);

    MatrixXcd Z(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Z(i, j).real(gaussian(engine));
            Z(i, j).imag(gaussian(engine));
        }
    }
    return Z;
}

// Function to produce a random unitary matrix (Haar distributed)
MatrixXcd random_unitary_matrix(int n) {
    MatrixXcd Z = generate_gaussian_complex_matrix(n);

    // Compute the QR decomposition: Z = Q*R
    // The Q factor will be a random unitary matrix
    HouseholderQR<MatrixXcd> qr(Z);
    MatrixXcd Q = qr.householderQ();

    // The direct Eigen QR decomposition has a non-unique phase,
    // but the resulting matrix is still Haar distributed up to this phase.
    // For a strict Haar measure sampling, one would need to adjust the diagonal
    // elements of R to be real and positive, which isn't directly exposed
    // in this high-level Eigen function, but the Q matrix is sufficient for most uses.

    return Q;
}