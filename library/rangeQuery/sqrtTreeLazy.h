#pragma once

// https://e-maxx-eng.appspot.com/data_structures/sqrt-tree.html

template <typename T, typename MergeOp = function<T(T, T)>, typename BlockOp = function<T(T, int)>>
struct SqrtTreeLazy {
    int N;
    int H;
    vector<T> value;                // 

    vector<int> layers;             // layer -> log
    vector<int> onLayer;            // log -> layer

    int lazyBlockSize;              // block size of layer 0
    vector<T> lazy;                 // 
    vector<bool> lazyExist;         // 

    vector<vector<T>> prefix;       // right side, A[L..i]
    vector<vector<T>> suffix;       // left side, A[i..R]
    vector<vector<T>> between;      // left and right side, A[i..j] (L <= i <= j <= R)

    MergeOp mergeOp;
    BlockOp blockOp;
    T       defaultValue;

    SqrtTreeLazy(MergeOp mop, BlockOp bop, T dfltValue = T())
        : lazyBlockSize(0), mergeOp(mop), blockOp(bop), defaultValue(dfltValue) {
    }

    SqrtTreeLazy(int n, const T& val, MergeOp op, T dfltValue = T())
        : mergeOp(op), blockOp(bop), defaultValue(dfltValue) {
        build(n, val);
    }

    SqrtTreeLazy(const T a[], int n, MergeOp mop, BlockOp bop, T dfltValue = T())
        : mergeOp(mop), blockOp(bop), defaultValue(dfltValue) {
        build(a, n);
    }

    SqrtTreeLazy(const vector<T>& a, MergeOp mop, BlockOp bop, T dfltValue = T())
        : mergeOp(mop), blockOp(bop), defaultValue(dfltValue) {
        build(a);
    }


    // O(N*loglogN)
    void build(int n, const T& val) {
        N = n;
        value.assign(n, val);
        buildTree(n);
        initSqrt(n);
    }

    // O(N*loglogN)
    void build(const T arr[], int n) {
        N = n;
        value.assign(arr, arr + n);
        buildTree(n);
        initSqrt(n);
    }

    void build(const vector<T>& v) {
        build(&v[0], int(v.size()));
    }

    //--- update

    // O(sqrt(N)), inclusive
    void update(int index, const T& val) {
        applyBlock(index / lazyBlockSize);
        value[index] = val;
        updateSub(0, 0, N - 1, index);
    }

    // O(N*loglogN), inclusive
    void update(int left, int right, const T& val) {
        updateBlock(left, right, val);
        updateSub(0, 0, N - 1, left, right);
    }

    //--- query

    // O(1), inclusive
    T query(int index) const {
        int blockIndex = index / lazyBlockSize;
        if (lazyExist[blockIndex])
            return lazy[blockIndex];
        else
            return value[index];
    }

    // O(1), inclusive
    T query(int left, int right) const {
        if (left == right)
            return query(left);

        if (left + 1 == right)
            return mergeOp(query(left), query(right));

        int layer = onLayer[sizeof(int) * 8 - clz(left ^ right)];
        int sizeLog = (layers[layer] + 1) >> 1;
        int countLog = layers[layer] >> 1;

        int lBound = (left >> layers[layer]) << layers[layer];
        int lBlock = ((left - lBound) >> sizeLog) + 1;
        int rBlock = ((right - lBound) >> sizeLog) - 1;

        T ans = suffix[layer][left];
        if (lBlock <= rBlock)
            ans = mergeOp(ans, between[layer][lBound + (lBlock << countLog) + rBlock]);

        return mergeOp(ans, prefix[layer][right]);
    }

private:
    void initSqrt(int n) {
        lazyBlockSize = 1 << ((layers[0] + 1) >> 1);
        int count = (n + lazyBlockSize - 1) / lazyBlockSize;

        lazy.assign(count, defaultValue);
        lazyExist.assign(count, false);
    }

    void buildTree(int n) {
        H = 0;
        while ((1 << H) < n)
            H++;

        onLayer.assign(H + 1, 0);

        layers.clear();
        for (int i = H; i > 1; i = (i + 1) >> 1) {
            onLayer[i] = int(layers.size());
            layers.push_back(i);
        }

        for (int i = H - 1; i >= 0; i--) {
            onLayer[i] = max(onLayer[i], onLayer[i + 1]);
        }

        prefix.assign(layers.size(), vector<T>(n));
        suffix.assign(layers.size(), vector<T>(n));
        between.assign(layers.size(), vector<T>(size_t(1) << H));

        buildSub(0, 0, n - 1);
    }

    void applyBlock(int blockIndex) {
        if (!lazyExist[blockIndex])
            return;

        T val = lazy[blockIndex];

        int L = blockIndex * lazyBlockSize;
        int R = min(L + lazyBlockSize - 1, N - 1);
        while (L <= R)
            value[L++] = val;

        lazyExist[blockIndex] = false;
    }

    void updateBlock(int left, int right, const T& val) {
        int blockIndexL = left / lazyBlockSize;
        int blockIndexR = right / lazyBlockSize;

        if (blockIndexL == blockIndexR) {
            applyBlock(blockIndexL);
            while (left <= right)
                value[left++] = val;
        } else {
            int leftN = lazyBlockSize - left % lazyBlockSize;
            if (leftN < lazyBlockSize) {
                applyBlock(blockIndexL);
                while (leftN-- > 0)
                    value[left++] = val;
                blockIndexL++;
            }

            int rightN = right % lazyBlockSize + 1;
            if (rightN < lazyBlockSize) {
                applyBlock(blockIndexR);
                while (rightN-- > 0)
                    value[right--] = val;
                blockIndexR--;
            }

            while (blockIndexL <= blockIndexR) {
                lazy[blockIndexL] = val;
                lazyExist[blockIndexL] = true;
                blockIndexL++;
            }
        }
    }


