#include<iostream>

using namespace std;
#include <gtest/gtest.h>
#include "../include/one_qubit_gate.h"
#include "../include/unitary.h"
#include<Eigen/Dense>
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, Basic2) {
  Eigen::Matrix2cd h = OneQubit::h_matrix();

  auto result = OneQubit::zyz_decomposition(h);
  const Eigen::Matrix2cd h_tilde = exp(result.alpha*1i) * OneQubit::rz_matrix(result.beta) *
                        OneQubit::ry_matrix(result.gamma) * OneQubit::rz_matrix(result.delta);
  EXPECT_TRUE(h.isApprox(h_tilde));
}

TEST(OneQubitGate, unitary2qasm) {
    Eigen::MatrixXcd temp = OneQubit::h_matrix();
    auto gate = unitary(temp);
    const string out = gate.unitary2qasm();
    cout << out << endl;
}