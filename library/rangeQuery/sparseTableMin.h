#pragma once

//--------- RMQ (Range Minimum Query) - Min Sparse Table ----------------------

struct SparseTableMin {
    int N;
    vector<vector<int>> value;
    vector<int> H;

    template <typename U>
    SparseTableMin(const U& a, int n) {
        this->N = n;

        H.resize(n + 1);
        H[1] = 0;
        for (int i = 2; i < (int)H.size(); i++)
            H[i] = H[i >> 1] + 1;

        value.resize(H.back() + 1, vector<int>(n));
        for (int i = 0; i < n; i++)
            value[0][i] = a[i];

        for (int i = 1; i < (int)value.size(); i++) {
            vector<int>& prev = value[i - 1];
            vector<int>& curr = value[i];
            for (int v = 0; v < n; v++) {
                if (v + (1 << (i - 1)) < n)
                    curr[v] = min(prev[v], prev[v + (1 << (i - 1))]);
                else
                    curr[v] = prev[v];
            }
        }
    }

    // inclusive
    int query(int left, int right) {
        right++;
        if (right <= left)
            return INT_MAX;

        int k = H[right - left];
        vector<int>& mink = value[k];
        return min(mink[left], mink[right - (1 << k)]);
    }
};