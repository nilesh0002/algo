class Solution {
public:
    unordered_set<int> visited, path;
    vector<vector<int>> adj;
    vector<int> ans;
    
    bool dfs(int node) {
        if (path.count(node)) return false;
        if (visited.count(node)) return true;

        path.insert(node);

        for (int next : adj[node]) {
            if (!dfs(next)) return false;
        }

        path.erase(node);
        visited.insert(node);
        ans.push_back(node);

        return true;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        adj.resize(numCourses);

        for (auto& p : prerequisites) {
            adj[p[1]].push_back(p[0]);
        }

        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i)) return {};
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};