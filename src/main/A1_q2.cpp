#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

namespace aim::q2 {

struct LabelEdit { 
    std::string from; 
    std::string to; 
};

// BEGIN IMPLEMENTATION
// aim-cpp-cw
std::string edit_labels(std::string labels, const std::vector<LabelEdit>& edits) {
    std::vector<std::string> vec;
    
    if (!labels.empty()) {
        size_t start = 0;
        size_t pos = labels.find(',');
        while (pos != std::string::npos) {
            vec.push_back(labels.substr(start, pos - start));
            start = pos + 1;
            pos = labels.find(',', start);
        }
        vec.push_back(labels.substr(start));
    }
    
    for (size_t i = 0; i < edits.size(); ++i) {
        const std::string& from = edits[i].from;
        const std::string& to = edits[i].to;
        
        if (from.empty()) {
            if (!to.empty()) {
                vec.push_back(to);
            }
        } else {
            for (size_t j = 0; j < vec.size(); ++j) {
                if (vec[j] == from) {
                    if (to.empty()) {
                        vec.erase(vec.begin() + j);
                    } else {
                        vec[j] = to;
                    }
                    break; 
                }
            }
        }
    }
    
    std::string result = "";
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) result += ",";
        result += vec[i];
    }
    
    return result;
}
// END IMPLEMENTATION

} // namespace aim::q2

// 下面是测试代码
#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)

using namespace aim::q2;

int main() {
    try {
        CHECK(edit_labels("cam,imu,radar", {{"imu","gyro"},{"cam",""},{"", "lidar"}}) == "gyro,radar,lidar");
        CHECK(edit_labels("cam,cam2,cam", {{"cam","camera"},{"cam",""}}) == "camera,cam2");
        CHECK(edit_labels("cam", {{"cam",""},{"", "imu"}}) == "imu");
        std::cout << "PUBLIC 2/2\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
