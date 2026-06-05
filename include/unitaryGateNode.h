//
// Created by alex on 07/04/26.
//

#pragma once
#include "iast.h"
#include <Eigen/Dense>
#include <memory>
#include "one_qubit_gate.h"

class csdNode;

class unitaryOneQubitGateNode final : public IASTnode {
public:
    explicit unitaryOneQubitGateNode(const zyz_result& zyz_params, int position = 0);
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    zyz_result params; 
    int position;
};

class twoQubitGateNode final : public IASTnode {
public:
    explicit twoQubitGateNode(const Eigen::MatrixXcd& matrix);
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    
    std::unique_ptr<IASTnode> gate_a;
    std::unique_ptr<IASTnode> gate_b;
    std::unique_ptr<IASTnode> gate_c;
    std::unique_ptr<IASTnode> gate_d;
    
    std::unique_ptr<IASTnode> rz_theta;
    std::unique_ptr<IASTnode> ry1_theta;
    std::unique_ptr<IASTnode> ry2_theta;
    
    double phase;
};

/*
 * unitary -> csd
 * unitary -> two_qubit_gate
 * unitary -> one_qubit_gate
  * @ params unitary matrix to be decomposed
 */
class unitaryGateNode final : public IASTnode {
public:
    explicit unitaryGateNode(const Eigen::MatrixXcd& matrix);
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    std::unique_ptr<IASTnode> csd;
    int get_num_qubits();
    static std::unique_ptr<IASTnode> createBaseUnitary(const Eigen::MatrixXcd& matrix, int position = 0);

private:    
    Eigen::MatrixXcd data;
    static int index;
    int name;

    void init();
    std::unique_ptr<IASTnode> createCSD(const Eigen::MatrixXcd& matrix);
    std::unique_ptr<IASTnode> createTwoQubitUnitary(const Eigen::MatrixXcd& matrix);
};