//
// Created by adenilton on 10/4/25.
//

#pragma once
#include <memory>
#include <vector>
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

/*
 * ucrz --> ucrz cx ucrz cx
 * ucrz --> rz cx ucrz rz
  * @ param angles vector with two double representing angles of uniformly controlled rz gate
 */
class ucrzNode:public UCRotationNode {
public:
    bool first=false;

    int name;
    explicit ucrzNode(const std::vector<double>* angles, bool _first, bool _reverse, bool _inverse);
    ~ucrzNode() override;                        
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    std::unique_ptr<IASTnode> createBaseRotation(double angle) override;
    std::unique_ptr<UCRotationNode> createSubNode(const std::vector<double>* subAngles, bool reverse) override;
};

/*
 * first_ucrz --> ucrz cx ucrz cx
 *              | rz cx rz cx
 */
class firstUcrzNode:public ucrzNode {
public:
    explicit firstUcrzNode(const std::vector<double>* angles, bool _inverse=false);
    void accept(nodeVisitor &visitor) override;
};
