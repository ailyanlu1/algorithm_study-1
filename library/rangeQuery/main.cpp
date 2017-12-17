#include <iostream>

using namespace std;

#define TEST(ModuleName)    extern void test##ModuleName(void); \
                            test##ModuleName()

int main(void) {
    TEST(SqrtDecomposition);
    TEST(MOAlgorithm);
    TEST(FenwickTree);
    TEST(FenwickTree2D);
    TEST(FenwickTreeMultAdd);
    TEST(SegmentTree);
    TEST(SegmentTreePersistent);
    TEST(SegmentTreeCompact);
    TEST(SegmentTreeCompactLazy);
    TEST(SegmentTreeCompactLazyAdd);
    TEST(LineSegmentTree);
    TEST(SparseTable);
}
