/**
 *   Author: Neeecu
 *   Algorithm: KMP (Knuth-Morris-Pratt) String Matching Algorithm
 */
namespace KMP {
    vector<int> pattern_prefix(string pattern, int n) {
        vector<int> res(n, 0);
        int i = 0, j = 1;
        while (j < n) {
            if (pattern[i] == pattern[j]) {
                res[j] = i + 1;
                i++, j++;
            } else {
                if (i != 0) {
                    i = res[i - 1];
                } else {
                    res[j] = 0;
                    j++;
                }
            }
        }
        return res;
    }

    /// Check if pattern is greater than the text
    bool check(string pattern, string text) {
        if (pattern.length() > text.length() or (pattern.length() == text.length() and pattern != text))
            return false;
        return true;
    }

    /// Returns a vector with matching positions
    vector<int> match(string pattern, int n, string text, int m) {
        vector<int> res;
        vector<int> pref_suf = pattern_prefix(pattern, n);
        int i = 0, j = 0;
        while (j < m) {
            if (pattern[i] == text[j]) {
                i++, j++;
                if (i == n) {     /// If you've reached the end of the pattern string, go to the longest prefix
                    res.push_back(j - n);
                    i = pref_suf[i - 1];
                }
            } else {
                if (i != 0) {
                    i = pref_suf[i - 1];
                } else {
                    j++;
                }
            }
        }
        return res;
    }
}
