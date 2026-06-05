#pragma once
#include "iast.h"

class ryNode final :public IASTnode {
public:
    explicit ryNode(double theta, int position = -1);
    ryNode();
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    static std::unique_ptr<IASTnode> createRyNode(double angle, int position = -1);
    int position;
private:
    double angle;
};