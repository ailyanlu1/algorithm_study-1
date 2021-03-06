#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "searchRabinKarp.h"

/////////// For Testing ///////////////////////////////////////////////////////

#include <iostream>
#include <cassert>
#include "../common/iostreamhelper.h"

static vector<int> searchNaive(const string& text, const string& pattern) {
    vector<int> res;

    int textLength = int(text.length());
    int patternLength = int(pattern.length());

    for (int i = 0; i <= textLength - patternLength; i++) {
        bool matched = true;
        for (int j = 0; j < patternLength; j++) {
            if (text[i + j] != pattern[j]) {
                matched = false;
                break;
            }
        }

        if (matched)
            res.push_back(i);
    }

    return res;
}

void testSearchRabinKarp() {
    return; //TODO: if you want to test, make this line a comment.

    cout << "-- Rabin Karp ---------" << endl;
    
    string S = "aabaacaadaabaaba", key = "aaba";

    auto gt = searchNaive(S, key);
    auto ans = searchRabinKarp(S, key);
    auto ans2 = searchRabinKarp2(S, key);
    if (gt != ans || gt != ans2) {
        cerr << "Error: " << gt << " <-> " << ans << endl;
    }
    assert(gt == ans && gt == ans2);

    cout << "OK!" << endl;
}
