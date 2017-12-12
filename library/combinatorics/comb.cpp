#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "comb.h"
#include "combMod.h"

/////////// For Testing ///////////////////////////////////////////////////////

#include <time.h>
#include <cassert>
#include <iostream>
#include "../common/iostreamhelper.h"

void testComb() {
    //return; //TODO: if you want to test functions of this file, make this line a comment.

    cout << "--- Combination --------------------------------------" << endl;
    {
        int N = 30;

        CombAllDP dpA(N);
        CombCompactDP dpC(N);

        for (int r = 0; r <= N; r++) {
            assert(combNaive(N, r) == dpA.comb(N, r));
            assert(combNaive(N, r) == dpC.comb(r));
        }
    }
    {
        int N = 70;
        int MOD = 1000000007;

        CombAllModDP dpA(N, MOD);

        for (int r = 0; r <= N; r++) {
            assert(combModNaive(N, r, MOD) == dpA.comb(N, r));
            assert(combModPrimeNaive(N, r, MOD) == dpA.comb(N, r));
            assert(combLucasModNaive(N, r, MOD) == dpA.comb(N, r));

            assert(combMod(N, r, MOD) == dpA.comb(N, r));
            assert(combModPrime(N, r, MOD) == dpA.comb(N, r));
            assert(combLucasMod(N, r, MOD) == dpA.comb(N, r));

            assert(combModNaive(N, r, MOD) == dpA.comb(N, r));
            assert(combModPrimeNaive(N, r, MOD) == dpA.comb(N, r));
            assert(combLucasModNaive(N, r, MOD) == dpA.comb(N, r));

            assert(combMod(N, r, MOD) == dpA.comb(N, r));
            assert(combModPrime(N, r, MOD) == dpA.comb(N, r));
            assert(combLucasMod(N, r, MOD) == dpA.comb(N, r));
        }

        assert(combLucasModNaive(1000, 900, 13) == 8);
        assert(combLucasMod(1000, 900, 13) == 8);
    }
    {
        int MOD = 1117;
        CombLucasModDP dpL(MOD);

        long long NN = 13124314124214ll;
        for (long long r = 3124314124214ll; r <= NN; r += 124314124214ll) {
            assert(combLucasModNaive(NN, r, MOD) == dpL.comb(NN, r));
            assert(combLucasMod(NN, r, MOD) == dpL.comb(NN, r));
        }
    }

    cout << "OK!" << endl;
}