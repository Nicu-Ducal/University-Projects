/**
*   Author: Neeecu
*   Data structure: Disjoint Set Union
*/
struct DSU {
    vector<int> parent, rank, size;
    // rank of a vertex ~ height of its subtree
    // 1) size[x] >= 2 ^ rank[x]
    // 2) rank[p[x]] > rank[x], p[x] != x

    DSU(int _n = 0) {
        init(n);
    }

    void init(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1);
        size.resize(n + 1);
        for (int i = 1; i <= n; i++)
            make_set(i);
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 1;
    }

    // Union by rank (size is similar)
    void union_sets(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (rank[x] < rank[y])
                swap(x, y);
            parent[y] = x;
            if (rank[x] == rank[y])
                rank[x]++;
        }
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
};
