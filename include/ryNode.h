#pragma once
#include "iast.h"

class ryNode final :public IASTnode {
public:
    explicit ryNode(double theta);
    ryNode();
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
private:
    double angle;
};