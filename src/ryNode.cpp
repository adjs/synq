#include "../include/ryNode.h"
#include "../include/nodeVisitor.h"

ryNode::ryNode(const double theta, int position): position(position) {
    num_qubits = 1;
    angle = theta;
}

ryNode::ryNode() : position(-1) {
    num_qubits = 1;
    angle = 0.0;
}

void ryNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type ryNode::get_data() {
    return angle;
}

std::unique_ptr<IASTnode> ryNode::createRyNode(double angle, int position) {
    return std::make_unique<ryNode>(angle, position);
}