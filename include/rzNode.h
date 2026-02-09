#pragma once
#include "iast.h"

class rzNode final :public IASTnode {
public:
    explicit rzNode(double theta);
    rzNode();
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
private:
    double angle;

};