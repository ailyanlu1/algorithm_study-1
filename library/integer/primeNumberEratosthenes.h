#pragma once

// get all prime numbers in [0, n], inclusive
// O(N loglogN)
inline vector<bool> eratosthenes(int n) {
    vector<bool> res(n + 1, true);
    res[0] = false;
    res[1] = false;

    if (n >= 4) {
        for (int j = 2 * 2; j <= n; j += 2)
            res[j] = false;
    }

    int root = int(sqrt(n));
    for (int i = 3; i <= root; i += 2) {
        if (res[i]) {
            for (int j = i * i; j >= 0 && j <= n; j += i)
                res[j] = false;
        }
    }

    return res;
}

// get all prime numbers in [0, n], inclusive
// O(N loglogN)
inline vector<int> eratosthenes2(int n) {
    vector<bool> p = eratosthenes(n);

    vector<int> res;
    if (n >= 2)
        res.push_back(2);
    for (int i = 3; i <= n; i += 2)
        if (p[i])
            res.push_back(i);

    return res;
}


// get all prime numbers
// inclusive, O(N loglogN)
inline vector<bool> eratosthenes(int left, int right) {
    int n = right - left + 1;
    vector<bool> res(n, true);

    if (left <= 0 && 0 <= right)
        res[0] = false;
    if (left <= 1 && 1 <= right)
        res[1 - left] = false;

    int root = int(sqrt(right));
    vector<bool> p(root + 1, true);

    if (root >= 4) {
        for (int j = 4; j <= root; j += 2)
            p[j] = false;
        for (int j = max(4, left + (left & 1)); j <= right; j += 2)
            res[j - left] = false;
    }
    for (int i = 3; i <= root; i += 2) {
        if (p[i]) {
            for (int j = i * i; j >= 0 && j <= root; j += i)
                p[j] = false;
            for (int j = max(i * i, ((left + i - 1) / i) * i); j >= 0 && j <= right; j += i)
                res[j - left] = false;
        }
    }

    return res;
}

// get all prime numbers
// inclusive, O(N loglogN)
inline vector<int> eratosthenes2(int left, int right) {
    vector<bool> p = eratosthenes(left, right);

    vector<int> res;
    for (int i = left; i <= right; i++)
        if (p[i - left])
            res.push_back(i);

    return res;
}
