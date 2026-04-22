//
// Created by alex.
//

#pragma once
#include <memory>
#include <vector>
#include <string>
#include <variant>
#include <complex>
#include <utility>

#include <Eigen/Dense>

class nodeVisitor;

using return_type = std::variant<
    std::monostate,                       
    double,                               
    std::vector<double>,                  
    std::vector<std::complex<double>>,    
    Eigen::MatrixXcd,                     
    std::pair<Eigen::MatrixXcd, Eigen::MatrixXcd>
>;

/**
 * IASTnode class is the base class of the Abstract Syntax Tree
 * used to parse quantum operations into quantum assembler.
 */
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
