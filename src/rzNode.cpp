//
// Created by Adenilton on 08/02/26.
//
#include "../include/rzNode.h"
#include "../include/nodeVisitor.h"

rzNode::rzNode(const double theta) {
    num_qubits = 1;
    angle = theta;
}

rzNode::rzNode() {
    num_qubits = 1;
    angle = 0.0;
}

void rzNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type rzNode::get_data() {
    return angle;
}