    void buildPrefixSuffix(int layer, int left, int right) {
        prefix[layer][left] = value[left];
        for (int i = left + 1; i <= right; i++) {
            prefix[layer][i] = mergeOp(prefix[layer][i - 1], value[i]);
        }

        suffix[layer][right] = value[right];
        for (int i = right - 1; i >= left; i--) {
            suffix[layer][i] = mergeOp(value[i], suffix[layer][i + 1]);
        }
    }

    void buildBetween(int layer, int left, int right, int sizeLog, int countLog) {
        int count = (right - left) / (1 << sizeLog) + 1;

        for (int i = 0; i < count; i++) {
            T ans = defaultValue;
            for (int j = i; j < count; j++) {
                ans = mergeOp(ans, suffix[layer][left + (j << sizeLog)]);
                between[layer][left + (i << countLog) + j] = ans;
            }
        }
    }


    void updatePrefixSuffix(int layer, int left, int right) {
        int blockIndex = left / lazyBlockSize;
        if (!lazyExist[blockIndex]) {
            buildPrefixSuffix(layer, left, right);
            return;
        }

        T val = lazy[blockIndex];

        prefix[layer][left] = val;
        for (int i = left + 1; i <= right; i++)
            prefix[layer][i] = mergeOp(prefix[layer][i - 1], val);

        suffix[layer][right] = val;
        for (int i = right - 1; i >= left; i--)
            suffix[layer][i] = mergeOp(val, suffix[layer][i + 1]);
    }

    void updateBetween(int layer, int left, int right, int blockIndex, int sizeLog, int countLog) {
        int rightIndex = (right - left) / (1 << sizeLog);

        for (int i = 0; i <= blockIndex; i++) {
            T ans = defaultValue;
            if (i < blockIndex)
                ans = between[layer][left + (i << countLog) + blockIndex - 1];
            for (int j = blockIndex; j <= rightIndex; j++) {
                ans = mergeOp(ans, suffix[layer][left + (j << sizeLog)]);
                between[layer][left + (i << countLog) + j] = ans;
            }
        }
    }

    void updateBetween(int layer, int left, int right, int blockIndexL, int blockIndexR, int sizeLog, int countLog) {
        int rightIndex = (right - left) / (1 << sizeLog);

        for (int i = 0; i <= blockIndexR; i++) {
            T ans = defaultValue;
            if (i < blockIndexL)
                ans = between[layer][left + (i << countLog) + blockIndexL - 1];
            for (int j = max(i, blockIndexL); j <= rightIndex; j++) {
                ans = mergeOp(ans, suffix[layer][left + (j << sizeLog)]);
                between[layer][left + (i << countLog) + j] = ans;
            }
        }
    }


    void buildSub(int layer, int left, int right) {
        if (layer >= int(layers.size()))
            return;

        int sizeLog = (layers[layer] + 1) >> 1;
        int countLog = layers[layer] >> 1;
        int size = 1 << sizeLog;

        for (int L = left; L <= right; L += size) {
            int R = min(L + size - 1, right);
            buildPrefixSuffix(layer, L, R);
            buildSub(layer + 1, L, R);
        }

        buildBetween(layer, left, right, sizeLog, countLog);
    }

    void updateSub(int layer, int left, int right, int index) {
        if (layer >= int(layers.size()))
            return;

        int sizeLog = (layers[layer] + 1) >> 1;
        int countLog = layers[layer] >> 1;
        int size = 1 << sizeLog;

        int blockIndex = (index - left) / size;

        int L = left + blockIndex * size;
        int R = min(L + size - 1, right);
        updatePrefixSuffix(layer, L, R);
        updateBetween(layer, left, right, blockIndex, sizeLog, countLog);
        updateSub(layer + 1, L, R, index);
    }

    void updateSub(int layer, int left, int right, int indexLeft, int indexRight) {
        if (layer >= int(layers.size()))
            return;

        int sizeLog = (layers[layer] + 1) >> 1;
        int countLog = layers[layer] >> 1;
        int size = 1 << sizeLog;

        int blockIndexL = (max(left, indexLeft) - left) / size;
        int blockIndexR = (min(right, indexRight) - left) / size;
        for (int L = left + blockIndexL * size, maxL = left + blockIndexR * size; L <= maxL; L += size) {
            int R = min(L + size - 1, right);
            updatePrefixSuffix(layer, L, R);
            updateSub(layer + 1, L, R, indexLeft, indexRight);
        }

        updateBetween(layer, left, right, blockIndexL, blockIndexR, sizeLog, countLog);
    }

    static int clz(int x) {
#ifndef __GNUC__
        return int(__lzcnt(unsigned(x)));
#else
        return __builtin_clz(unsigned(x));
#endif
    }
};

template <typename T, typename MergeOp, typename BlockOp>
SqrtTreeLazy<T, MergeOp, BlockOp> makeSqrtTreeLazy(const vector<T>& arr, MergeOp mop, BlockOp bop, T dfltValue = T()) {
    return SqrtTreeLazy<T, MergeOp, BlockOp>(arr, mop, bop, dfltValue);
}

template <typename T, typename MergeOp, typename BlockOp>
SqrtTreeLazy<T, MergeOp, BlockOp> makeSqrtTreeLazy(const T arr[], int size, MergeOp mop, BlockOp bop, T dfltValue = T()) {
    return SqrtTreeLazy<T, MergeOp, BlockOp>(arr, size, mop, bop, dfltValue);
}