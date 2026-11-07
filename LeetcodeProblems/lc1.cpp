#include<vector>
#include<iostream>
#include<unordered_map>

std::vector<int> twoSum(std::vector<int> nums, int target) {
    std::unordered_map<int, int> hashMap;
    int diff;
    // 2, 0
    for (auto index {0}; index < nums.size(); index++){
        hashMap.insert({nums[index], index});
        std::cout << "Insert: " << nums[index] << ", " << index << "\n";
        std:: cout << "Target - Index" << target-nums[index] << "\n";
        if (hashMap.contains(target-nums[index])) {
            std::cout << hashMap[nums[index]] << index;
            return {hashMap[target-nums[index]], index};
        }            
    }
    return {};
}


int main() {
    std::vector<int> twoSim = twoSum({3,2,4}, 6);
}