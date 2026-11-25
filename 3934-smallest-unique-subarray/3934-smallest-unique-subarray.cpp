class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        
        // Two large primes and bases for double rolling hash to prevent collisions
        const long long MOD1 = 1e9 + 7, BASE1 = 131313;
        const long long MOD2 = 1e9 + 9, BASE2 = 131319;
        
        vector<long long> pow1(n + 1, 1), pow2(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pow1[i] = (pow1[i - 1] * BASE1) % MOD1;
            pow2[i] = (pow2[i - 1] * BASE2) % MOD2;
        }
        
        auto hasUniqueOfLength = [&](int len) -> bool {
            unordered_map<uint64_t, int> freq;
            freq.reserve(n - len + 1);
            
            long long h1 = 0, h2 = 0;
            for (int i = 0; i < n; ++i) {
                // Add current element to the rolling hash
                h1 = (h1 * BASE1 + nums[i]) % MOD1;
                h2 = (h2 * BASE2 + nums[i]) % MOD2;
                
                // Remove the element that slides out of the window
                if (i >= len) {
                    h1 = (h1 - (nums[i - len] * pow1[len]) % MOD1 + MOD1) % MOD1;
                    h2 = (h2 - (nums[i - len] * pow2[len]) % MOD2 + MOD2) % MOD2;
                }
                
                // Once we have a full window of size `len`, record its combined hash
                if (i >= len - 1) {
                    uint64_t combined = (uint64_t(h1) << 32) | uint64_t(h2);
                    freq[combined]++;
                }
            }
            
            for (const auto& [hashVal, count] : freq) {
                if (count == 1) return true;
            }
            return false;
        };
        
        int low = 1, high = n, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hasUniqueOfLength(mid)) {
                ans = mid;
                high = mid - 1; // Try to find an even smaller length
            } else {
                low = mid + 1;  // Need a longer subarray
            }
        }
        
        return ans;
    }
};
