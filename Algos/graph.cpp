struct Graph {
    vector<vector<pii>> adj;
    vector<bool> marked;

    Graph(int n = 0) {
        init(n);
    }

    void init(int n) {
        adj.resize(n + 1);
        marked.resize(n + 1);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
};
