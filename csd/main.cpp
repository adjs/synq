

// https://www.netlib.org/lapack/explore-html-3.6.1/df/d14/lapacke__cuncsd_8c_a0d8bba2ce527b3bd6c82a3f6bd31320b.html
// https://netlib.org/lapack/explore-html-3.6.1/de/d0d/zuncsd_8f_a6c456c8f5615f0cc513fa939498e5e79.html

#include "csd.h"
#include <iostream>

void test_x();
void test_t();
void test_rnd();

int main() {
    test_x();
    test_t();
    test_rnd();

    // Eigen::MatrixXcd A(4, 4);
    // A << 1.1f + 2.0fi, 5.0f + 6.0fi, 1.0f + 2.0fi, 5.0f + 6.0fi,
    //      3.0f + 4.0fi, 7.0f + 8.0fi, 3.0f + 4.0fi, 7.0f + 8.0fi,
    //      1.0f + 2.0fi, 5.0f + 6.0fi, 1.0f + 2.0fi, 5.0f + 6.0fi,
    //      3.0f + 4.0fi, 7.0f + 8.0fi, 3.0f + 4.0fi, 7.0f + 8.0fi;
    //
    // int a = csd(A, 2, 2);

    // Matrix dimensions
    // int p = 2, q = 2;
    // int m = p + q;
    // int ldx11 = m;

    // Input unitary matrix U (2x2 identity)
    // lapack_complex_float X11[4] = {
    //     lapack_make_complex_float(1.0f, 0.0f), lapack_make_complex_float(0.0f, 0.0f),
    //     lapack_make_complex_float(0.0f, 0.0f), lapack_make_complex_float(1.0f, 0.0f)
    // };

    // lapack_complex_float X11[1] = {lapack_make_complex_float(0.0f, 0.0f)};
    // lapack_complex_float X12[1] = {lapack_make_complex_float(1.0f, 0.0f)};
    // lapack_complex_float X21[1] = {lapack_make_complex_float(0.0f, 1.0f)};
    // lapack_complex_float X22[1] = {lapack_make_complex_float(0.0f, 0.0f)};
    //
    // lapack_complex_float a1 = lapack_make_complex_float(0.0f, 0.1f);
    //
    // // Output arrays
    // float theta[2]; // min(p,q) = 1
    // lapack_complex_float V1T[1], V2T[1], U1[1], U2[1];
    //
    // // Workspace
    // lapack_complex_float work[1];
    // lapack_complex_float rwork[8]; // 8 * min(p,q)
    // int lwork = -1;
    // int info;

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
// std::cout << U1[0];
//     std::cout << V2T << "b" <<  std::endl;
//     info = LAPACKE_cuncsd(
//         LAPACK_COL_MAJOR, // matrix_layout
//         'Y', // JOBU1
//         'Y', // JOBU2
//         'Y', // JOBV1T
//         'Y', // JOBV2T
//         'T', // TRANS
//         'O', // SIGNS
//         m, q, p, // M, P, Q
//         X11, ldx11, // X11, ldx11
//         X12, ldx11, // x12, ldx12
//         X21, ldx11, // x21, ldx21
//         X22, ldx11, // x11, ldx11
//         theta,
//         U1, ldx11,
//         U2, ldx11,
//         V1T, ldx11,
//         V2T, ldx11 // x22, ldx22
//     );
//
//     std::cout << creal(U1[0]) << "+" << cimag(U1[0]) << "i " <<"\t" << 0 << std::endl <<
//                 0  << "\t"                                          <<crealf(U2[0]) << "+" << cimag(U2[0])<<"i" << std::endl;
//     std::cout << "theta: " << theta[0];
//
//
//     std::cout << info;


    return 0;
}

void test_x() {
    // test x gate
    Eigen::MatrixXcd A(2, 2);
    A << 0.0f + 0.0fi,  1.0f + 0.0fi,
         1.0f + 0.0fi, 0.0f + 0.0fi;

    auto out = csd(A, 1, 1);
    bool test_ver = verify(A, out);
    if (test_ver) std::cout << "x gate ok" << std::endl;
    else std::cout << "no x gate ok" << std::endl;

}

void test_t() {
    Eigen::MatrixXcd T(4, 4);
    T << 1.0f + 0.0fi, 0.0f + 0.0fi,  0.0f + 0.0fi,  0.0f + 0.0fi,
         0.0f + 0.0fi, 1.0f + 0.0fi,  0.0f + 0.0fi,  0.0f + 0.0fi,
         0.0f + 0.0fi, 0.0f + 0.0fi,  0.0f + 0.0fi,  1.0f + 0.0fi,
         0.0f + 0.0fi, 0.0f + 0.0fi,  1.0f + 0.0fi,  0.0f + 0.0fi;

    auto out = csd(T, 2, 2);
    auto test_ver = verify(T, out);

    if (test_ver) std::cout << "T gate ok" << std::endl;
    else std::cout << "no T gate ok" << std::endl;
}

void test_rnd() {
    Eigen::MatrixXcd T(4, 4);
    T << (2.364882618857422347e-01-4.822143073226670129e-01j),
    (6.829647732695640072e-02+4.447897757628520299e-02j),
    (5.115007388835463020e-01-9.529865837327188005e-02j),
    (5.520571865947265788e-01-3.597469917942807127e-01j),
 (-1.114816726427168281e-01+6.978032089401685623e-01j),
    (-2.494382786327934143e-01+8.410701104345530421e-02j),
    (4.670592911721889728e-01-4.319298125262461818e-01j),
    (1.622065409340211206e-01-1.817602163908954571e-02j),
 (-2.235192632554647840e-01-2.591835234472851801e-01j),
    (2.436499611612899796e-01-5.375622959989125038e-02j),
    (-9.259829400673319499e-02-5.381058778231553319e-01j),
    (2.726770843179722736e-01+6.694197728029507299e-01j),
 (1.151995301476407552e-01-2.859672891120846883e-01j),
    (-9.016492271986602525e-01-2.209918615739195902e-01j),
    (-9.627758278964056171e-02-1.310559524249576557e-01j),
    (-2.001520487551047139e-02+1.276612783179109645e-01j);

    auto out = csd(T, 2, 2);
    auto test_ver = verify(T, out);

    if (test_ver) std::cout << "rnd gate ok" << std::endl;
    else std::cout << "no rnd gate ok" << std::endl;
}