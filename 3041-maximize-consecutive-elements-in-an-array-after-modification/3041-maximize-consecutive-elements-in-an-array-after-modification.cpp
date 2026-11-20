#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        // Sort the array so we can build consecutive sequences in increasing order
        sort(nums.begin(), nums.end());
        
        // dp[v] stores the max length of a consecutive sequence ending at value v
        unordered_map<int, int> dp;
        int max_len = 0;
        
        for (int num : nums) {
            // Option 1: Increase num by 1 (becomes num + 1), extending a sequence ending at num
            dp[num + 1] = dp[num] + 1;
            
            // Option 2: Keep num as is, extending a sequence ending at num - 1
            dp[num] = dp[num - 1] + 1;
            
            max_len = max({max_len, dp[num], dp[num + 1]});
        }
        
        return max_len;
    }
};
