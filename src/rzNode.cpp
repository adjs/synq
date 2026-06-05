//
// Created by Adenilton on 08/02/26.
//
#include "../include/rzNode.h"
#include "../include/nodeVisitor.h"

rzNode::rzNode(const double theta, int position): position(position) {
    num_qubits = 1;
    angle = theta;
}

rzNode::rzNode() : position(-1){
    num_qubits = 1;
    angle = 0.0;
}

void rzNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type rzNode::get_data() {
    return angle;
}

std::unique_ptr<IASTnode> rzNode::createRzNode(double angle, int position) {
    return std::make_unique<rzNode>(angle, position);
}