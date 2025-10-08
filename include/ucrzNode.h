//
// Created by adenilton on 10/4/25.
//

#pragma once
#include <memory>
#include <vector>
#include <string>
#include <variant>

class nodeVisitor;

using return_type = std::variant<double, std::vector<double> >;

class IASTnode
{
public:
    inline static int index = 0;
    int name;
    int num_qubits = 0;
    bool reverse_gate = false;
    virtual ~IASTnode() = default;
    virtual void accept(nodeVisitor &visitor) = 0;
    virtual return_type get_data() = 0;
    virtual int get_num_qubits();
private:
    std::string mName;
};

class uGate:public IASTnode {

};

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
class ucrzNode:public IASTnode {
public:
    bool first=false;

    int name;
    explicit ucrzNode(const std::vector<double>* angles, bool _first, bool _reverse);
    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    std::vector<double> angles;
    std::unique_ptr<IASTnode> gate1;
    std::unique_ptr<IASTnode> gate2;
};

/*
 * first_ucrz --> ucrz cx ucrz cx
 *              | rz cx rz cx
 */
class firstUcrzNode:public ucrzNode {
public:
    explicit firstUcrzNode(const std::vector<double>* angles);
    void accept(nodeVisitor &visitor) override;
};