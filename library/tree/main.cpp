#include <iostream>

using namespace std;

#define TEST(ModuleName)    extern void test##ModuleName(void); \
                            test##ModuleName()

int main(void) {
    TEST(TreeBasic);
    TEST(HeavyLightDecomposition);
    TEST(DfsTour);
    TEST(EulerTour);
    TEST(TreeMO);
    TEST(SparseTableLCA);
    TEST(BST);
    TEST(Splay);
    TEST(SplayRangeQuery);
    TEST(Treap);
    TEST(TreapRangeQuery);
    TEST(LinkCutTree);
    TEST(LinkCutTreePathQuery);
    TEST(CentroidDecomposition);
    TEST(KDTree);
    TEST(KDTreeNoUpdate);
    TEST(IntervalTree);
}