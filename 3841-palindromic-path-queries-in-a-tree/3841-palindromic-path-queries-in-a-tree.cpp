
#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> tree;
    vector<vector<int>> parent;
    vector<int> depth, entry, exitTime, prefixXor;
    int timer, LOG, n;

    // Give each character one bit: a = bit 0, b = bit 1, ...
    int getBit(char c) {
        return 1 << (c - 'a');
    }

    // Find Lowest Common Ancestor using binary lifting
    int findLCA(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        // Bring both nodes to the same depth
        int difference = depth[u] - depth[v];

        for (int k = 0; k < LOG; k++) {
            if (difference & (1 << k))
                u = parent[k][u];
        }

        if (u == v)
            return u;

        // Move both nodes upward until their parents match
        for (int k = LOG - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }

        return parent[0][u];
    }

    // Fenwick Tree for XOR updates
    struct FenwickTree {
        vector<int> bit;
        int size;

        FenwickTree(int n) {
            size = n + 1;
            bit.assign(size + 1, 0);
        }

        void add(int index, int value) {
            index++;

            while (index <= size) {
                bit[index] ^= value;
                index += index & -index;
            }
        }

        // XOR-update every node in the range [left, right]
        void updateRange(int left, int right, int value) {
            add(left, value);
            add(right + 1, value);
        }

        // Get the combined XOR updates affecting this position
        int query(int index) {
            index++;

            int result = 0;
            while (index > 0) {
                result ^= bit[index];
                index -= index & -index;
            }

            return result;
        }
    };

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;
        timer = 0;

        // Step 1: Build the tree
        tree.assign(n, {});

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        // Step 2: Prepare binary lifting
        LOG = 1;
        while ((1 << LOG) <= n)
            LOG++;

        parent.assign(LOG, vector<int>(n, 0));
        depth.assign(n, 0);
        entry.assign(n, 0);
        exitTime.assign(n, 0);
        prefixXor.assign(n, 0);

        // Step 3: DFS to calculate depth, prefix XOR and subtree ranges
        // Iterative DFS avoids recursion stack overflow
        vector<array<int, 3>> st;
        st.push_back({0, 0, 0});

        while (!st.empty()) {
            auto [u, p, state] = st.back();
            st.pop_back();

            if (state == 0) {
                entry[u] = timer++;
                parent[0][u] = p;

                depth[u] = (u == 0) ? 0 : depth[p] + 1;

                prefixXor[u] =
                    ((u == 0) ? 0 : prefixXor[p]) ^ getBit(s[u]);

                // Process children before exiting this node
                st.push_back({u, p, 1});

                for (int v : tree[u]) {
                    if (v == p)
                        continue;

                    st.push_back({v, u, 0});
                }
            } else {
                exitTime[u] = timer - 1;
            }
        }

        // Step 4: Build the binary lifting table
        for (int k = 1; k < LOG; k++) {
            for (int u = 0; u < n; u++) {
                parent[k][u] =
                    parent[k - 1][parent[k - 1][u]];
            }
        }

        // Step 5: Process queries
        FenwickTree fenwick(n);
        vector<bool> answer;

        for (string& query : queries) {
            stringstream ss(query);

            string type;
            int u, v;
            ss >> type >> u;

            // Query type 1: Change a node's character
            if (type == "update") {
                char newChar;
                ss >> newChar;

                int change = getBit(s[u]) ^ getBit(newChar);

                if (change != 0) {
                    fenwick.updateRange(
                        entry[u], exitTime[u], change
                    );

                    s[u] = newChar;
                }
            }

            // Query type 2: Check whether a path can form a palindrome
            else {
                ss >> v;

                int lca = findLCA(u, v);

                // Correct prefix XORs after previous updates
                int xorU =
                    prefixXor[u] ^ fenwick.query(entry[u]);

                int xorV =
                    prefixXor[v] ^ fenwick.query(entry[v]);

                // XOR mask for the path from u to v
                int pathMask =
                    xorU ^ xorV ^ getBit(s[lca]);

                // A palindrome needs at most one odd-frequency character
                answer.push_back(
                    __builtin_popcount((unsigned)pathMask) <= 1
                );
            }
        }

        return answer;
    }
};
