
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        long long ans = 0, cost = 0;
        deque<pair<int, int>> dq;

        int j = nums.size() - 1;

        for (int i = nums.size() - 1; i >= 0; i--) {
            int num = nums[i];
            int count = 1;

            while (!dq.empty() && dq.back().first < num) {
                int value = dq.back().first;
                int cnt = dq.back().second;
                dq.pop_back();

                count += cnt;
                cost += 1LL * (num - value) * cnt;
            }

            dq.push_back({num, count});

            while (cost > k) {
                int value = dq.front().first;
                int cnt = dq.front().second;
                dq.pop_front();

                cost -= value - nums[j];
                j--;

                if (cnt > 1)
                    dq.push_front({value, cnt - 1});
            }

            ans += j - i + 1;
        }

        return ans;
    }
};
