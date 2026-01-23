//
// Created by alex.
//

#pragma once
#include <memory>
#include <vector>
#include "ucRotationNode.h"


class ryNode final :public IASTnode {
public:
    explicit ryNode(double theta);
    ryNode();
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
private:
    double angle;

};

/*
 * ucry --> ucry cx ucry cx
 * ucry --> ry cx ucry ry
  * @ param angles vector with two double representing angles of uniformly controlled ry gate
 */
class ucryNode:public UCRotationNode {
public:
    bool first=false;

    int name;
    explicit ucryNode(const std::vector<double>* angles, bool _first, bool _reverse);
    std::unique_ptr<IASTnode> createBaseRotation(double angle) override;
    std::unique_ptr<UCRotationNode> createSubNode(const std::vector<double>* subAngles) override;
};

/*
 * first_ucry --> ucry cx ucry cx
 *              | ry cx ry cx
 */
class firstUcryNode:public ucryNode {
public:
    explicit firstUcryNode(const std::vector<double>* angles);
    void accept(nodeVisitor &visitor) override;
};