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

// Assessment 01 B1; see 题面.pdf.
namespace aim::b1 {


// BEGIN IMPLEMENTATION
// aim-cpp-cw
bool parse_i32(const std::string& text, int& output) {
    if (text.empty()) return false;
    int i = 0;
    bool neg = false;
    if (text[0] == '+' || text[0] == '-') {
        neg = (text[0] == '-');
        i = 1;
    }
    if (i >= (int)text.size()) return false;
    
    long long val = 0;
    for (; i < (int)text.size(); ++i) {
        if (text[i] < '0' || text[i] > '9') return false;
        val = val * 10 + (text[i] - '0');
        if (val > 2147483648LL) return false;
    }
    
    if (neg) {
        if (val > 2147483648LL) return false;
        output = (val == 2147483648LL) ? -2147483648 : -(int)val;
    } else {
        if (val > 2147483647LL) return false;
        output = (int)val;
    }
    return true;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::b1;
int main() {
    try {
        { int x=9; CHECK(parse_i32("-12",x) && x==-12); }
        { int x=9; CHECK(!parse_i32("12x",x) && x==9); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
