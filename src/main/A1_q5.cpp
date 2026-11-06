#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) {
    if (grid.empty()) return {};
    int rows = grid.size();
    int cols = grid[0].size();
    if (cols == 0) throw std::invalid_argument("empty col");
    
    for (int i = 0; i < rows; ++i) {
        if ((int)grid[i].size() != cols) throw std::invalid_argument("diff length");
        for (char c : grid[i]) {
            if (c != '.' && c != '#') throw std::invalid_argument("bad char");
        }
    }
    
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '#') {
                result[r][c] = -1;
            } else {
                int cnt = 0;
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '#') {
                        cnt++;
                    }
                }
                result[r][c] = cnt;
            }
        }
    }
    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
