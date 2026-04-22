//
// Created by alex on 07/04/26.
//

#pragma once
#include <memory>
#include <vector>
#include "iast.h"
#include <Eigen/Dense>
#include "csd.h"
#include "qsdNode.h"
#include "ucryNode.h"

/*
 * csd --> qsd ucry qsd
  * @ param unitary matrix to be decomposed
 */
class csdNode final : public IASTnode {
public:
    explicit csdNode(const Eigen::MatrixXcd& matrix);
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    std::unique_ptr<qsdNode> qsd1;
    std::unique_ptr<qsdNode> qsd2;
    std::unique_ptr<ucryNode> ucry;

private:
    std::unique_ptr<qsdNode> createQSD(const Eigen::MatrixXcd& gate1, const Eigen::MatrixXcd& gate2);
    std::unique_ptr<ucryNode> createUcry(const std::vector<double>& angles);
    Eigen::MatrixXcd m_matrix;
};