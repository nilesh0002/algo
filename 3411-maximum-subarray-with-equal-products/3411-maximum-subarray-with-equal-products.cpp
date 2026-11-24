class Solution {
public:
    int maxLength(vector<int>& nums) {
         int n = nums.size();
        if (n == 0) return 0;

        // Special case: single element arrays
        if (n == 1) return 1;

        // For arrays with 2 elements, always valid
        if (n == 2) return 2;

        // For longer arrays, need to find longest subarray where all elements are pairwise coprime
        // (except for 1s which can be included freely)
        int max_len = 2;  // Minimum valid length for n >= 2

        // We'll use a sliding window approach
        // Track prime factors in the current window
        unordered_map<int, int> prime_count;  // prime -> count in current window

        // Helper function to get prime factors of a number
        auto get_primes = [](int x) -> unordered_set<int> {
            unordered_set<int> primes;
            if (x <= 1) return primes;

            int num = x;
            for (int i = 2; i * i <= num; i++) {
                if (num % i == 0) {
                    primes.insert(i);
                    while (num % i == 0) {
                        num /= i;
                    }
                }
            }
            if (num > 1) {
                primes.insert(num);
            }
            return primes;
        };

        // Sliding window with two pointers
        int left = 0;
        for (int right = 0; right < n; right++) {
            // Add current number's prime factors to the window
            unordered_set<int> current_primes = get_primes(nums[right]);

            // Check if adding this number conflicts with existing primes in window
            while (!current_primes.empty()) {
                bool conflict = false;
                for (int prime : current_primes) {
                    if (prime_count.find(prime) != prime_count.end() && prime_count[prime] > 0) {
                        conflict = true;
                        break;
                    }
                }

                if (!conflict) break;  // No conflict, can add this number

                // Remove elements from left until no conflict
                unordered_set<int> left_primes = get_primes(nums[left]);
                for (int prime : left_primes) {
                    prime_count[prime]--;
                    if (prime_count[prime] == 0) {
                        prime_count.erase(prime);
                    }
                }
                left++;
            }

            // Add current number's prime factors to the window
            for (int prime : current_primes) {
                prime_count[prime]++;
            }

            // Update max length (window size is right - left + 1)
            max_len = max(max_len, right - left + 1);
        }

        return max_len;
    }
};