//
// Created by alex.
//

#pragma once
#include <memory>
#include <vector>
#include <complex>
#include "iast.h"
#include "ucryNode.h"
#include "ucrzNode.h"


/*
 * qsp --> qsp ucry ucrz
 *       | ry rz
 */

class qspUcrNode final: public IASTnode {
public:
    bool first = false;
    int name;
   
    std::unique_ptr<IASTnode> next_qsp;
    std::unique_ptr<ucryNode> ucry;
    std::unique_ptr<ucrzNode> ucrz;
    std::unique_ptr<ryNode> base_ry;
    std::unique_ptr<rzNode> base_rz;

    explicit qspUcrNode(const std::vector<std::complex<double>>* state);

    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    std::unique_ptr<ryNode> createBaseRy(double angles_ry);
    std::unique_ptr<rzNode> createBaseRz(double angles_rz);
    std::unique_ptr<qspUcrNode> createSubQsp(const std::vector<std::complex<double>>* subState);
    std::unique_ptr<ucryNode> createUcry(const std::vector<double>* angles_ry);
    std::unique_ptr<ucrzNode> createUcrz(const std::vector<double>* angles_rz);
    void init();

private:
    std::vector<std::complex<double>> state;
    std::vector<double> angles_ry;
    std::vector<double> angles_rz;
    std::vector<std::complex<double>> next_state;
};
