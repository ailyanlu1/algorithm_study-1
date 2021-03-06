#include <iostream>

using namespace std;

#define TEST(ModuleName)    extern void test##ModuleName(void); \
                            test##ModuleName()

int main(void) {
    TEST(PrefixSum);
    TEST(PrefixSum2D);
    TEST(PackedArray);
    TEST(PersistentArray);
    TEST(PersistentStack);
    TEST(VectorRangeCount);
    TEST(VectorRangeSum);
    TEST(VectorRangeQuery);
}
