//
// Created by adenilton on 10/4/25.
//

#pragma once
# include "one_qubit_gate.h"
#include <string>
class unitary {
public:
    explicit unitary(const Eigen::MatrixXcd &);
    std::string unitary2qasm();
private:
    Eigen::MatrixXcd data;
};