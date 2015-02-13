#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <vector>
#include <bits/stl_queue.h>

using namespace std;

void zip(std::ifstream & in, std::ofstream & out);
void unzip(std::ifstream & in, std::ofstream & out);

#endif