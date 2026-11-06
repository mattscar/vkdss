#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

int main() {
    // Load MTX file
    std::ifstream infile("bcsstk01.mtx");
    if (!infile) {
        std::cerr << "Error: could not open matrix file" << std::endl;
        return 1;
    }

    // Skip comments
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '%') continue;
        break;
    }

    // Read matrix dimensions
    std::stringstream ss(line);
    int rows, cols, nnz;
    ss >> rows >> cols >> nnz;

    // Create data containers on host
    std::vector<int> rowStarts(rows + 1, 0);
    std::vector<int> colIndices(nnz);
    std::vector<double> values(nnz);
    std::vector<double> rhs(rows, 0.0);
    std::vector<std::tuple<int, int, double>> entries(nnz);

    // Create vector entries
    int rowIndex, colIndex;
    double value;
    for (int i = 0; i < nnz; i++) {
        infile >> rowIndex >> colIndex >> value;
        entries[i] = std::make_tuple(rowIndex - 1, colIndex - 1, value);
        rowStarts[rowIndex]++;
        rhs[rowIndex - 1] += value;
    }
    infile.close();

    // Update rowStarts array
    for (int i = 1; i < rowStarts.size(); ++i) {
        rowStarts[i] += rowStarts[i - 1];
    }

    // Sort file entries
    std::sort(entries.begin(), entries.end(),
        [](const auto& a, const auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        });

    // Get column indices and values
    for (int i = 0; i < nnz; i++) {
        colIndices[i] = std::get<1>(entries[i]);
        values[i] = std::get<2>(entries[i]);
    }
    
    return 0;
}