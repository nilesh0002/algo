
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> l, r;
        long long sumL = 0, sumR = 0;

        vector<long long> cost(n - x + 1);

        auto add = [&](int val) {
            if (r.empty() || val <= *r.begin()) {
                l.insert(val);
                sumL += val;
            } else {
                r.insert(val);
                sumR += val;
            }
        };

        auto remove = [&](int val) {
            auto it = l.find(val);

            if (it != l.end()) {
                l.erase(it);
                sumL -= val;
            } else {
                it = r.find(val);
                r.erase(it);
                sumR -= val;
            }
        };

        auto balance = [&]() {
            int need = (x + 1) / 2;

            while (l.size() > need) {
                int val = *l.rbegin();
                l.erase(prev(l.end()));
                sumL -= val;

                r.insert(val);
                sumR += val;
            }

            while (l.size() < need) {
                int val = *r.begin();
                r.erase(r.begin());
                sumR -= val;

                l.insert(val);
                sumL += val;
            }
        };

        auto getCost = [&]() -> long long {
            long long med = *l.rbegin();

            return med * l.size() - sumL
                 + sumR - med * r.size();
        };

        // First window
        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        balance();
        cost[0] = getCost();

        // Sliding window
        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            add(nums[i]);

            balance();
            cost[i - x + 1] = getCost();
        }

        // DP
        const long long INF = LLONG_MAX / 4;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];

                if (i >= x) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
