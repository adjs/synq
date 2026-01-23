#include "../include/qspUcrNode.h"

#include <algorithm>
#include <cmath>
#include "../include/nodeVisitor.h"

qspUcrNode::qspUcrNode(const std::vector<double>* state) {
    num_qubits = static_cast<int>(log2(static_cast<double>(state->size())));
    name = index++;
    this->state = *state;
    first = false;
    reverse_gate = false;
    this->next_state.resize(state->size()/2);
    this->angles_ry.resize(state->size()/2);
    init();
}

void qspUcrNode::init(){
  
    if(num_qubits > 1){
        for (int i = 0; i < this->state.size()/2; i++){
            this->next_state[i] = std::sqrt((std::pow(this->state[2*i],2) + std::pow(this->state[2*i+1],2)));
            this->angles_ry[i] = 2 * std::asin(this->state[2*i+1] / this->next_state[i]);
        }

        next_qsp = createSubQsp(&next_state);
        ucry = createUcry(&angles_ry);
    }
    else{
        this->base_ry = createBaseQsp(2 * std::asin(this->state[1] / std::sqrt((std::pow(this->state[0],2) + std::pow(this->state[1],2)))));
    }


}

void qspUcrNode::accept(nodeVisitor &visitor) {
    visitor.visit(*this);
}

return_type qspUcrNode::get_data() {
    return state;
}

std::unique_ptr<ryNode> qspUcrNode::createBaseQsp(double angle) {
    return std::make_unique<ryNode>(angle);
}

std::unique_ptr<qspUcrNode> qspUcrNode::createSubQsp(const std::vector<double>* subState) {
    return std::make_unique<qspUcrNode>(subState);
}

std::unique_ptr<ucryNode> qspUcrNode::createUcry(const std::vector<double>* angles_ry) {
    return std::make_unique<ucryNode>(angles_ry, false, false);
}

