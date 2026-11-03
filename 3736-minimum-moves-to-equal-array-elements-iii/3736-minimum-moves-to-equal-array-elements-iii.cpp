class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int s = 0;
        int m = *max_element(nums.begin(), nums.end());
        for (int i = 0; i < n; i++) {
            s += (m - nums[i]);
        }
        return s;
    }
};