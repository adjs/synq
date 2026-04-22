//
// Created by alex on 07/04/26.
//

#include "../include/unitaryGateNode.h"
#include "../include/one_qubit_gate.h"
#include "../include/csdNode.h"
#include "../include/nodeVisitor.h"
#include <stdexcept>
#include <cmath>

int unitaryGateNode::index = 0;

unitaryGateNode::unitaryGateNode(const Eigen::MatrixXcd& matrix) : data(matrix) {

    if (matrix.size() == 0 || matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("Matrix must be square and non-empty");
    }

    if ((matrix.rows() & (matrix.rows() - 1)) != 0) {
        throw std::invalid_argument("Matrix dimension must be a power of 2 (e.g., 2, 4, 8, 16...)");
    }

    if ((matrix * matrix.adjoint()).isIdentity(1e-10) == false) {
        throw std::invalid_argument("Matrix must be unitary");
    }

    num_qubits = static_cast<int>(log2(static_cast<double>(matrix.rows())));
    name = index++;
    init();
}

void unitaryGateNode::init(){
    if (num_qubits > 1) {
        csd = createCSD(data);
    } else {
        base_unitary = createBaseUnitary(data);
    }
}

unitaryOneQubitGateNode::unitaryOneQubitGateNode(const zyz_result& zyz_params) : params(zyz_params) {
}

void unitaryOneQubitGateNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type unitaryOneQubitGateNode::get_data() {
    return std::vector<double>{
        params.alpha, 
        params.beta, 
        params.gamma, 
        params.delta
    }; 
}

std::unique_ptr<csdNode> unitaryGateNode::createCSD(const Eigen::MatrixXcd& matrix) {
    return std::make_unique<csdNode>(matrix);
}

std::unique_ptr<unitaryOneQubitGateNode> unitaryGateNode::createBaseUnitary(const Eigen::MatrixXcd& matrix) {
    auto zyz = OneQubit::zyz_decomposition(matrix);
    return std::make_unique<unitaryOneQubitGateNode>(zyz);
}

void unitaryGateNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

int unitaryGateNode::get_num_qubits() {
    return num_qubits;
}

return_type unitaryGateNode::get_data() {
    return data;
}