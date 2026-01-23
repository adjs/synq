//
// Created by alex.
//

#pragma once
#include <memory>
#include <vector>
#include "iast.h"
#include "ucryNode.h"


class qspUcrNode final: public IASTnode {
public:
    bool first = false;
    int name;
   
    std::unique_ptr<IASTnode> next_qsp;
    std::unique_ptr<ucryNode> ucry;
    std::unique_ptr<ryNode> base_ry;

    explicit qspUcrNode(const std::vector<double>* state);

    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    std::unique_ptr<ryNode> createBaseQsp(double angle);
    std::unique_ptr<qspUcrNode> createSubQsp(const std::vector<double>* subState);
    std::unique_ptr<ucryNode> createUcry(const std::vector<double>* angles_ry);
    void init();

private:
    std::vector<double> state;
    std::vector<double> angles_ry;
    std::vector<double> next_state;
};
