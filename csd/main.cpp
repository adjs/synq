#include <iostream>
#include <lapacke.h>
#include<complex.h>
#include<Eigen/Dense>
// https://www.netlib.org/lapack/explore-html-3.6.1/df/d14/lapacke__cuncsd_8c_a0d8bba2ce527b3bd6c82a3f6bd31320b.html

int csd(Eigen::MatrixXcf& unitary, int p, int q);
lapack_complex_float* eigen2lapack(Eigen::MatrixXcf& unitary, int start_line, int start_col, int n_rows, int n_cols);
int main() {

    Eigen::MatrixXcf A(4, 4);
    A << 1.1f + 2.0fi, 5.0f + 6.0fi, 1.0f + 2.0fi, 5.0f + 6.0fi,
         3.0f + 4.0fi, 7.0f + 8.0fi, 3.0f + 4.0fi, 7.0f + 8.0fi,
         1.0f + 2.0fi, 5.0f + 6.0fi, 1.0f + 2.0fi, 5.0f + 6.0fi,
         3.0f + 4.0fi, 7.0f + 8.0fi, 3.0f + 4.0fi, 7.0f + 8.0fi;

    int a = csd(A, 2, 2);

    // Matrix dimensions
    int p = 2, q = 2;
    int m = p + q;
    int ldx11 = m;

    // Input unitary matrix U (2x2 identity)
    // lapack_complex_float X11[4] = {
    //     lapack_make_complex_float(1.0f, 0.0f), lapack_make_complex_float(0.0f, 0.0f),
    //     lapack_make_complex_float(0.0f, 0.0f), lapack_make_complex_float(1.0f, 0.0f)
    // };

    lapack_complex_float X11[1] = {lapack_make_complex_float(0.0f, 0.0f)};
    lapack_complex_float X12[1] = {lapack_make_complex_float(1.0f, 0.0f)};
    lapack_complex_float X21[1] = {lapack_make_complex_float(0.0f, 1.0f)};
    lapack_complex_float X22[1] = {lapack_make_complex_float(0.0f, 0.0f)};

    lapack_complex_float a1 = lapack_make_complex_float(0.0f, 0.1f);

    // Output arrays
    float theta[2]; // min(p,q) = 1
    lapack_complex_float V1T[1], V2T[1], U1[1], U2[1];

    // Workspace
    lapack_complex_float work[1];
    lapack_complex_float rwork[8]; // 8 * min(p,q)
    int lwork = -1;
    int info;

    // Query optimal workspace size
/*      [ X11 | X12 ]
 *  X = [-----------]
 *      [ X21 | X22 ]
 * X is M-by-M
 * X11 is P-by-Q
 *
 * U1 P-by-P
 * U2 (M-P)-by-(M-P))
 * V1 Q-by-Q
 * V2 (M-Q)-by-(M-Q)
 */
std::cout << U1[0];
    std::cout << V2T << "b" <<  std::endl;
    info = LAPACKE_cuncsd(
        LAPACK_COL_MAJOR, // matrix_layout
        'Y', // JOBU1
        'Y', // JOBU2
        'Y', // JOBV1T
        'Y', // JOBV2T
        'T', // TRANS
        'O', // SIGNS
        m, q, p, // M, P, Q
        X11, ldx11, // X11, ldx11
        X12, ldx11, // x12, ldx12
        X21, ldx11, // x21, ldx21
        X22, ldx11, // x11, ldx11
        theta,
        U1, ldx11,
        U2, ldx11,
        V1T, ldx11,
        V2T, ldx11 // x22, ldx22
    );

    std::cout << creal(U1[0]) << "+" << cimag(U1[0]) << "i " <<"\t" << 0 << std::endl <<
                0  << "\t"                                          <<crealf(U2[0]) << "+" << cimag(U2[0])<<"i" << std::endl;
    std::cout << "theta: " << theta[0];


    std::cout << info;


    return 0;
}

int csd(Eigen::MatrixXcf& unitary, int p, int q) {
    int m = unitary.rows();
    int n = unitary.cols();

    lapack_complex_float* X11 = eigen2lapack(unitary, 0, 0, p, q);
    lapack_complex_float* X12 = eigen2lapack(unitary, 0, q, p, n-p);
    lapack_complex_float* X21 = eigen2lapack(unitary, p, 0,m-p, q);
    lapack_complex_float* X22 = eigen2lapack(unitary, p, q, m-p, n-p);

    float theta[std::min(q, q)];

    lapack_complex_float V1T[q*q], V2T[(m-q)*(m-q)], U1[p*p], U2[(m-p)*(m-p)];
    int info = 0;
    int ldx11 = 0;
    info = LAPACKE_cuncsd(
        LAPACK_COL_MAJOR, // matrix_layout
        'Y', // JOBU1
        'Y', // JOBU2
        'Y', // JOBV1T
        'Y', // JOBV2T
        'T', // TRANS
        'O', // SIGNS
        m, q, p, // M, P, Q
        X11, ldx11, // X11, ldx11
        X12, ldx11, // x12, ldx12
        X21, ldx11, // x21, ldx21
        X22, ldx11, // x11, ldx11
        theta,
        U1, ldx11,
        U2, ldx11,
        V1T, ldx11,
        V2T, ldx11 // x22, ldx22
    );
    std::cout << info << "real";
    delete X11;
    return 0;
}

lapack_complex_float* eigen2lapack(Eigen::MatrixXcf& unitary, int start_line, int start_col, int n_rows, int n_cols) {
    lapack_complex_float* U1 = new lapack_complex_float[n_rows * n_cols];

    for (int j = 0; j < n_cols; ++j)
        for (int i = 0; i < n_rows; ++i) {
            float a = unitary(i + start_line, j+start_col).real();
            float b = unitary(i + start_line, j+start_col).imag();
            U1[n_rows*j +i] = lapack_make_complex_float(a, b);
        }
    return U1;
}