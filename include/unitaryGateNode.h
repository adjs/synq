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
    explicit unitaryOneQubitGateNode(const zyz_result& zyz_params);
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    zyz_result params; 
};

/*
 * unitary -> csd
 * unitary -> one_qubit_gate
  * @ params unitary matrix to be decomposed
 */
class unitaryGateNode final : public IASTnode {
public:
    explicit unitaryGateNode(const Eigen::MatrixXcd& matrix);
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    std::unique_ptr<csdNode> csd;
    std::unique_ptr<unitaryOneQubitGateNode> base_unitary;
    int get_num_qubits();

private:
    Eigen::MatrixXcd data;
    static int index;
    int name;

    void init();
    std::unique_ptr<csdNode> createCSD(const Eigen::MatrixXcd& matrix);
    std::unique_ptr<unitaryOneQubitGateNode> createBaseUnitary(const Eigen::MatrixXcd& matrix);
};