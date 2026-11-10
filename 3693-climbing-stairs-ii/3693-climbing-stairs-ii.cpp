
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<long long> dp(n + 1, LLONG_MAX);

        dp[0] = 0;

        for (int i = 1; i <= n; i++) {

            for (int j = max(0, i - 3); j < i; j++) {

                long long jump = i - j;

                dp[i] = min(
                    dp[i],
                    dp[j] + costs[i - 1] + jump * jump
                );
            }
        }

        return dp[n];
    }
};
