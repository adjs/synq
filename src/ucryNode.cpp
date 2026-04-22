//
// Created by alex.
//

#include "../include/ucryNode.h"
#include "../include/ryNode.h"

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

return_type ucryNode::get_data() {
    return std::vector<double>{}; 
}
