//
// Created by alex on 07/04/26.
//

#include "../include/unitaryGateNode.h"
#include "../include/one_qubit_gate.h"
#include "../include/csdNode.h"
#include "../include/nodeVisitor.h"
#include "../include/twoQubitsUnitary.h"
#include "../include/ryNode.h"
#include "../include/rzNode.h"
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
    if (num_qubits > 2) {
        csd = createCSD(data);
    } else if (num_qubits == 2) {
        csd = createTwoQubitUnitary(data);
    } else {
        csd = createBaseUnitary(data);
    }
}

unitaryOneQubitGateNode::unitaryOneQubitGateNode(const zyz_result& zyz_params, int position) : params(zyz_params), position(position) {
}

twoQubitGateNode::twoQubitGateNode(const Eigen::MatrixXcd& matrix) {
    auto decomp_result = twoQubitsUnitaryDecomposition(matrix);
    
    gate_a = unitaryGateNode::createBaseUnitary(decomp_result.A, 0);
    gate_b = unitaryGateNode::createBaseUnitary(decomp_result.B, 1);
    gate_c = unitaryGateNode::createBaseUnitary(decomp_result.C, 1);
    gate_d = unitaryGateNode::createBaseUnitary(decomp_result.D, 0);
    
    rz_theta = rzNode::createRzNode(-1 * decomp_result.angleRz, 1); 
    ry1_theta = ryNode::createRyNode(-1 *decomp_result.angleRy1, 0);
    ry2_theta = ryNode::createRyNode( decomp_result.angleRy2, 0);
    
    phase = decomp_result.phase;
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

std::unique_ptr<IASTnode> unitaryGateNode::createCSD(const Eigen::MatrixXcd& matrix) {
    return std::make_unique<csdNode>(matrix);
}

std::unique_ptr<IASTnode> unitaryGateNode::createBaseUnitary(const Eigen::MatrixXcd& matrix, int position) {
    auto zyz = OneQubit::zyz_decomposition(matrix);
    return std::make_unique<unitaryOneQubitGateNode>(zyz, position);
}

std::unique_ptr<IASTnode> unitaryGateNode::createTwoQubitUnitary(const Eigen::MatrixXcd& matrix) {
    return std::make_unique<twoQubitGateNode>(matrix);
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

void twoQubitGateNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type twoQubitGateNode::get_data() {
    return phase; 
}