//
// Created by adenilton on 10/4/25.
//

#pragma once

#include "ucrzNode.h"


class nodeVisitor {
public:
    virtual ~nodeVisitor() = default;
    virtual void visit(rzNode &node) = 0;
    virtual void visit(ucrzNode &node) = 0;
    virtual void visit(firstUcrzNode &node) = 0;
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
    explicit qasmVisitor(int num_qubits);
    void visit(rzNode &node) override;
    void visit(firstUcrzNode &node) override;
    void visit(ucrzNode &node) override;
};
