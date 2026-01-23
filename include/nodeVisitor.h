//
// Created by adenilton on 10/4/25.
//

#pragma once

#include "ucrzNode.h"
#include "ucryNode.h"
#include "iast.h"
#include "qspUcrNode.h"


class nodeVisitor {
public:
    virtual ~nodeVisitor() = default;
    virtual void visit(rzNode &node) = 0;
    virtual void visit(ucrzNode &node) = 0;
    virtual void visit(firstUcrzNode &node) = 0;
    virtual void visit(ryNode &node) = 0;
    virtual void visit(ucryNode &node) = 0;
    virtual void visit(firstUcryNode &node) = 0;
    virtual void visit(UCRotationNode &node) = 0;
    virtual void visit(qspUcrNode &node) = 0;
};

struct return_type_visitor {
  std::string operator()(const double a) {
      return std::to_string(a);
  }
    std::string operator()(const std::vector<double> a) {
      return "";
  }
};

class qasmVisitor : public nodeVisitor {
public:
    std::string qasm_code;
    int _num_qubits;
    int active_target = -1;
    explicit qasmVisitor(int num_qubits);
    void visit(rzNode &node) override;
    void visit(firstUcrzNode &node) override;
    void visit(ucrzNode &node) override;
    void visit(ryNode &node) override;
    void visit(firstUcryNode &node) override;
    void visit(ucryNode &node) override;
    void visit(UCRotationNode &node) override;
    void visit(qspUcrNode &node) override;
};
