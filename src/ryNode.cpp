#include "../include/ryNode.h"
#include "../include/nodeVisitor.h"

ryNode::ryNode(const double theta) {
    num_qubits = 1;
    angle = theta;
}

ryNode::ryNode() {
    num_qubits = 1;
    angle = 0.0;
}

void ryNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type ryNode::get_data() {
    return angle;
}