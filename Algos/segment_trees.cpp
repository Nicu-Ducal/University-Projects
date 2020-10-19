/**
 *  Author: Neeecu
 *  Data structure: Segment Tree (max)
 */
template<typename T>
struct max_segment_tree {
    vector<T> tree, lazy, arr;
    int n;

    void init(int l, int r, int pos) {
        if (l == r)
            tree[pos] = arr[l];
        else {
            int mid = l + (r - l) / 2;
            init(l, mid, 2 * pos + 1);
            init(mid + 1, r, 2 * pos + 2);
            tree[pos] = max(tree[2 * pos + 1], tree[2 * pos + 2]);
        }
    }

    max_segment_tree(vector<T> _arr) : arr(_arr), n(arr.size()) {
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        init(0, n - 1, 0);
    }

    void add(int idx, T val) {
        _update(val, idx, idx, 0, n - 1, 0);
    }

    void add(int l, int r, T val) {
        _update(val, l, r, 0, n - 1, 0);
    }

    void update(int idx, T val) {
        _update(val - query(idx, idx), idx, idx, 0, n - 1, 0);
    }

    void _update(int val, int l, int r, int li, int ri, int pos) {
        if (lazy[pos] != 0) {
            tree[pos] += lazy[pos];
            if (li != ri) {
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        if (ri < l or r < li)
            return;
        else if (l <= li and ri <= r) {
            tree[pos] += val;
            if (li != ri) {
                lazy[2 * pos + 1] += val;
                lazy[2 * pos + 2] += val;
            }
        } else {
            int mi = li + (ri - li) / 2;
            _update(val, l, r, li, mi, 2 * pos + 1);
            _update(val, l, r, mi + 1, ri, 2 * pos + 2);
            tree[pos] = max(tree[2 * pos + 1], tree[2 * pos + 2]);
        }
    }

    T query(int l, int r) {
        return _query(l, r, 0, n - 1, 0);
    }

    T _query(int l, int r, int li, int ri, int pos) {
        if (lazy[pos] != 0) {
            tree[pos] += lazy[pos];
            if (li != ri) {
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        if (r < li or ri < l)
            return LLONG_MIN;
        else if (l <= li and ri <= r)
            return tree[pos];
        else {
            int mi = li + (ri - li) / 2;
            return max(_query(l, r, li, mi, 2 * pos + 1), _query(l, r, mi + 1, ri, 2 * pos + 2));
        }
    }
};


/**
 *  Author: Neeecu
 *  Data structure: Segment Tree (min)
 */
template<typename T>
struct min_segment_tree {
    vector<T> tree, lazy, arr;
    int n;

    void init(int l, int r, int pos) {
        if (l == r)
            tree[pos] = arr[l];
        else {
            int mid = l + (r - l) / 2;
            init(l, mid, 2 * pos + 1);
            init(mid + 1, r, 2 * pos + 2);
            tree[pos] = min(tree[2 * pos + 1], tree[2 * pos + 2]);
        }
    }

    min_segment_tree(vector<T> _arr) : arr(_arr), n(arr.size()) {
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        init(0, n - 1, 0);
    }

    void add(int idx, T val) {
        _update(val, idx, idx, 0, n - 1, 0);
    }

    void add(int l, int r, T val) {
        _update(val, l, r, 0, n - 1, 0);
    }

    void update(int idx, T val) {
        _update(val - query(idx, idx), idx, idx, 0, n - 1, 0);
    }

    void _update(int val, int l, int r, int li, int ri, int pos) {
        if (lazy[pos] != 0) {
            tree[pos] += lazy[pos];
            if (li != ri) {
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        if (ri < l or r < li)
            return;
        else if (l <= li and ri <= r) {
            tree[pos] += val;
            if (li != ri) {
                lazy[2 * pos + 1] += val;
                lazy[2 * pos + 2] += val;
            }
        } else {
            int mi = li + (ri - li) / 2;
            _update(val, l, r, li, mi, 2 * pos + 1);
            _update(val, l, r, mi + 1, ri, 2 * pos + 2);
            tree[pos] = min(tree[2 * pos + 1], tree[2 * pos + 2]);
        }
    }

    T query(int l, int r) {
        return _query(l, r, 0, n - 1, 0);
    }

    T _query(int l, int r, int li, int ri, int pos) {
        if (lazy[pos] != 0) {
            tree[pos] += lazy[pos];
            if (li != ri) {
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        if (r < li or ri < l)
            return LLONG_MAX;
        else if (l <= li and ri <= r)
            return tree[pos];
        else {
            int mi = li + (ri - li) / 2;
            return min(_query(l, r, li, mi, 2 * pos + 1), _query(l, r, mi + 1, ri, 2 * pos + 2));
        }
    }
};


/**
 *  Author: Neeecu
 *  Data structure: Segment Tree (sum)
 */
template<typename T>
struct sum_segment_tree {
    vector<T> tree, lazy, arr;
    int n;

    void init(int l, int r, int pos) {
        if (l == r)
            tree[pos] = arr[l];
        else {
            int mid = l + (r - l) / 2;
            init(l, mid, 2 * pos + 1);
            init(mid + 1, r, 2 * pos + 2);
            tree[pos] = tree[2 * pos + 1] + tree[2 * pos + 2];
        }
    }

    sum_segment_tree(vector<T> _arr) : arr(_arr), n(arr.size()) {
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        init(0, n - 1, 0);
    }

    void add(int idx, T val) {
        _update(val, idx, idx, 0, n - 1, 0);
    }

    void add(int l, int r, T val) {
        _update(val, l, r, 0, n - 1, 0);
    }

    void update(int idx, T val) {
        _update(val - query(idx, idx), idx, idx, 0, n - 1, 0);
    }

    void _update(int val, int l, int r, int li, int ri, int pos) {
        if (lazy[pos] != 0) {
            tree[pos] += lazy[pos];
            if (li != ri) {
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        if (ri < l or r < li)
            return;
        else if (l <= li and ri <= r) {
            tree[pos] += val;
            if (li != ri) {
                lazy[2 * pos + 1] += val;
                lazy[2 * pos + 2] += val;
            }
        } else {
            int mi = li + (ri - li) / 2;
            _update(val, l, r, li, mi, 2 * pos + 1);
            _update(val, l, r, mi + 1, ri, 2 * pos + 2);
            tree[pos] = tree[2 * pos + 1] + tree[2 * pos + 2];
        }
    }

    T query(int l, int r) {
        return _query(l, r, 0, n - 1, 0);
    }

    T _query(int l, int r, int li, int ri, int pos) {
        if (lazy[pos] != 0) {
            tree[pos] += lazy[pos];
            if (li != ri) {
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        if (r < li or ri < l)
            return 0;
        else if (l <= li and ri <= r)
            return tree[pos];
        else {
            int mi = li + (ri - li) / 2;
            return _query(l, r, li, mi, 2 * pos + 1) + _query(l, r, mi + 1, ri, 2 * pos + 2);
        }
    }
};
