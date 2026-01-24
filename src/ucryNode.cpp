//
// Created by alex.
//

#include "../include/ucryNode.h"

#include <algorithm>
#include<cmath>
#include <iostream>
#include <ostream>
#include "../include/nodeVisitor.h"

ucryNode::ucryNode(const std::vector<double>* angles, const bool _first = false, const bool _reverse=false, const bool _inverse=false) : UCRotationNode(angles, _first, _reverse, _inverse) {
    init();
}

std::unique_ptr<IASTnode> ucryNode::createBaseRotation(double angle) {
    return std::make_unique<ryNode>(angle);
}

std::unique_ptr<UCRotationNode> ucryNode::createSubNode(const std::vector<double>* subAngles, bool reverse) {
    return std::make_unique<ucryNode>(subAngles, false, reverse, this->inverse);
}

void ucryNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

firstUcryNode::firstUcryNode(const std::vector<double>* angles, const bool _inverse) : ucryNode(angles, true, false, _inverse){
}

void firstUcryNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

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