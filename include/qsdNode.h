//
// Created by alex on 07/04/26.
//

#pragma once
#include <memory>
#include <vector>
#include "iast.h"
#include <Eigen/Dense>
#include "qsd.h"
#include "unitaryGateNode.h"
#include "ucrzNode.h"

/*
 * qsd --> unitary ucrz unitary
  * @ params two unitary matrices corresponding to the mux gate in the CSD decomposition
 */
class qsdNode final : public IASTnode {
public:
    explicit qsdNode(const Eigen::MatrixXcd& gate1, const Eigen::MatrixXcd& gate2);
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    std::unique_ptr<unitaryGateNode> gate_v;
    std::unique_ptr<unitaryGateNode> gate_w;
    std::unique_ptr<ucrzNode> ucrz;

private:
    std::unique_ptr<unitaryGateNode> createUnitary(const Eigen::MatrixXcd& matrix);
    std::unique_ptr<ucrzNode> createUcrz(const std::vector<double>& angles);
    Eigen::MatrixXcd m_gate1; 
    Eigen::MatrixXcd m_gate2;
};