#ifndef MATRICES_CS_HPP
#define MATRICES_CS_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

struct matrix {
    matrix(int n, int m, double** const& matrix_);
    matrix& operator = (matrix const& other);
    ~matrix();

    matrix& read_matrix(std::ifstream& input);
    void print_matrix(std::ostream& out);

    matrix& operator += (matrix const& a);
    matrix& operator *= (matrix const& a);
private:
    double ** matrix_;
    int n;
    int m;
};

#endif