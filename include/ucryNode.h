//
// Created by alex.
//

#pragma once
#include <memory>
#include <vector>
#include "ucRotationNode.h"

/*
 * ucry --> ucry cx ucry cx
 * ucry --> ry cx ucry ry
  * @ param angles vector with two double representing angles of uniformly controlled ry gate
 */
class ucryNode:public UCRotationNode {
public:
    bool first=false;

    int name;
    return_type get_data() override;
    explicit ucryNode(const std::vector<double>* angles, bool _first, bool _reverse, bool _inverse);
    void accept(nodeVisitor &visitor) override;
    std::unique_ptr<IASTnode> createBaseRotation(double angle) override;
    std::unique_ptr<UCRotationNode> createSubNode(const std::vector<double>* subAngles, bool reverse) override;
};

/*
 * first_ucry --> ucry cx ucry cx
 *              | ry cx ry cx
 */
class firstUcryNode:public ucryNode {
public:
    explicit firstUcryNode(const std::vector<double>* angles, bool _inverse=false);
    void accept(nodeVisitor &visitor) override;
};