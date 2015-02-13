#include "matrices.cpp"

using namespace std;

int main(int argc, char ** argv) {
    matrix* ans = new matrix(0, 0, new double*[0]);
    char c = 'm';
    for(int i = 1; i < argc; ++i) {
        matrix* matr = new matrix(0, 0, new double*[0]);
        unsigned long pos;
        string arg = argv[i];
        if (c == 'm') {
            pos = arg.find(".txt");
            if(pos && pos < arg.length()) {
                if(pos == arg.length() - 4) {
                    try {
                        ifstream input;
                        input.open(argv[i]);
                        matr->read_matrix(input);
                        //matr->print_matrix(cout);
                        c = 'o';
                    }
                    catch (...) {
                        throw std::runtime_error("Wrong matrix file");
                    }
                }
                else {
                    throw std::runtime_error("You should input matrix in file matrix_name.txt");
                }
            }
            else {
                throw std::runtime_error("You should input matrix in file matrix_name.txt");
            }
        }
        else {
            pos = arg.find("--");
            if(!pos) {
                if(arg.find("add") && arg.length() == 5) {
                    *ans += *matr;
                    c = 'm';
                }
                else if(arg.find("mult") && arg.length() == 6) {
                    *ans *= *matr;
                    c = 'm';
                }
                else {
                    throw std::runtime_error("Wrong operation. The program supports --add and --mult");
                }
            }
            else {
                throw std::runtime_error("Wrong operation format. The program supports --add and --mult");
            }
        }
    }
    ans->print_matrix(cout);
    return 0;
}