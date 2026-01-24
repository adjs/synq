//
// Created by adenilton on 10/4/25.
//

#include "../include/ucrzNode.h"

#include <algorithm>
#include<cmath>
#include <iostream>
#include <ostream>
#include "../include/nodeVisitor.h"

ucrzNode::ucrzNode(const std::vector<double>* angles, const bool _first = false, const bool _reverse=false, const bool _inverse=false) : UCRotationNode(angles, _first, _reverse, _inverse) {
    init();
}

std::unique_ptr<IASTnode> ucrzNode::createBaseRotation(double angle) {
    return std::make_unique<rzNode>(angle);
}

std::unique_ptr<UCRotationNode> ucrzNode::createSubNode(const std::vector<double>* subAngles) {
    return std::make_unique<ucrzNode>(subAngles, false, false, this->inverse);
}

firstUcrzNode::firstUcrzNode(const std::vector<double>* angles, const bool _inverse) : ucrzNode(angles, true, false, _inverse){
}

void firstUcrzNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

int IASTnode::get_num_qubits() {
    return num_qubits;
}

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


ucrzNode::~ucrzNode() {
}

void ucrzNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type ucrzNode::get_data() {
    return std::vector<double>{}; 
}