//
// Created by adenilton on 10/4/25.
//

#ifndef TEST_TWO_QUBIT_GATE_H
#define TEST_TWO_QUBIT_GATE_H
#include<Eigen/Dense>

class ctrl_qubit_gate {
public:
    explicit ctrl_qubit_gate(Eigen::Matrix2cd uMatrix);
    std::string to_qasm();
private:
    Eigen::Matrix2cd data;
};


#endif //TEST_TWO_QUBIT_GATE_H