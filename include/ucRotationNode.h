#pragma once

#include <vector>
#include "iast.h"

class UCRotationNode : public IASTnode {
public:
    bool first = false;
    bool inverse = false;
    int name;
    std::vector<double> angles;
    std::unique_ptr<IASTnode> gate1;
    std::unique_ptr<IASTnode> gate2;

    explicit UCRotationNode(const std::vector<double>* angles, bool _first, bool _reverse, bool _inverse);

    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    virtual std::unique_ptr<IASTnode> createBaseRotation(double angle) = 0;
    virtual std::unique_ptr<UCRotationNode> createSubNode(const std::vector<double>* subAngles, bool reverse) = 0;
    void init();
};
