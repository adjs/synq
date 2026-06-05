#pragma once
#include "iast.h"

class rzNode final :public IASTnode {
public:
    explicit rzNode(double theta, int position = -1);
    rzNode();
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    static std::unique_ptr<IASTnode> createRzNode(double angle, int position = -1);
    int position;
private:
    double angle;

};