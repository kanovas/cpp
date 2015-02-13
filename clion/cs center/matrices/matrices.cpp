#include "matrices.hpp"

matrix::matrix(int n, int m, double** const& matrix_) {
    this->n = n;
    this->m = m;
    this->matrix_ = matrix_;
}

matrix& matrix::operator = (matrix const& other) {
    n = other.n;
    m = other.m;
    matrix_ = other.matrix_;
    return *this;
}

matrix::~matrix() {
    for(int i = 0; i < n; i++) {
        delete[] matrix_[i];
    }
    delete [] matrix_;
    matrix_ = 0;
}

matrix& matrix::read_matrix(std::ifstream& input) {
    try {
        input >> n >> m;
        double** matrix_ = new double*[n];
        for(int i = 0; i < n; i++) {
            matrix_[i] = new double[m];
            for(int j = 0; j < m; j++) {
                input >> matrix_[i][j];
            }
        }
        return *this;
    }
    catch (...) {
        throw std::runtime_error("Wrong matrix file format");
    }
}

void matrix::print_matrix(std::ostream& out) {
    out << n << ' ' << m << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            out << matrix_[i][j] << ' ';
        }
        out << endl;
    }
}

matrix& matrix::operator += (matrix const& a) {
    if(n != a.n || m != a.m) {
        throw std::runtime_error("Impossible to count sum for matrices of different sizes");
    }
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix_[i][j] += a.matrix_[i][j];
        }
    }
    return *this;
}

matrix& matrix::operator *= (matrix const& a) {
    if(m != a.n) {
        throw std::runtime_error("Impossible to multiply matrices where m1 != n2");
    }
    matrix* that = this;
    long long cur_sum;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cur_sum = 0;
            for(int k = 0; k < m; k++) {
                cur_sum += that->matrix_[i][k] * a.matrix_[k][j];
            }
            matrix_[i][j] = cur_sum;
        }
    }
    return *this;
}