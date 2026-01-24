//
// Created by alex.
//

#include <gtest/gtest.h>
#include "../include/qspUcrNode.h"
#include "../include/nodeVisitor.h"
#include <iostream>
#include <complex>

TEST(QSPTests, UniformSuperposition2Qubits) {

    std::vector<std::complex<double>> state = {0.5, 0.5, 0.5, 0.5};

    auto qsp = qspUcrNode(&state);
    auto visitor = qasmVisitor(2);

    qsp.accept(visitor);

    std::cout << visitor.qasm_code << std::endl;

    EXPECT_FALSE(visitor.qasm_code.empty());
    EXPECT_NE(visitor.qasm_code.find("OPENQASM"), std::string::npos);
}

TEST(QSPTests, RandomState3Qubits) {

    std::vector<std::complex<double>> state = {0.2, 0.2, 0.3, 0.4, 0.4, 0.5, 0.3, 0.4123};

    auto qsp = qspUcrNode(&state);
    auto visitor = qasmVisitor(3);

    qsp.accept(visitor);

    std::cout << visitor.qasm_code << std::endl;

    EXPECT_FALSE(visitor.qasm_code.empty());
    EXPECT_NE(visitor.qasm_code.find("OPENQASM"), std::string::npos);
}

TEST(QSPTests, BasisState2Qubits) {

    std::vector<std::complex<double>> state = {0, 0, 1, 0};

    auto qsp = qspUcrNode(&state);
    auto visitor = qasmVisitor(2);

    qsp.accept(visitor);

    std::cout << visitor.qasm_code << std::endl;

    EXPECT_FALSE(visitor.qasm_code.empty());
    EXPECT_NE(visitor.qasm_code.find("OPENQASM"), std::string::npos);
}

TEST(QSPTests, ComplexState2Qubits) {

    std::vector<std::complex<double>> state = {
        0.122 + 0.0j,   
        0.0 + 0.122j,   
        0.173 - 0.433j,
        0.520 + 0.693j
    };

    auto qsp = qspUcrNode(&state);
    auto visitor = qasmVisitor(2);

    qsp.accept(visitor);

    std::cout << visitor.qasm_code << std::endl;

    EXPECT_FALSE(visitor.qasm_code.empty());
    EXPECT_NE(visitor.qasm_code.find("OPENQASM"), std::string::npos);
}
