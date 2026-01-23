//
// Created by alex.
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

class UCRotationNode : public IASTnode {
public:
    bool first = false;
    int name;
    std::vector<double> angles;
    std::unique_ptr<IASTnode> gate1;
    std::unique_ptr<IASTnode> gate2;

    explicit UCRotationNode(const std::vector<double>* angles, bool _first, bool _reverse);

    void accept(nodeVisitor &visitor) override;
    return_type get_data() override;
    virtual std::unique_ptr<IASTnode> createBaseRotation(double angle) = 0;
    virtual std::unique_ptr<UCRotationNode> createSubNode(const std::vector<double>* subAngles) = 0;
    void init();
};
