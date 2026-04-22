//
// Created by alex on 07/04/26.
//

#include "../include/csdNode.h"
#include "../include/csd.h"
#include "../include/nodeVisitor.h"
#include "../include/qsdNode.h"
#include "../include/ucryNode.h"    

csdNode::csdNode(const Eigen::MatrixXcd& matrix) : m_matrix(matrix) {
    auto csdValues = csd(matrix, matrix.rows() / 2, matrix.cols() / 2);
    qsd1 = createQSD(csdValues.V1T, csdValues.V2T);
    qsd2 = createQSD(csdValues.U1, csdValues.U2);
    Eigen::VectorXd theta_eigen = Eigen::Map<Eigen::VectorXd>(csdValues.theta.data(), csdValues.theta.size());
    Eigen::VectorXd angles_eigen = 2.0 * theta_eigen;
    std::vector<double> angles(angles_eigen.data(), angles_eigen.data() + angles_eigen.size());
    ucry = createUcry(angles);
}

std::unique_ptr<qsdNode> csdNode::createQSD(const Eigen::MatrixXcd& gate1, const Eigen::MatrixXcd& gate2) {
    return std::make_unique<qsdNode>(gate1, gate2);
}

std::unique_ptr<ucryNode> csdNode::createUcry(const std::vector<double>& angles) {
    return std::make_unique<firstUcryNode>(&angles, false);
}

void csdNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type csdNode::get_data() {
    return m_matrix;
}