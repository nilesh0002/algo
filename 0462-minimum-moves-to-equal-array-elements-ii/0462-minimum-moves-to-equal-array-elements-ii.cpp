class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int m=nums[n/2];
        int step=0;
        for(int i=0;i<n;i++){
           step+=abs(nums[i]-m);
        }
        return step;
    }
};