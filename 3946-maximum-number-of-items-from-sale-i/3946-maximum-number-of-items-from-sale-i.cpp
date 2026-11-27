
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        int minPrice = INT_MAX;

        for (auto &it : items) {
            minPrice = min(minPrice, it[1]);
        }

        vector<int> dp(budget + 1, -1e9);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int factor = items[i][0];
            int price = items[i][1];

            int cnt = 0;

            // Count purchased item + free items
            for (int j = 0; j < n; j++) {
                if (items[j][0] % factor == 0) {
                    cnt++;
                }
            }

            // 0/1 Knapsack: first purchase only once
            for (int j = budget; j >= price; j--) {
                if (dp[j - price] != -1e9) {
                    dp[j] = max(dp[j], dp[j - price] + cnt);
                }
            }
        }

        int ans = 0;

        // Buy additional cheapest items
        for (int i = 0; i <= budget; i++) {
            if (dp[i] != -1e9) {
                int extra = (budget - i) / minPrice;
                ans = max(ans, dp[i] + extra);
            }
        }

        return ans;
    }
};
