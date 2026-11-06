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

// Assessment 01 Q6; see 题面.pdf.
namespace aim::q6 {
struct Target { int id; int x; int y; int hp; bool visible; };

// BEGIN IMPLEMENTATION
// aim-cpp-cw
int select_target(const std::vector<Target>& targets, int max_range) {
    if (max_range < 0 || targets.empty()) return -1;
    
    long long max_range_sq = (long long)max_range * max_range;
    int best_id = -1;
    int best_hp = 0;
    long long best_dist_sq = 0;
    
    for (const auto& t : targets) {
        if (!t.visible || t.hp <= 0) continue;
        long long dist_sq = (long long)t.x * t.x + (long long)t.y * t.y;
        if (dist_sq > max_range_sq) continue;
        
        if (best_id == -1 || 
            t.hp < best_hp || 
            (t.hp == best_hp && dist_sq < best_dist_sq) || 
            (t.hp == best_hp && dist_sq == best_dist_sq && t.id < best_id)) {
            best_id = t.id;
            best_hp = t.hp;
            best_dist_sq = dist_sq;
        }
    }
    return best_id;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q6;
int main() {
    try {
        { CHECK(select_target({{7,3,4,20,true},{2,0,5,20,true}},5)==2); }
        { CHECK(select_target({},5)==-1); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
