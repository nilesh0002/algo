
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {

        vector<vector<pair<int, int>>> adj(n);

        // Build directed graph
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
        }

        // dist[node][count]
        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));

        // {cost, node, consecutive count}
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                       greater<tuple<int, int, int>>>
            pq;

        // Starting node has one character
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {

            auto [cost, u, count] = pq.top();
            pq.pop();

            if (cost != dist[u][count])
                continue;

            if (u == n - 1)
                return cost;

            for (auto [v, w] : adj[u]) {

                int newCount;

                if (labels[u] == labels[v])
                    newCount = count + 1;
                else
                    newCount = 1;

                // Too many consecutive identical characters
                if (newCount > k)
                    continue;

                int newCost = cost + w;

                if (newCost < dist[v][newCount]) {
                    dist[v][newCount] = newCost;

                    pq.push({newCost, v, newCount});
                }
            }
        }

        return -1;
    }
};
