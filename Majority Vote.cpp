# Answer

#include <vector>
#include <algorithm>  // For min and max
using namespace std;

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int candidate1 = -1, candidate2 = -1;  // Initialize candidates with invalid values
        int count1 = 0, count2 = 0;
        int n = nums.size();

        // Early return if the array has less than 3 elements
        if (n == 0) return {};  // No elements
        if (n == 1) return {nums[0]};  // Only one element, return it as the majority
        if (n == 2) {  // Two elements, either both are the same or both are different
            if (nums[0] == nums[1]) return {nums[0]};
            return {min(nums[0], nums[1]), max(nums[0], nums[1])};
        }

        // First pass: Find potential candidates using Boyer-Moore Voting Algorithm
        for (int num : nums) {
            if (num == candidate1) {
                count1++;
            } else if (num == candidate2) {
                count2++;
            } else if (count1 == 0) {
                candidate1 = num;
                count1 = 1;
            } else if (count2 == 0) {
                candidate2 = num;
                count2 = 1;
            } else {
                count1--;
                count2--;
            }
        }

        // Second pass: Validate the candidates
        count1 = count2 = 0;
        for (int num : nums) {
            if (num == candidate1) count1++;
            else if (num == candidate2) count2++;
        }
        vector<int> result;
        if (count1 > n / 3) result.push_back(candidate1);  // If candidate1 is a majority
        if (count2 > n / 3) result.push_back(candidate2);  // If candidate2 is a majority

        // If no valid majority candidate is found, return {-1}
        if (result.empty()) return {-1};

        // The result must be sorted in increasing order
        sort(result.begin(), result.end());

        return result;
    }
};
