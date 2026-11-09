
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        // Available servers
        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {finishing time, server ID}
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            busy;

        vector<int> count(k, 0);

        for (int i = 0; i < arrival.size(); i++) {

            int time = arrival[i];

            // Free servers that have completed their requests
            while (!busy.empty() && busy.top().first <= time) {
                available.insert(busy.top().second);
                busy.pop();
            }

            // No server is available
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int id = i % k;

            // Find first available server >= id
            auto it = available.lower_bound(id);

            // Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign request
            available.erase(it);

            count[server]++;

            // Store finishing time
            busy.push({time + load[i], server});
        }

        // Find maximum number of requests
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
