#include <cmath>
#include <vector>
#include <deque>
#include <numeric>
#include <algorithm>

using namespace std;

#include "convexHullTrickMin.h"
#include "maxProductSumOfSubarray.h"


/////////// For Testing ///////////////////////////////////////////////////////

#include <time.h>
#include <cassert>
#include <string>
#include <iostream>
#include "../common/iostreamhelper.h"
#include "../common/profile.h"
#include "../common/rand.h"

#pragma warning(disable: 4334)

void testProductSumOfSubarray() {
    return; //TODO: if you want to test, make this line a comment.

    cout << "--- Max Product-Sum of All Pairs of Subarray -----------------------------------" << endl;
    {
        int N = 10;
        vector<int> A(1 << N);
        for (int i = 0; i < (1 << N); i++)
            A[i] = RandInt32::get() % 65536;

        AllPairMaxProductSumOfSubarray solver;
        solver.build(A);

        cout << solver.solve() << endl;
    }
    cout << "OK!" << endl;
}
