#include <memory.h>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

#include "segmentTreePersistent.h"
#include "segmentTreePersistentLazy.h"

/////////// For Testing ///////////////////////////////////////////////////////

#include <time.h>
#include <cassert>
#include <string>
#include <iostream>
#include "../common/iostreamhelper.h"
#include "../common/profile.h"

#include "segmentTree.h"

void testSegmentTreePersistent() {
    return; //TODO: if you want to test a split function, make this line a comment.

    cout << "-- Persistent Segment Tree ----------------------------------------" << endl;

    auto segTree = makePersistentSegmentTree(vector<int>{6, 5, 4, 3, 2, 1}, [](int a, int b) { return a + b; });
    auto segTree2 = makePersistentSegmentTree(vector<int>{6, 5, 4, 3, 2, 1}, [](int a, int b) { return min(a, b); }, INT_MAX);
    RMQ rmq(vector<int>{6, 5, 4, 3, 2, 1});

    int ans, ansRMQ;

    ans = segTree.query(1, 3);
    cout << ans << endl;
    assert(ans == 12);

    segTree.update(2, 10);
    ans = segTree.query(1, 3);
    cout << ans << endl;
    assert(ans == 18);

    ans = segTree2.query(1, 3);
    cout << ans << endl;
    assert(ans == 3);

    ansRMQ = rmq.query(1, 3);
    assert(ans == ansRMQ);

    segTree2.update(2, -10);
    ans = segTree2.query(1, 3);
    cout << ans << endl;
    assert(ans == -10);

    rmq.update(2, -10);
    ansRMQ = rmq.query(1, 3);
    assert(ans == ansRMQ);

    segTree.updateRange(0, 2, 3);
    ans = segTree.query(1, 3);
    cout << ans << endl;
    assert(ans == 9);

    segTree2.updateRange(0, 2, 2);
    ans = segTree2.query(1, 3);
    cout << ans << endl;
    assert(ans == 2);

    cout << "*** with history" << endl;

    int history = 0;

    segTree.upgrade(3, 7);
    segTree2.upgradeRange(3, 4, 7);

    ans = segTree.query(history, 1, 3);
    cout << ans << endl;
    assert(ans == 9);

    segTree.upgrade(2, 10);
    ans = segTree.query(history, 1, 3);
    cout << ans << endl;
    assert(ans == 9);

    ans = segTree2.query(history, 1, 3);
    cout << ans << endl;
    assert(ans == 2);

    segTree2.upgrade(2, -10);
    ans = segTree2.query(history, 1, 3);
    cout << ans << endl;
    assert(ans == 2);

    segTree.upgradeRange(0, 2, 3);
    ans = segTree.query(history, 1, 3);
    cout << ans << endl;
    assert(ans == 9);

    segTree2.upgradeRange(0, 2, 2);
    ans = segTree2.query(history, 1, 3);
    cout << ans << endl;
    assert(ans == 2);

    cout << "-- Persistent Segment Tree Performance Test -----------------------" << endl;
    cout << "*** Persistent segment tree vs RMQ" << endl;
    {
        int N = 1000000;

#if _DEBUG
        N = 100000;
#endif

        vector<int> T(N);
        for (int i = 0; i < N; i++)
            T[i] = rand();

        vector<pair<int, int>> Q;
        for (int i = 0; i < N; i++) {
            int a = rand() * rand() % N;
            int b = rand() * rand() % N;
            Q.push_back({ min(a, b), max(a, b) });
        }

        PROFILE_START(0);
        {
            int res = 0;
            auto seg = makePersistentSegmentTree(T, [](int a, int b) { return min(a, b); }, INT_MAX);
            for (int i = 0; i < 10; i++) {
                for (auto& it : Q) {
                    res += seg.query(it.first, it.second);
                }
            }
            cout << "result = " << res << endl;
        }
        PROFILE_STOP(0);

        PROFILE_START(1);
        {
            int res = 0;
            RMQ rmq(T);
            for (int i = 0; i < 10; i++) {
                for (auto& it : Q) {
                    res += rmq.query(it.first, it.second);
                }
            }
            cout << "result = " << res << endl;
        }
        PROFILE_STOP(1);
    }
    cout << "*** Persistent segment tree vs persistent segment tree with lazy propagation" << endl;
    {
        int T = 100000;
        int N = 1000000;
        vector<int> in(N);

        auto segTree = makePersistentSegmentTree(in, [](int a, int b) { return a + b; });
        auto segTreeLazy = makePersistentSegmentTreeLazy(in, [](int a, int b) { return a + b; }, [](int a, int n) { return a * n; });

        vector<tuple<int, int, int, int>> Q;
        for (int i = 0; i < T; i++) {
            if (rand() % 2) {
                int L = rand() % (int)in.size();
                int R = rand() % (int)in.size();
                if (L > R)
                    swap(L, R);
                Q.emplace_back(1, L, R, 0);
            } else {
                int L = rand() % (int)in.size();
                int R = rand() % (int)in.size();
                int x = rand() % 100;
                if (L > R)
                    swap(L, R);
                Q.emplace_back(0, L, R, x);
            }
        }

        for (auto& q : Q) {
            if (get<0>(q)) {
                int L = get<1>(q);
                int R = get<2>(q);

                int a = segTree.query(L, R);
                int b = segTreeLazy.query(L, R);
                if (a != b) {
                    cout << "FAIL in query()" << endl;
                    assert(a == b);
                }
            } else {
                int L = get<1>(q);
                int R = get<2>(q);
                int x = get<3>(q);
                int a = segTree.updateRange(L, R, x);
                int b = segTreeLazy.updateRange(L, R, x);
                if (a != b) {
                    cout << "FAIL in update()" << endl;
                    assert(a == b);
                }
            }
        }
        cout << "OK!" << endl;

        PROFILE_START(0);
        for (auto& q : Q) {
            if (get<0>(q)) {
                int L = get<1>(q);
                int R = get<2>(q);
                if (segTree.query(L, R) == INT_MAX)
                    cout << "It'll Never be shown!" << endl;
            } else {
                int L = get<1>(q);
                int R = get<2>(q);
                int x = get<3>(q);
                segTree.updateRange(L, R, x);
            }
        }
        PROFILE_STOP(0);

        PROFILE_START(1);
        for (auto& q : Q) {
            if (get<0>(q)) {
                int L = get<1>(q);
                int R = get<2>(q);
                if (segTreeLazy.query(L, R) == INT_MAX)
                    cout << "It'll Never be shown!" << endl;
            } else {
                int L = get<1>(q);
                int R = get<2>(q);
                int x = get<3>(q);
                segTreeLazy.updateRange(L, R, x);
            }
        }
        PROFILE_STOP(1);
    }
    cout << "*** with history" << endl;
    {
        int T = 100000;
        int N = 1000000;
        vector<int> in(N);

        auto segTree = makePersistentSegmentTree(in, [](int a, int b) { return a + b; });
        auto segTreeLazy = makePersistentSegmentTreeLazy(in, [](int a, int b) { return a + b; }, [](int a, int n) { return a * n; });

        int history = 0;
        segTree.upgrade(3, 7);
        segTreeLazy.upgradeRange(3, 4, 7);

        vector<tuple<int, int, int, int>> Q;
        for (int i = 0; i < T; i++) {
            if (rand() % 2) {
                int L = rand() % (int)in.size();
                int R = rand() % (int)in.size();
                if (L > R)
                    swap(L, R);
                Q.emplace_back(1, L, R, 0);
            } else {
                int L = rand() % (int)in.size();
                int R = rand() % (int)in.size();
                int x = rand() % 100;
                if (L > R)
                    swap(L, R);
                Q.emplace_back(0, L, R, x);
            }
        }

        for (auto& q : Q) {
            if (get<0>(q)) {
                int L = get<1>(q);
                int R = get<2>(q);

                int a = segTree.query(history, L, R);
                int b = segTreeLazy.query(history, L, R);
                if (a != b) {
                    cout << "FAIL!" << endl;
                    assert(a == b);
                }
            } else {
                int L = get<1>(q);
                int R = get<2>(q);
                int x = get<3>(q);
                int a = segTree.updateRange(history, L, R, x);
                int b = segTreeLazy.updateRange(history, L, R, x);
                if (a != b) {
                    cout << "FAIL in update()" << endl;
                    assert(a == b);
                }
            }
        }
        cout << "OK!" << endl;

        PROFILE_START(0);
        for (auto& q : Q) {
            if (get<0>(q)) {
                int L = get<1>(q);
                int R = get<2>(q);
                if (segTree.query(history, L, R) == INT_MAX)
                    cout << "It'll Never be shown!" << endl;
            } else {
                int L = get<1>(q);
                int R = get<2>(q);
                int x = get<3>(q);
                segTree.updateRange(history, L, R, x);
            }
        }
        PROFILE_STOP(0);

        PROFILE_START(1);
        for (auto& q : Q) {
            if (get<0>(q)) {
                int L = get<1>(q);
                int R = get<2>(q);
                if (segTreeLazy.query(history, L, R) == INT_MAX)
                    cout << "It'll Never be shown!" << endl;
            } else {
                int L = get<1>(q);
                int R = get<2>(q);
                int x = get<3>(q);
                segTreeLazy.updateRange(history, L, R, x);
            }
        }
        PROFILE_STOP(1);
    }

    cout << "OK!" << endl;
}